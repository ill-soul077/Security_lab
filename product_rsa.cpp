#include<bits/stdc++.h>
using namespace std;
#define int long long
#define int128 __int128

int mul_mod(int a, int b, int m) {
    return (int)((int128)a * b % m);
}
int mod_pow(int a, int e, int m) {
    int r = 1; a %= m;
    while (e) {
        if (e & 1) r = mul_mod(r, a, m);
        a = mul_mod(a, a, m);
        e >>= 1;
    }
    return r;
}
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
signed main() {
    int p = 61, q = 53;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 17;
    int d = modinv(e, phi);
    cout << "Public key (n, e): (" << n << ", " << e << ")\n";
    cout << "Private key (d): " << d << "\n";
    int m1 = 65, m2 = 77;
    int c1 = mod_pow(m1, e, n), c2 = mod_pow(m2, e, n);
    cout << "Enc(m1)=" << c1 << " Enc(m2)=" << c2 << "\n";
    int cprod = mul_mod(c1, c2, n);
    cout << "Combined ciphertext = " << cprod << "\n";
    int dec = mod_pow(cprod, d, n);
    cout << "Decrypted product: " << dec << " (expected " << (m1 * m2) % n << ")\n";
}