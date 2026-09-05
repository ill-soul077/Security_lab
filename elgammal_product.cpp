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

// Find prime factors of n
vector<int> primeFactors(int n) {
    vector<int> f;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            f.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }

    if (n > 1)
        f.push_back(n);

    return f;
}

// Find primitive root of prime p
int primitiveRoot(int p) {
    vector<int> factors = primeFactors(p - 1);

    for (int g = 2; g < p; g++) {
        bool ok = true;

        for (int q : factors) {
            if (mod_pow(g, (p - 1) / q, p) == 1) {
                ok = false;
                break;
            }
        }

        if (ok)
            return g;
    }

    return -1;
}

signed main() {

    int p, a;

    cout << "Enter a 3 or 4 digit prime number (p): ";
    cin >> p;

    int alpha = primitiveRoot(p);

    cout << "Primitive Root (alpha) = " << alpha << endl;

    cout << "Enter private key (a): ";
    cin >> a;

    int beta = mod_pow(alpha, a, p);

    cout << "\nPublic Key (p, alpha, beta): ("
         << p << ", " << alpha << ", " << beta << ")\n";
    cout << "Private Key a = " << a << "\n";

    int m1, m2, r1, r2;

    cout << "\nEnter first message (m1): ";
    cin >> m1;

    cout << "Enter second message (m2): ";
    cin >> m2;

    cout << "Enter random value r1: ";
    cin >> r1;

    cout << "Enter random value r2: ";
    cin >> r2;

    // Encrypt m1
    int C11 = mod_pow(alpha, r1, p);
    int C12 = (m1 * mod_pow(beta, r1, p)) % p;

    // Encrypt m2
    int C21 = mod_pow(alpha, r2, p);
    int C22 = (m2 * mod_pow(beta, r2, p)) % p;

    cout << "\nCiphertext of m1: (" << C11 << ", " << C12 << ")\n";
    cout << "Ciphertext of m2: (" << C21 << ", " << C22 << ")\n";

    // Homomorphic multiplication
    int C1p = (C11 * C21) % p;
    int C2p = (C12 * C22) % p;

    cout << "\nCombined Cipher (C1', C2'): ("
         << C1p << ", " << C2p << ")\n";

    // Decryption
    int s = mod_pow(C1p, a, p);
    int s_inv = modinv(s, p);
    int m_dec = (C2p * s_inv) % p;

    cout << "\nDecrypted Message = " << m_dec << endl;
    cout << "Expected = " << (m1 * m2) % p << endl;

    return 0;
}