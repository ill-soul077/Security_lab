#include <bits/stdc++.h>
using namespace std;
#define int long long
#define int128 __int128

int mulMod(int a, int b, int m) {
    return (int)((int128)a * b % m);
}

int modPow(int a, int e, int m) {
    int r = 1;
    a = a % m;

    while (e > 0) {
        if (e % 2 == 1) {
            r = mulMod(r, a, m);
        }
        a = mulMod(a, a, m);
        e /= 2;
    }

    return r;
}

int modInv(int e, int phi) {
    int a = e, b = phi;
    int x0 = 1, x1 = 0;

    while (b != 0) {
        int q = a / b;
        a -= q * b;
        swap(a, b);
        x0 -= q * x1;
        swap(x0, x1);
    }

    if (x0 < 0) {
        x0 += phi;
    }

    return x0;
}

signed main() {
    int p = 61, q = 53;
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int e = 17;
    int d = modInv(e, phi);

    cout << "Public key (n, e): (" << n << ", " << e << ")\n";
    cout << "Private key (d): " << d << "\n";

    int m1 = 65, m2 = 77;
    int c1 = modPow(m1, e, n);
    int c2 = modPow(m2, e, n);
    cout << "Enc(m1)=" << c1 << " Enc(m2)=" << c2 << "\n";

    int cProd = mulMod(c1, c2, n);
    cout << "Combined ciphertext = " << cProd << "\n";

    int dec = modPow(cProd, d, n);
    cout << "Decrypted product: " << dec << " (expected " << (m1 * m2) % n << ")\n";

    return 0;
}
