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

signed main(){
    int prime=17;
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
    int c1=mod_pow(alpha,rand,prime);
    int c2=(msg*mod_pow(beta,rand,prime))%prime;

    int s=mod_pow(c1,d,prime);
    int inv=mod_pow(s,prime-2,prime);
    int dec=(c2*inv)%prime;
    cout<<dec<<endl;
    cout<<"farhan bokachoda"<<endl;
}
