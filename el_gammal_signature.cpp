#include <bits/stdc++.h>
using namespace std;

#define int long long

// Fast Modular Exponentiation
int mod_pow(int a, int e, int m)
{
    int r = 1;
    a %= m;

    while (e > 0)
    {
        if (e & 1)
            r = (__int128)r * a % m;

        a = (__int128)a * a % m;
        e >>= 1;
    }

    return r;
}

// Extended Euclidean Algorithm
int egcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
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

// Modular Inverse
int modinv(int a, int m)
{
    int x, y;
    int g = egcd(a, m, x, y);

    if (g != 1)
        return -1;

    x %= m;
    if (x < 0)
        x += m;

    return x;
}

signed main()
{
    // Fixed ElGamal parameters
    int p = 467;
    int alpha = 5;
    int a = 123;

    int beta = mod_pow(alpha, a, p);

    cout << "Public Key (p, alpha, beta): ("
         << p << ", " << alpha << ", " << beta << ")\n";
    cout << "Private Key a = " << a << "\n";

    int M;
    cout << "\nEnter message (integer): ";
    cin >> M;

    int r = 7;

    if (__gcd(r, p - 1) != 1)
    {
        cout << "r is not coprime to p-1.\n";
        return 0;
    }

    // Signature Generation
    int y1 = mod_pow(alpha, r, p);
    int r_inv = modinv(r, p - 1);

    int y2 = (r_inv * (M - a * y1)) % (p - 1);
    if (y2 < 0)
        y2 += (p - 1);

    cout << "\nSignature (y1, y2): ("
         << y1 << ", " << y2 << ")\n";

    // Signature Verification
    int left = mod_pow(alpha, M, p);
    int right = (__int128)mod_pow(beta, y1, p) * mod_pow(y1, y2, p) % p;

    cout << "\nVerification: ";

    if (left == right)
        cout << "Signature VALID\n";
    else
        cout << "Signature INVALID\n";

    return 0;
}