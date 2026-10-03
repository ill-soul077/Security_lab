#include<bits/stdc++.h>
using namespace std;
#define int long long


// COMMON FUNCTIONS
// These examples use small lab values so products fit in long long.
// mod must be positive; exponents must be nonnegative.
int modd(int val,int mod){
    val%=mod;
    if(val<0) val+=mod;
    return val;
}

int mod_pow(int val,int pow,int mod){
    val=modd(val,mod);
    int ans=1%mod;
    while(pow){
        if(pow%2) ans=(ans*val)%mod;
        val=(val*val)%mod;
        pow/=2;
    }
    return ans;
}

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

// Works for prime and composite moduli; -1 means no inverse.
int mod_inv(int a,int mod){
    if(mod<=1) return -1;
    int x,y;
    int g=egcd(modd(a,mod),mod,x,y);
    if(g!=1) return -1;
    return modd(x,mod);
}

// Fermat inverse: mod must be prime and a must be nonzero modulo mod.
int mod_inv_prime(int a,int mod){
    a=modd(a,mod);
    if(a==0) return -1;
    return mod_pow(a,mod-2,mod);
}


// RSA: p and q must be distinct primes.
int rsa_choose_e(int phi){
    for(int i=2;i<phi;i++){
        if(__gcd(i,phi)==1) return i;
    }
    return -1;
}

int rsa_enc(int msg,int e,int n){
    return mod_pow(msg,e,n);
}

int rsa_dec(int enc,int d,int n){
    return mod_pow(enc,d,n);
}

// Decrypting this gives (m1*m2) % n.
int rsa_product(int c1,int c2,int n){
    return modd(c1*c2,n);
}

int rsa_sign(int msg,int d,int n){
    return mod_pow(msg,d,n);
}

bool rsa_verify(int msg,int sign,int e,int n){
    return mod_pow(sign,e,n)==modd(msg,n);
}


// ELGAMAL: prime must be prime; alpha is a primitive element.
int primitive_element(int prime){
    for(int i=1;i<prime;i++){
        set<int>ms;
        for(int j=0;j<prime-1;j++){
            ms.insert(mod_pow(i,j,prime));
        }
        if((int)ms.size()==prime-1) return i;
    }
    return -1;
}

// beta = alpha^d % prime; k is the random exponent.
// Ciphertext is {c1,c2}.
pair<int,int> el_enc(int msg,int alpha,int beta,int k,int prime){
    int c1=mod_pow(alpha,k,prime);
    int c2=modd(modd(msg,prime)*mod_pow(beta,k,prime),prime);
    return {c1,c2};
}

int el_dec(pair<int,int> c,int d,int prime){
    int s=mod_pow(c.first,d,prime);
    int inv=mod_inv_prime(s,prime);
    if(inv==-1) throw invalid_argument("Invalid ElGamal ciphertext");
    return modd(c.second*inv,prime);
}

// Decrypting this gives (m1*m2) % prime.
pair<int,int> el_product(pair<int,int> c,pair<int,int> q,int prime){
    return {modd(c.first*q.first,prime),modd(c.second*q.second,prime)};
}

// Multiply by a fresh encryption of 1; decrypted message stays the same.
pair<int,int> el_rrand(pair<int,int> c,int alpha,int beta,int k,int prime){
    return el_product(c,el_enc(1,alpha,beta,k,prime),prime);
}

// Signature is {y1,y2}; k must be coprime to prime-1.
pair<int,int> el_sign(int msg,int alpha,int d,int k,int prime){
    int inv=mod_inv(k,prime-1);
    if(inv==-1) throw invalid_argument("Signature k has no inverse");
    int y1=mod_pow(alpha,k,prime);
    int y2=modd(inv*modd(msg-y1*d,prime-1),prime-1);
    return {y1,y2};
}

bool el_verify(int msg,pair<int,int> sign,int alpha,int beta,int prime){
    int y1=sign.first,y2=sign.second;
    if(y1<=0 || y1>=prime || y2<0 || y2>=prime-1) return false;
    int l=mod_pow(alpha,msg,prime);
    int r=modd(mod_pow(beta,y1,prime)*mod_pow(y1,y2,prime),prime);
    return l==r;
}


// ECC: y^2 = x^3 + a*x + b (mod prime).
// Use valid curve points with normalized coordinates and an odd prime.
struct point{
    int x,y;
    bool inf;
};

point point_add(point p,point q,int mod,int a){
    if(p.inf) return q;
    if(q.inf) return p;
    if(p.x==q.x && modd(p.y+q.y,mod)==0) return {0,0,true};

    int up,down;
    if(p.x==q.x && p.y==q.y){
        up=modd(3*p.x*p.x+a,mod);
        down=modd(2*p.y,mod);
    }else{
        up=modd(q.y-p.y,mod);
        down=modd(q.x-p.x,mod);
    }

    int inv=mod_inv_prime(down,mod);
    if(inv==-1) throw invalid_argument("Invalid ECC points");
    int m=modd(up*inv,mod);
    int x3=modd(m*m-p.x-q.x,mod);
    int y3=modd(m*(p.x-x3)-p.y,mod);
    return {x3,y3,false};
}

point point_neg(point p,int mod){
    if(!p.inf) p.y=modd(-p.y,mod);
    return p;
}

