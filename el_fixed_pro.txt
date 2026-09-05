#include <bits/stdc++.h>
using namespace std;

#define int long long

// Iterative Extended Euclidean Algorithm
int egcd(int a, int b, int &x, int &y) {
    x = 1;
    y = 0;
    int x1 = 0, y1 = 1;

    while (b != 0) {
        int q = a / b;

        int temp = a;
        a = b;
        b = temp % b;

        temp = x;
        x = x1;
        x1 = temp - q * x1;

        temp = y;
        y = y1;
        y1 = temp - q * y1;
    }

    return a;
}

// Fast Modular Exponentiation
int mod_pow(int a, int e, int m) {
    int r = 1;
    a %= m;

    while (e > 0) {
        if (e & 1)
            r = (__int128)r * a % m;

        a = (__int128)a * a % m;
        e >>= 1;
    }

    return r;
}

// Modular Inverse
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

    // Fixed ElGamal parameters
    int p = 467;
    int alpha = 2;
    int a = 123;

    int beta = mod_pow(alpha, a, p);

    cout << "Public Key (p, alpha, beta): ("
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

    // Encrypt first message
    int C11 = mod_pow(alpha, r1, p);
    int C12 = (m1 * mod_pow(beta, r1, p)) % p;

    // Encrypt second message
    int C21 = mod_pow(alpha, r2, p);
    int C22 = (m2 * mod_pow(beta, r2, p)) % p;

    cout << "\nCiphertext of m1: (" << C11 << ", " << C12 << ")\n";
    cout << "Ciphertext of m2: (" << C21 << ", " << C22 << ")\n";

    // Homomorphic multiplication
    int C1p = (C11 * C21) % p;
    int C2p = (C12 * C22) % p;

    cout << "\nCombined Cipher (C1', C2'): ("
         << C1p << ", " << C2p << ")\n";

    // Decrypt combined ciphertext
    int s = mod_pow(C1p, a, p);
    int s_inv = modinv(s, p);
    int m_dec = (C2p * s_inv) % p;

    cout << "\nDecrypted Message = " << m_dec << endl;
    cout << "Expected = " << (m1 * m2) % p << endl;

    return 0;
}