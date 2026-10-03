#include<bits/stdc++.h>
using namespace std;
#define int long long


int mod_pow(int val,int pow,int mod){
    int ans=1;
    while(pow){
        if(pow%2) ans=(ans*val)%mod;
        val=(val*val)%mod;
        pow/=2;
    }
    return ans;
}


struct point{
    int x,y;
    bool inf;
};


int modd(int val,int mod){
    val%=mod;
    if(val<0) val+=mod;

    return val;
}


int mod_inv(int a,int mod){
    a=modd(a,mod);

    return mod_pow(a,mod-2,mod);
}


point point_add(point p,point q,int mod,int a){

    if(p.inf) return q;
    if(q.inf) return p;


    // P + (-P) = infinity
    if(p.x==q.x && modd(p.y+q.y,mod)==0){
        return {0,0,true};
    }


    int m=-1;


    // point doubling
    if(p.x==q.x && p.y==q.y){

        if(p.y==0){
            return {0,0,true};
        }

        int up=modd(3*p.x*p.x+a,mod);
        int down=modd(2*p.y,mod);

        m=modd(up*mod_inv(down,mod),mod);
    }


    // point addition
    else{

        int up=modd(q.y-p.y,mod);
        int down=modd(q.x-p.x,mod);

        m=modd(up*mod_inv(down,mod),mod);
    }


    int x3=modd(m*m-p.x-q.x,mod);

    int y3=modd(m*(p.x-x3)-p.y,mod);


    return {x3,y3,false};
}


point mul(int k,point p,int mod,int a){

    point ans={0,0,true};


    while(k){

        if(k%2)
            ans=point_add(ans,p,mod,a);


        p=point_add(p,p,mod,a);

        k/=2;
    }


    return ans;
}


point point_neg(point p,int mod){

    p.y=modd(-p.y,mod);

    return p;
}


void print_point(point p){

    if(p.inf){
        cout<<"INF";
        return;
    }

    cout<<"("<<p.x<<","<<p.y<<")";
}


signed main(){

    int p=17;
    int a=2;
    int b=2;


    point G={5,1,false};


    // private key
    int d=7;


    // public key beta = dG
    point beta=mul(d,G,p,a);


    cout<<"Public Key = ";
    print_point(beta);
    cout<<endl;



    // =========================
    // MESSAGE 1
    // =========================


    int m1=2;
    int k1=3;


    // M1 = m1G
    point M1=mul(m1,G,p,a);


    // C11 = k1G
    point c11=mul(k1,G,p,a);


    // C12 = M1 + k1*beta
    point c12=point_add(
        M1,
        mul(k1,beta,p,a),
        p,a
    );


    cout<<"Message 1 = ";
    print_point(M1);
    cout<<endl;


    cout<<"Cipher 1 = (";

    print_point(c11);

    cout<<" , ";

    print_point(c12);

    cout<<")"<<endl;



    // =========================
    // MESSAGE 2
    // =========================


    int m2=3;
    int k2=5;


    // M2 = m2G
    point M2=mul(m2,G,p,a);


    // C21 = k2G
    point c21=mul(k2,G,p,a);


    // C22 = M2 + k2*beta
    point c22=point_add(
        M2,
        mul(k2,beta,p,a),
        p,a
    );


    cout<<"Message 2 = ";
    print_point(M2);
    cout<<endl;


    cout<<"Cipher 2 = (";

    print_point(c21);

    cout<<" , ";

    print_point(c22);

    cout<<")"<<endl;



    // =========================
    // HOMOMORPHIC ADDITION
    // =========================


    // C1 = C11 + C21
    point c1=point_add(c11,c21,p,a);


    // C2 = C12 + C22
    point c2=point_add(c12,c22,p,a);


    cout<<"Added Cipher = (";

    print_point(c1);

    cout<<" , ";

    print_point(c2);

    cout<<")"<<endl;



    // =========================
    // DECRYPTION
    // =========================


    // d*C1
    point dc1=mul(d,c1,p,a);


    // -(d*C1)
    point neg=point_neg(dc1,p);


    // M = C2 - d*C1
    point dec=point_add(c2,neg,p,a);


    cout<<"Final Decrypted = ";

    print_point(dec);

    cout<<endl;



    // expected result = (m1+m2)G

    point expected=mul(m1+m2,G,p,a);


    cout<<"Expected = ";

    print_point(expected);

    cout<<endl;


    return 0;
}