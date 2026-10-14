#include "../Source/DigimonVenomNXTRuntime/Public/DigimonVenomNXTServerConsoleCore.h"
#include <iostream>
#include <cassert>
using namespace DigimonVenomNXTServerConsoleCore;
int main()
{
    int Count=0;
    // Every gate is independently required. Server-side remote controllers still have authority.
    for(int Bits=0;Bits<512;++Bits)
    {
        const bool Result=Authorized(Bits&1,Bits&2,Bits&4,Bits&8,Bits&16,Bits&32,Bits&64,Bits&128,Bits&256);
        assert(Result==(Bits==511));++Count;
    }
    std::int64_t N=77;
    assert(UnsignedDecimal("9223372036854775807",INT64_MAX,N)&&N==INT64_MAX);++Count;
    for(const auto* Bad:{"9223372036854775808","18446744073709551616","-1","+1","1e3","1.5"," 1","1 ","","0x10","9999999999999999999999999999999999999999"})
    {N=77;assert(!UnsignedDecimal(Bad,INT64_MAX,N)&&N==77);++Count;}
    assert(UnsignedDecimal("0",0,N)&&N==0);++Count;
    assert(!UnsignedDecimal("1",0,N));++Count;
    assert(UnsignedDecimal("0000100",100,N)&&N==100);++Count;
    assert(!UnsignedDecimal("101",100,N));++Count;
    assert(AddWithin(9000000000000LL-1,1,9000000000000LL,N)&&N==9000000000000LL);++Count;
    assert(!AddWithin(9000000000000LL,1,9000000000000LL,N));++Count;
    assert(!AddWithin(-1,10,100,N));++Count;
    assert(!AddWithin(INT64_MAX,1,INT64_MAX,N));++Count;
    assert(ActiveUntil(-1,100));++Count;
    assert(!ActiveUntil(100,100));++Count;
    assert(ActiveUntil(101,100));++Count;
    assert(!ActiveUntil(0,100));++Count;
    std::vector<std::string> Tokens;std::string Error;
    assert(Tokenize("/givedigimon \"Player One\" \"Digi \\\"Prime\\\"\" 100 firewall",Tokens,Error));
    assert(Tokens.size()==5&&Tokens[1]=="Player One"&&Tokens[2]=="Digi \"Prime\"");++Count;
    assert(Tokenize("  /settitle   Player  \"Relay Champion\"  ",Tokens,Error)&&Tokens.size()==3);++Count;
    assert(Tokenize("/broadcast \"C:\\\\Games\"",Tokens,Error)&&Tokens[1]=="C:\\Games");++Count;
    for(const std::string& Bad:std::vector<std::string>{"/warn p \"unfinished","/warn p \"bad\\q\"","/players\n/shutdown","/players\r/ban","/players\t/ban","   ",std::string(1025,'a'),"/x 1 2 3 4 5 6 7 8 9 10 11 12","/x "+std::string(513,'a')})
    {assert(!Tokenize(Bad,Tokens,Error)&&!Error.empty());++Count;}
    assert(Tokenize("/broadcast \"slash /shutdown is literal text\"",Tokens,Error)&&Tokens.size()==2);++Count;
    assert(Tokenize("/broadcast \"; rm -rf x && y\"",Tokens,Error)&&Tokens.size()==2);++Count;
    // Parser accepts text only; executable command routing is the explicit registry, never a shell.
    int Candidate=25,Live=10,SaveCalls=0,PublishCalls=0;
    assert(!Commit(Candidate,[&](int& Value){++SaveCalls;assert(Value==25);return false;},[&](int& Value){++PublishCalls;Live=Value;}));
    assert(Live==10&&SaveCalls==1&&PublishCalls==0);++Count;
    assert(Commit(Candidate,[&](int& Value){++SaveCalls;assert(Value==25);return true;},[&](int& Value){++PublishCalls;Live=Value;}));
    assert(Live==25&&SaveCalls==2&&PublishCalls==1);++Count;
    assert(ConfirmationAllowed(true,true,10,30,true));++Count;
    assert(!ConfirmationAllowed(false,true,10,30,true));++Count;
    assert(!ConfirmationAllowed(true,false,10,30,true));++Count;
    assert(!ConfirmationAllowed(true,true,31,30,true));++Count;
    assert(!ConfirmationAllowed(true,true,10,30,false));++Count;
    std::cout<<Count<<" native console parser/authority/numeric checks passed\n";
}
