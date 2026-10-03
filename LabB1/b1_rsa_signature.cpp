#include<bits/stdc++.h>
using namespace std;
#define int long long


// int mod_inv(int a,int mod){
//     for(int i=1;i<mod;i++){
//         if((a*i)%mod==1){
//             return i;
//         }
//     }
//     return -1;
// }


// int egcd(int a,int b,int &x,int &y){
//     if(b==0){
//         x=1;
//         y=0;
//         return a;
//     }

//     int x1,y1;
//     int g=egcd(b,a%b,x1,y1);

//     x=y1;
//     y=x1-(a/b)*y1;

//     return g;
// }

// int mod_inv(int a,int mod){
//     int x,y;
//     int g=egcd(a,mod,x,y);

//     if(g!=1) return -1;

//     return (x%mod+mod)%mod;

// }






int egcd(int a,int b,int &x,int &y){

    if(b==0){
        x=1;
        y=0;
        return a;
    }
    int x1,y1;
    int g=egcd(b,a%b,x1,y1);

    x=y1;
    y=x1-(a/b)*y1;

    return g;

}








int mod_inv(int a,int mod){
    int x,y;
    int g=egcd(a,mod,x,y);

    if(g!=1) return -1;

    return (x%mod+mod)%mod;
}

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
    int p=97,q=101;
    int n=p*q;
    int phi=(p-1)*(q-1);
    int e=-1;
    for(int i=2;i<phi;i++){
        if(__gcd(i,phi)==1){
            e=i;
            break;
        }
    }

    int d=mod_inv(e,phi);

    int msg=10;
    int sign=mod_pow(msg,d,n);

    cout<<"Signature : "<<sign<<endl;
    int veri=mod_pow(sign,e,n);
    cout<<"Verification : "<<veri<<endl;
}
