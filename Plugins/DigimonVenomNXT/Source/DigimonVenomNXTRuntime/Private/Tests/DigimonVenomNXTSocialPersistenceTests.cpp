#if WITH_DEV_AUTOMATION_TESTS

#include "DigimonVenomNXTSocialSubsystem.h"
#include "DigimonVenomNXTSocialCore.h"
#include "JsonObjectConverter.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDigimonVenomNXTSocialDatabaseIntegrityTest,
    "DigimonVenomNXT.Community.Social.AtomicDatabaseInvariantsAndRoundTrip",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDigimonVenomNXTSocialDatabaseIntegrityTest::RunTest(const FString& Parameters)
{
    (void)Parameters;
    FDigimonSocialDatabase Empty;
    TestTrue(TEXT("A new account server starts with an empty valid social database"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Empty));
    FDigimonSocialDatabase DB;
    FDigimonSocialAccountRecord A, B;
    A.AccountId = TEXT("immutable-account-A"); A.Username = TEXT("Alice");
    B.AccountId = TEXT("immutable-account-B"); B.Username = TEXT("Bob");
    DB.Accounts = {A, B};
    DB.Accounts[0].OutgoingFriends.Add(B.AccountId);
    TestFalse(TEXT("A request cannot be committed on only one side"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(DB));
    DB.Accounts[1].IncomingFriends.Add(A.AccountId);
    TestTrue(TEXT("Pending request round trip is mutually consistent"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(DB));
    DB.Accounts[0].OutgoingFriends.Reset(); DB.Accounts[1].IncomingFriends.Reset();
    DB.Accounts[0].Friends.Add(B.AccountId);
    TestFalse(TEXT("A friendship cannot be committed on only one side"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(DB));
    DB.Accounts[1].Friends.Add(A.AccountId);
    TestTrue(TEXT("Mutual friendship is valid"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(DB));
    DB.Accounts[0].Ignored.Add(B.AccountId);
    TestFalse(TEXT("Ignoring requires removal of an existing friendship"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(DB));
    DB.Accounts[0].Ignored.Reset();

    FDigimonClanRecord Clan;
    Clan.ClanId = TEXT("immutable-clan-id"); Clan.Name = TEXT("Venom Guardians"); Clan.Tag = TEXT("VNOM");
    FDigimonClanMemberRecord Leader, Member;
    Leader.AccountId = A.AccountId; Leader.Role = EDigimonClanRole::Leader; Leader.JoinedUnix = 123;
    Member.AccountId = B.AccountId; Member.Role = EDigimonClanRole::Member; Member.JoinedUnix = 456;
    Clan.Members = {Leader, Member}; DB.Clans.Add(Clan);
    TestTrue(TEXT("A clan has one leader and unique member IDs"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(DB));
    FString Json; FDigimonSocialDatabase Restored;
    TestTrue(TEXT("Serialize all relationships and clan ranks"), FJsonObjectConverter::UStructToJsonObjectString(DB, Json));
    TestTrue(TEXT("Read persisted social relationships"), FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Restored, 0, 0));
    TestTrue(TEXT("Reload preserves valid bidirectional friendship and unique leadership"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Restored));
    TestTrue(TEXT("Every server record round-trips exactly"), FDigimonSocialDatabase::StaticStruct()->CompareScriptStruct(&DB, &Restored, 0));

    FDigimonSocialDatabase Invalid = DB;
    Invalid.Clans[0].Members[0].Role = EDigimonClanRole::Member;
    TestFalse(TEXT("A leaderless clan is rejected"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Invalid));
    Invalid = DB; Invalid.Clans[0].Members[1].Role = EDigimonClanRole::Leader;
    TestFalse(TEXT("Two simultaneous leaders are rejected"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Invalid));
    Invalid = DB;
    FDigimonClanRecord Other = Clan; Other.ClanId = TEXT("other-clan"); Other.Name = TEXT("Other Clan"); Other.Tag = TEXT("OTHER");
    Invalid.Clans.Add(Other);
    TestFalse(TEXT("An account can never belong to two clans"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Invalid));
    Invalid = DB; Invalid.Accounts[0].Friends.Add(A.AccountId);
    TestFalse(TEXT("A player cannot friend their own account"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Invalid));
    Invalid = DB; Invalid.Accounts[0].Friends.Add(B.AccountId);
    TestFalse(TEXT("Duplicate relationship rows are rejected"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Invalid));
    Invalid = DB; Invalid.Accounts[0].Friends.Add(TEXT("unknown-id"));
    TestFalse(TEXT("A nonexistent identity cannot be inserted into a friends list"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Invalid));

    FDigimonSocialDatabase Invitations = DB;
    FDigimonSocialAccountRecord Invitee; Invitee.AccountId = TEXT("invitee-C"); Invitee.Username = TEXT("Charlie");
    Invitations.Accounts.Add(Invitee);
    FDigimonClanInvitationRecord Invitation; Invitation.AccountId = Invitee.AccountId;
    Invitation.InviterAccountId = A.AccountId; Invitation.ExpiresUnix = 9999999;
    Invitations.Clans[0].Invitations.Add(Invitation);
    TestTrue(TEXT("A leader can have a pending invitation to an unaffiliated account"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Invitations));
    Invitations.Clans[0].Invitations[0].InviterAccountId = B.AccountId;
    TestFalse(TEXT("Regular members cannot retain privileged invitations"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Invitations));
    Invitations.Clans[0].Invitations[0].InviterAccountId = A.AccountId;
    Invitations.Accounts.Last().Ignored.Add(A.AccountId);
    TestFalse(TEXT("Ignoring an inviter requires clearing their clan invitation"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Invitations));
    Invitations.Accounts.Last().Ignored.Reset();
    Invitations.Clans[0].Invitations[0].AccountId = B.AccountId;
    TestFalse(TEXT("Players already in a clan cannot retain join invitations"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Invitations));

    // Deleting an offline account and later reusing its name must never migrate friends to the new account.
    FDigimonSocialAccountRecord Reused; Reused.AccountId = TEXT("new-account-A"); Reused.Username = A.Username;
    Restored.Accounts.Add(Reused);
    TestTrue(TEXT("Names may be reused while historical IDs remain isolated"), UDigimonVenomNXTSocialSubsystem::ValidateDatabase(Restored));
    TestEqual(TEXT("New identity receives no old friendships"), Restored.Accounts.Last().Friends.Num(), 0);
    return true;
}
#endif
