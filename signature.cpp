#include<bits/stdc++.h>
using namespace std;
#define int long long
#define int128 __int128

int modpow(int base, int exp, int mod){
    int res = 1;
    base %= mod;
    while(exp > 0){
        if(exp & 1) res = (int128)res * base % mod;
        base = (int128)base * base % mod;
        exp >>= 1;
    }
    return res;

}

// int modpow(int base,int exp,int mod){
//     int res=1;
//     base%=mod;
//     while(exp>0){
//         if(exp&1) res=(int128)res*base%mod;
//         base=(int128)base*base% mod;
//         exp>>=1;
//     }
//     return res;
// }

int modinv(int e, int phi){
    int a = e, b = phi, x0 = 1, x1 = 0;
    while(b != 0){
        int q = a / b;
        a -= q * b; swap(a, b);
        x0 -= q * x1; swap(x0, x1);
    }
    if(x0 < 0) x0 += phi;
    return x0;
}

int modiv(int e,int phi){
    int a=e,b=phi,x0=1,x1=0;
    while(b!=0){
        int q=a/b;
        a-=q*b;swap(a,b);
        x0-=q*x1; swap(x0,x1);
    }
    if(x0<x1) x0+=phi;
    return x0;
}

signed main(){       // <-- signed, not int, because of the macro
    int p = 11, q = 3;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 7;
    int d = modinv(e, phi);

    cout << "n=" << n << " phi=" << phi << " d=" << d << "\n";

    int msg = 7;
    int enc = modpow(msg, e, n);
    int dec = modpow(enc, d, n);

    cout << "msg=" << msg << " enc=" << enc << " dec=" << dec << "\n";
}