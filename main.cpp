#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
using namespace std;
vector<int> dec2bin(int num){
    vector<int>arr;
    string binary;
    while (num>0){
        arr.push_back((num%2));
        num/=2;
    }
    return arr;
}
ll negMod(ll a, ll b){
    return (a % b + b) % b;
}
ll squareAndMultiply( ll x,  ll H,  ll n){
    long long r;
    vector<int>bin=dec2bin((int)H);
    int i=(int)bin.size();
    r = 1;
    while(i>0){
        r = (r * r) % n;
        if( bin[--i] == 1 ){
            r = (r * x) % n;
        }
    }
    return r;
}
int random(int begin, int end){
    vector<int>randVectorForPrimality;
    for (int i = begin; i < end; ++i) {
        randVectorForPrimality.push_back(i);
    }
    random_shuffle(randVectorForPrimality.begin(),randVectorForPrimality.end());
    return randVectorForPrimality[0];
}
bool fermat(int s,int p){
    for (int i = 1; i <= s; ++i) {
        int a = random(2,p-2);
        if (squareAndMultiply(a,p-1,p)!=1)
            return false;
    }
    return true;
}
ll getE(ll phi){
    for(ll i=2;i<phi;i++)
        if (__gcd(i,phi)==1)
            return i;
    return 0;
}
ll EEA(ll r0,ll r1){
    int s0=1,s1=0,t0=0,t1=1,i=1;
    vector<ll>r;
    vector<ll>s;
    vector<ll>t;
    r.push_back(r0);r.push_back(r1);s.push_back(s0);s.push_back(s1);t.push_back(t0);t.push_back(t1);
    do {
        i++;
        r.push_back(r[i-2]%r[i-1]);
        ll q = (r[i-2]-r[i])/r[i-1];
        s.push_back((s[i-2])-q*s[i-1]);
        t.push_back((t[i-2])-q*t[i-1]);

    }
    while(r[i]!=0);
    ll size = (ll)t.size();
    return t[size-2]<0? negMod(t[size-2],r0):t[size-2];
}
ll CRT(ll x,ll d,ll p,ll q,ll n){
    ll xp = x%p;
    ll xq = x%q;
    ll dp = d%(p-1);
    ll dq = d%(q-1);
    ll yp = squareAndMultiply(xp,dp,p);
    ll yq = squareAndMultiply(xq,dq,q);
    ll cp = EEA(p,q)%p;
    ll cq = EEA(q,p)%q;
    return ((q*cp)*yp + (p*cq)*yq)%n;
}
int main() {
    srand((unsigned)time(nullptr));
    string plainText;
    getline(cin,plainText);
    int plainTextSize=(int)plainText.size();
    ll p,q;
    while (true) {
        p = rand();
        if(fermat(100,p))
            break;
    }
    while(true) {
        q = rand();
        if (fermat(100, q))
            break;
    }
    ll n = p*q;
    ll phi = (p-1)*(q-1);
    ll e = getE(phi);
    ll invE=EEA(phi,e);
    ll d = invE%phi;
    string decrypted;
    vector<ll>v;
    cout<<"p:"<<p<<",q:"<<q<<endl;
    cout<<"e:"<<e<<",d:"<<d<<endl;
    for (int i = 0; i < plainTextSize; ++i) {
        cout<<"Character:"<<plainText[i]<<",ASCII:"<<(int)plainText[i]<<endl;
        ll cipherText = squareAndMultiply((long)plainText[i],e,n);
        v.push_back(cipherText);
        cout<<"y("<<plainText[i]<<")="<<cipherText<<endl;
    }
    int sz = (int)v.size();
    for(int i =0;i<sz;i++){
        decrypted+=(char)CRT(v[i],d,p,q,n);
        cout<<"x("<<v[i]<<")="<<(char)CRT(v[i],d,p,q,n)<<endl;
    }
    cout<<"the decryped is = "<<decrypted<<endl;

    return 0;
}
