#include <bits/stdc++.h>
using namespace std;

#define int long long

int egcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int g = egcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

int mod_pow(int a, int e, int m) {
    int r = 1;
    a %= m;

    while (e) {
        if (e & 1)
            r = (__int128)r * a % m;

        a = (__int128)a * a % m;
        e >>= 1;
    }

    return r;
}

int modinv(int a, int m) {
    int x, y;
    int g = egcd(a, m, x, y);

    if (g != 1)
        return -1;

    x %= m;
    if (x < 0)
        x += m;

    return x;
}

signed main() {

    int p, alpha, a;

    cout << "Enter a 3 or 4 digit prime number (p): ";
    cin >> p;

    cout << "Enter primitive root (alpha): ";
    cin >> alpha;

    cout << "Enter private key (a): ";
    cin >> a;

    int beta = mod_pow(alpha, a, p);

    cout << "\nPublic Key (p, alpha, beta): ("
         << p << ", " << alpha << ", " << beta << ")\n";
    cout << "Private Key a = " << a << "\n";

    int m, r;

    cout << "\nEnter message (m < p): ";
    cin >> m;

    cout << "Enter random value r: ";
    cin >> r;

    int C1 = mod_pow(alpha, r, p);
    int C2 = (m * mod_pow(beta, r, p)) % p;

    cout << "\nOriginal Cipher (C1, C2): ("
         << C1 << ", " << C2 << ")\n";

    int r2;
    cout << "Enter another random value r2 (for re-randomization): ";
    cin >> r2;

    int C1_new = (C1 * mod_pow(alpha, r2, p)) % p;
    int C2_new = (C2 * mod_pow(beta, r2, p)) % p;

    cout << "\nRe-randomized Cipher (C1', C2'): ("
         << C1_new << ", " << C2_new << ")\n";

    int s = mod_pow(C1_new, a, p);
    int s_inv = modinv(s, p);
    int m_dec = (C2_new * s_inv) % p;

    cout << "\nDecrypted Message = " << m_dec << endl;
    cout << "Expected Message = " << m << endl;

    return 0;
}