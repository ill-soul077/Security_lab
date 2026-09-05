#include<bits/stdc++.h>
using namespace std;
#define int long long


int mod_pow(int val,int pow,int mod){
    int ans=1;
    val%=mod;
    while(pow){
        if(pow%2) ans=(ans*val)%mod;
        val=(val*val) %mod;
        pow/=2;
    }

    return ans;
}

int modinv(int val,int mod){
    return mod_pow(val,mod-2,mod);
}


signed main(){
    int p=467;
    int alpha=2;
    int a=123;


    int beta=mod_pow(alpha,a,p);

    int m1,m2,r1,r2;
    cin>>m1>>m2;
    cin>>r1>>r2;

    int c11=mod_pow(alpha,r1,p);
    int c12=(m1*mod_pow(beta,r1,p))%p;


    int c21=mod_pow(alpha,r2,p);
    int c22=(m2*mod_pow(beta,r2,p))%p;

    int c1p=(c11*c21)%p;
    int c2p=(c12*c22)%p;

    int s=mod_pow(c1p,a,p);
    int dec=c2p*mod_pow(s,p-2,p)%p;

    cout<<dec<<endl;
}