point mul(int k,point p,int mod,int a){
    if(k<0) throw invalid_argument("Use a nonnegative ECC multiplier");
    point ans={0,0,true};
    while(k){
        if(k%2) ans=point_add(ans,p,mod,a);
        p=point_add(p,p,mod,a);
        k/=2;
    }
    return ans;
}

bool point_equal(point p,point q){
    if(p.inf || q.inf) return p.inf==q.inf;
    return p.x==q.x && p.y==q.y;
}

void print_point(point p){
    if(p.inf){
        cout<<"INF";
        return;
    }
    cout<<"("<<p.x<<","<<p.y<<")";
}

// beta = d*G; msg is a point, such as mul(m,G,prime,a).
pair<point,point> ecc_enc(point msg,point G,point beta,int k,int prime,int a){
    point c1=mul(k,G,prime,a);
    point c2=point_add(msg,mul(k,beta,prime,a),prime,a);
    return {c1,c2};
}

point ecc_dec(pair<point,point> c,int d,int prime,int a){
    point s=mul(d,c.first,prime,a);
    return point_add(c.second,point_neg(s,prime),prime,a);
}

// Decrypting this gives M1+M2, or (m1+m2)*G when Mi=mi*G.
pair<point,point> ecc_hom_add(pair<point,point> c,pair<point,point> q,int prime,int a){
    return {point_add(c.first,q.first,prime,a),point_add(c.second,q.second,prime,a)};
}


// CAESAR: encrypt with key; decrypt with -modd(key,26).
string caesar(string msg,int key){
    key=modd(key,26);
    for(int i=0;i<(int)msg.size();i++){
        if(msg[i]>='A' && msg[i]<='Z'){
            msg[i]='A'+modd(msg[i]-'A'+key,26);
        }else if(msg[i]>='a' && msg[i]<='z'){
            msg[i]='a'+modd(msg[i]-'a'+key,26);
        }
    }
    return msg;
}


// VERNAM: same function for encryption and decryption.
string vernam(string msg,string key){
    if(msg.size()!=key.size()) throw invalid_argument("Key length must match message");
    string ans=msg;
    for(int i=0;i<(int)msg.size();i++){
        ans[i]=(unsigned char)msg[i]^(unsigned char)key[i];
    }
    return ans;
}

void print_hex(string msg){
    string digits="0123456789ABCDEF";
    for(int i=0;i<(int)msg.size();i++){
        int val=(unsigned char)msg[i];
        cout<<digits[val/16]<<digits[val%16];
        if(i+1<(int)msg.size()) cout<<" ";
    }
}


// EXAMPLES: copy the functions you need and replace main for your problem.
signed main(){
    int p=97,q=101,n=p*q,phi=(p-1)*(q-1);
    int e=rsa_choose_e(phi),d=mod_inv(e,phi);
    int c1=rsa_enc(10,e,n),c2=rsa_enc(5,e,n);
    assert(rsa_dec(c1,d,n)==10);
    assert(rsa_dec(rsa_product(c1,c2,n),d,n)==50);
    assert(rsa_verify(10,rsa_sign(10,d,n),e,n));
    cout<<"RSA encryption, product, signature: OK"<<endl;

    int prime=97,alpha=primitive_element(prime),ed=5;
    int beta=mod_pow(alpha,ed,prime);
    auto ec1=el_enc(11,alpha,beta,3,prime);
    auto ec2=el_enc(5,alpha,beta,5,prime);
    assert(el_dec(ec1,ed,prime)==11);
    assert(el_dec(el_product(ec1,ec2,prime),ed,prime)==55);
    assert(el_dec(el_rrand(ec1,alpha,beta,5,prime),ed,prime)==11);
    assert(el_verify(11,el_sign(11,alpha,ed,5,prime),alpha,beta,prime));
    cout<<"ElGamal encryption, product, rerandomization, signature: OK"<<endl;

    int ep=17,a=2,dd=7;
    point G={5,1,false};
    point ebeta=mul(dd,G,ep,a);
    point M1=mul(2,G,ep,a),M2=mul(3,G,ep,a);
    auto pc1=ecc_enc(M1,G,ebeta,3,ep,a);
    auto pc2=ecc_enc(M2,G,ebeta,5,ep,a);
    assert(point_equal(ecc_dec(pc1,dd,ep,a),M1));
    point dec=ecc_dec(ecc_hom_add(pc1,pc2,ep,a),dd,ep,a);
    assert(point_equal(dec,mul(5,G,ep,a)));
    cout<<"ECC encryption, additive homomorphism: OK; sum = ";
    print_point(dec);
    cout<<endl;

    string msg="Hello, World!";
    string enc=caesar(msg,3);
    assert(enc=="Khoor, Zruog!");
    assert(caesar(enc,-3)==msg);
    cout<<"Caesar encrypted : "<<enc<<endl;

    string venc=vernam("HELLO","XMCKL");
    assert(vernam(venc,"XMCKL")=="HELLO");
    cout<<"Vernam encrypted (hex) : ";
    print_hex(venc);
    cout<<endl;

    assert(mod_inv(6,96)==-1);
    assert(mod_inv(-3,17)==11);
    assert(!rsa_verify(11,rsa_sign(10,d,n),e,n));
    assert(!el_verify(12,el_sign(11,alpha,ed,5,prime),alpha,beta,prime));
    assert(point_equal(point_add(G,point_neg(G,ep),ep,a),{0,0,true}));
    assert(mul(0,G,ep,a).inf);
    cout<<"All examples passed"<<endl;
    return 0;
}
