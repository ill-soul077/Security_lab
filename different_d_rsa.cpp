#include<bits/stdc++.h>
using namespace std;
#define int long long
#define int128 __int128

int mod_pow(int a, int e, int m) {
    int r = 1; a %= m;
    while (e) {
        if (e & 1) r = (int128)r * a % m;
        a = (int128)a * a % m;
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
    int p, q;
    cout << "Enter prime p and q: ";
    cin >> p >> q;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    cout << "n = " << n << ", phi = " << phi << "\n";
    int e;
    cout << "Enter public exponent e (0 for auto): ";
    cin >> e;
    if (e == 0) {
        e = 2;
        while (__gcd(e, phi) != 1) ++e;
        cout << "Auto-selected e = " << e << "\n";
    } else if (__gcd(e, phi) != 1) {
        cout << "e and phi(n) not coprime.\n";
        return 0;
    }
    int d = modinv(e, phi);
    cout << "Private exponent d = " << d << "\n";
    vector<int> dd;
    for (int k = 1; k < phi; ++k) {
        if ((1 + k * phi) % e == 0) {
            int d_cand = (1 + k * phi) / e;
            dd.push_back(d_cand);
            if ((int)dd.size() >= 8) break;
        }
    }
    cout << "Candidate d values: ";
    for (int v : dd) cout << v << " ";
    cout << "\n";
    int m;
    cout << "Enter plaintext m: ";
    cin >> m;
    int c = mod_pow(m, e, n);
    cout << "Ciphertext c = " << c << "\n";
    for (int i = 1; i <= phi; ++i) {
        if (mod_pow(c, i, n) == m) {
            cout << "Found exponent i = " << i << " (possible d)\n";
            break;
        }
    }
    cout << "Decrypted: " << mod_pow(c, d, n) << "\n";
}