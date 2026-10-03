#include<bits/stdc++.h>
using namespace std;
#define int long long


int mod_pow(int val,int pow,int mod){
    int ans=1;
    while(pow){
        if(pow%2) ans=(ans*val)%mod;
        val=(val*val)%mod;
        pow/=2;
    }
    return ans;
}

int mod_inv(int a,int mod){
    for(int i=1;i<mod;i++){
        if((a*i)%mod==1){
            return i;
        }
    }
    return -1;
}

signed main(){
    int prime=97;
    // primitive element
    int alpha=-1;
    for(int i=2;i<prime;i++){
        set<int>ms;
        for(int j=0;j<prime-1;j++){
            int val=mod_pow(i,j,prime);
            ms.insert(val);
        }
        if(ms.size()==(prime-1)){
            cout<<i<<endl;
            alpha=i;
            break;
        }
    }
    int d=5;
    int beta=mod_pow(alpha,d,prime);
    int msg=11;
    int rand;
    cout<<"give a rand";
    cin>>rand;

    int inv=mod_inv(rand,prime-1);
    while(inv==-1){
            cout<<"give valid  rand";
            cin>>rand;
            inv=mod_inv(rand,prime-1);
    }
        int y1=mod_pow(alpha,rand,prime);
    int y2=(inv*((msg-y1*d)))%(prime-1);
    if(y2<0) y2+=prime-1;
   

    int l=mod_pow(alpha,msg,prime);
    int r=(mod_pow(beta,y1,prime)*(mod_pow(y1,y2,prime)))%prime;

    cout<<l<<" hehe  "<<r<<endl;
    cout<<"farhan bokachoda"<<endl;
}
