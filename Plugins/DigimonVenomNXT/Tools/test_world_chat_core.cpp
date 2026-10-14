#include "../Source/DigimonVenomNXTRuntime/Private/DigimonVenomNXTWorldChatCore.h"
#include <cassert>
#include <iostream>
#include <limits>
using namespace DigimonVenomNXTWorldChatCore;
int main()
{
    int Checks = 0;
    auto Check = [&](bool Value) { ++Checks; assert(Value); };
    Check(CanSend(0.0, -1000.0));
    Check(!CanSend(1.99, 1.0));
    Check(CanSend(2.0, 1.0));
    Check(!CanSend(0.0, 2.0));
    Check(!CanSend(std::numeric_limits<double>::infinity(), 0.0));
    Check(!CanSend(std::numeric_limits<double>::quiet_NaN(), 0.0));
    auto Text = [](const std::u16string& S, int Limit=180) { return Normalize(S.data(), static_cast<int>(S.size()), Limit); };
    Check(Text(u" \t\r\n ").empty());
    Check(Text(u" hello\r\nworld \t") == u"hello world");
    Check(Text(u"/shutdown") == u"/shutdown"); // Plain chat, never command execution.
    Check(Text(u"<Admin> & hi") == u"<Admin> & hi"); // Plain UTextBlock, never rich markup.
    Check(Text(u"a\u202e\u2066b\u2069\u200bc") == u"abc");
    Check(Text(u"\u65e5\u672c\u8a9e \u0627\u0644\u0639\u0631\u0628\u064a\u0629") == u"\u65e5\u672c\u8a9e \u0627\u0644\u0639\u0631\u0628\u064a\u0629");
    Check(Text(u"a\U0001f600", 2) == u"a");
    Check(Text(u"a\U0001f600", 3) == u"a\U0001f600");
    Check(Text(u"ab c",3) == u"ab");
    Check(Text(std::u16string(10000,u' ')+u'x').empty());
    for (int Limit=-2; Limit<=514; ++Limit)
    {
        const int Clamped=Limit<1 ? 1 : Limit>512 ? 512 : Limit;
        auto Result=Text(std::u16string(1000,u'x'),Limit);
        Check(static_cast<int>(Result.size())==Clamped);
        Check(Result==Text(Result,Limit));
    }
    std::cout << Checks << " world chat core checks passed\n";
}
