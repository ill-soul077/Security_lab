#include<bits/stdc++.h>
using namespace std;
#define int long long



int mod_pow(int val,int po,int mod){
    int ans=1;
    val%=mod;
    while(po){
        if(po%2) ans=ans*val%mod;

        val=(val*val)%mod;

        po/=2;

    }
    return ans;
}

int modinv(int val,int mod){
    return mod_pow(val,mod-2,mod);
}
signed main() {
    int p = 467;
    int alpha = 2;
    int a = 123;

    int rand=5;
    int beta=mod_pow(alpha,a,p);
    int m;
    cout<<"message ";cin>>m;
    int C1=mod_pow(alpha,rand,p);
    int C2=m*mod_pow(beta,rand,p);

    int r2;
    cout<<"new rand"; cin>>r2;
    int C1_new=C1*mod_pow(alpha,r2,p)%p;
    int C2_new=C2*mod_pow(beta,r2,p)%p;

    cout<<"Rerandcomized"<<C1_new<<" : "<<C2_new<<endl;

    int s=mod_pow(C1_new,a,p)%p;
    int dec=C2_new*modinv(s,p)%p;

    cout<<dec<<endl;

}