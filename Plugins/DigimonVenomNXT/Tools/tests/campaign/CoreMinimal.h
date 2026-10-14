#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdarg>
#include <string>
#include <vector>
#include <map>
#include <set>
#define GENERATED_BODY()
#define UPROPERTY(...)
#define UMETA(...)
#if defined(_MSC_VER)
#define FORCENOINLINE __declspec(noinline)
#else
#define FORCENOINLINE __attribute__((noinline))
#endif
#define DIGIMONVENOMNXTRUNTIME_API
#define TEXT(x) L##x
#define check(x) assert(x)
#define checkf(x, ...) assert(x)
#define MoveTemp(x) std::move(x)
using int32=int32_t; using int64=int64_t; using uint8=uint8_t; using TCHAR=wchar_t;
struct FString {
 std::wstring S;
 FString()=default; FString(const wchar_t* s):S(s){} FString(std::wstring s):S(std::move(s)){}
 const wchar_t* operator*() const {return S.c_str();}
 bool IsEmpty() const{return S.empty();} void Reset(){S.clear();}
 int32 Len() const{return static_cast<int32>(S.size());} FString Mid(int32 Start)const{return S.substr(Start);}
 bool Contains(const wchar_t* s)const{return S.find(s)!=S.npos;}
 friend bool operator==(const FString&a,const FString&b){return a.S==b.S;}
 friend bool operator!=(const FString&a,const FString&b){return !(a==b);}
 friend bool operator<(const FString&a,const FString&b){return a.S<b.S;}
 friend FString operator+(const FString&a,const FString&b){return a.S+b.S;}
 static FString Printf(const wchar_t* f,...){return f;}
};
struct FName: FString {
 using FString::FString; FName()=default;
 bool IsNone() const{return S.empty()||S==L"None";}
 FString ToString() const{return S;}
};
inline const FName NAME_None;
template<class T> struct TArray: std::vector<T>{
 using std::vector<T>::vector; using std::vector<T>::operator=;
 int Num()const{return this->size();} bool IsEmpty()const{return this->empty();}
 bool IsValidIndex(int n)const{return n>=0&&n<Num();}
 void Add(const T&v){this->push_back(v);} void Add(T&&v){this->push_back(std::move(v));}
 bool Contains(const T&v)const{return std::find(this->begin(),this->end(),v)!=this->end();}
 void AddUnique(const T&v){if(!Contains(v))Add(v);}
 template<class F>const T* FindByPredicate(F f)const{for(const auto&v:*this)if(f(v))return &v;return nullptr;}
 template<class F>TArray FilterByPredicate(F f)const{TArray o;for(const auto&v:*this)if(f(v))o.Add(v);return o;}
 template<class F>void RemoveAll(F f){this->erase(std::remove_if(this->begin(),this->end(),f),this->end());}
};
template<class K,class V>struct TMap:std::map<K,V>{
 void Add(const K&k,const V&v){(*this)[k]=v;}
 const V*Find(const K&k)const{auto i=this->find(k);return i==this->end()?nullptr:&i->second;}
 V FindRef(const K&k)const{auto p=Find(k);return p?*p:V();}
};
template<class K>struct TSet:std::set<K>{bool Contains(const K&k)const{return this->count(k)>0;}void Add(const K&k){this->insert(k);}};
struct FVector2D {double X=0,Y=0;FVector2D()=default;FVector2D(double x,double y):X(x),Y(y){}static const FVector2D ZeroVector;};
inline const FVector2D FVector2D::ZeroVector;
struct FVector {double X=0,Y=0,Z=0;static const FVector ZeroVector;};
inline const FVector FVector::ZeroVector;
inline std::wstring CampaignASCIIToWide(const char* Value){return std::wstring(Value,Value+std::char_traits<char>::length(Value));}
#define UTF8_TO_TCHAR(x) CampaignASCIIToWide(x).c_str()
struct FTCHARToUTF8 {std::string Value; explicit FTCHARToUTF8(const wchar_t* Text){while(*Text)Value.push_back(static_cast<char>(*Text++));}const char*Get()const{return Value.c_str();}int32 Length()const{return static_cast<int32>(Value.size());}};
struct FMath {template<class T>static T Clamp(T x,T a,T b){return std::clamp(x,a,b);}template<class T>static T Max(T a,T b){return std::max(a,b);}};
struct FGuid {int n=0;static FGuid NewGuid(){static int n=0;return {++n};}bool IsValid()const{return n>0;}void Invalidate(){n=0;}friend bool operator==(FGuid a,FGuid b){return a.n==b.n;}friend bool operator!=(FGuid a,FGuid b){return !(a==b);}};
