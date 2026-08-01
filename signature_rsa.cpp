#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int64 modPow(int64 a, int64 e, int64 m) {
    int64 r = 1;
    a = a % m;

    while (e > 0) {
        if (e % 2 == 1) {
            r = (__int128)r * a % m;
        }
        a = (__int128)a * a % m;
        e /= 2;
    }

    return r;
}

int64 egcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int64 x1, y1;
    int64 g = egcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

int64 modInv(int64 a, int64 m) {
    int64 x, y;
    egcd(a, m, x, y);

    x = x % m;
    if (x < 0) {
        x += m;
    }

    return x;
}

int main() {
    int64 p = 61, q = 53;
    int64 n = p * q;
    int64 phi = (p - 1) * (q - 1);

    int64 e = 17;
    int64 d = modInv(e, phi);

    cout << "Public key (n, e): (" << n << ", " << e << ")" << endl;
    cout << "Private key d: " << d << endl;

    int64 m;
    cout << "Enter message (integer): ";
    cin >> m;

    int64 s = modPow(m, d, n);
    cout << "Signature: " << s << endl;

    int64 v = modPow(s, e, n);
    cout << "Verification result: " << v;

    if (v == m) {
        cout << " -> Valid" << endl;
    } else {
        cout << " -> Invalid" << endl;
    }

    return 0;
}
