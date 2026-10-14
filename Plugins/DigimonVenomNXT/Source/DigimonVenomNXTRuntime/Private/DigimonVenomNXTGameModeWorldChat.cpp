#include "DigimonVenomNXTGameMode.h"
#include "DigimonVenomNXTPlayerController.h"
#include "DigimonVenomNXTPlayerState.h"
#include "DigimonVenomNXTSocialSubsystem.h"
#include "DigimonVenomNXTAuthSubsystem.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

int32 ADigimonVenomNXTGameMode::BroadcastWorldChat(const FDigimonChatMessage& Message, const ADigimonVenomNXTPlayerController* Excluded)
{
    if (!HasAuthority() || !GetWorld()) return 0;
    int32 Recipients = 0;
    const UDigimonVenomNXTSocialSubsystem* Social = GetGameInstance()->GetSubsystem<UDigimonVenomNXTSocialSubsystem>();
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        ADigimonVenomNXTPlayerController* Recipient = Cast<ADigimonVenomNXTPlayerController>(It->Get());
        if (!Recipient || Recipient == Excluded || !Recipient->IsAccountAuthenticated()) continue;
        const ADigimonVenomNXTPlayerState* RecipientState = Recipient->GetPlayerState<ADigimonVenomNXTPlayerState>();
        if (Social && RecipientState && Social->IsIgnoring(RecipientState->Profile.AccountId, Message.SenderAccountId)) continue;
        // All public habitats and private menu views share this authenticated server session.
        // No pawn, distance, streaming-zone or currently selected map dependency.
        Recipient->ClientReceiveLocalChat(Message);
        ++Recipients;
    }
    return Recipients;
}

void ADigimonVenomNXTGameMode::JoinWorldChat(ADigimonVenomNXTPlayerController* Controller)
{
    if (!HasAuthority() || !Controller || !Controller->IsAccountAuthenticated()) return;
    const TWeakObjectPtr<ADigimonVenomNXTPlayerController> Key(Controller);
    if (WorldChatMembers.Contains(Key)) return;
    const ADigimonVenomNXTPlayerState* State = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>();
    if (!State || State->Profile.AccountId.IsEmpty() || State->Profile.Username.IsEmpty()) return;
    WorldChatMembers.Add(Key, State->Profile.Username);
    FDigimonChatMessage Notice;
    Notice.Kind = EDigimonChatMessageKind::PlayerJoined;
    Notice.Sender = State->Profile.Username;
    Notice.SenderAccountId = State->Profile.AccountId;
    Notice.Message = Notice.Sender + TEXT(" has joined the game.");
    Notice.UnixTime = FDateTime::UtcNow().ToUnixTimestamp();
    BroadcastWorldChat(Notice);
}

void ADigimonVenomNXTGameMode::LeaveWorldChat(ADigimonVenomNXTPlayerController* Controller)
{
    if (!HasAuthority() || !Controller) return;
    FString Username;
    // Remove first: orderly deauthentication and the later engine Logout must emit only once.
    // The trusted admission name survives missing player state/pawn during disconnect teardown.
    if (!WorldChatMembers.RemoveAndCopyValue(TWeakObjectPtr<ADigimonVenomNXTPlayerController>(Controller), Username)) return;
    FDigimonChatMessage Notice;
    Notice.Kind = EDigimonChatMessageKind::PlayerLeft;
    Notice.Sender = Username;
    if (const ADigimonVenomNXTPlayerState* State = Controller->GetPlayerState<ADigimonVenomNXTPlayerState>()) Notice.SenderAccountId = State->Profile.AccountId;
    if (Notice.SenderAccountId.IsEmpty())
        if (const UDigimonVenomNXTAuthSubsystem* Auth = GetGameInstance()->GetSubsystem<UDigimonVenomNXTAuthSubsystem>())
        {
            FString CanonicalName;
            Auth->GetAccountIdentity(Username, CanonicalName, Notice.SenderAccountId);
        }
    Notice.Message = Username + TEXT(" has left the game.");
    Notice.UnixTime = FDateTime::UtcNow().ToUnixTimestamp();
    BroadcastWorldChat(Notice);
}
