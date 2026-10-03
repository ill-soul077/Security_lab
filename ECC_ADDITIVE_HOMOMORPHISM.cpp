#include<bits/stdc++.h>
using namespace std;

using ll=long long ;

struct point{
    ll x,y;
    bool infinity;
};

ll eg(ll a,ll b , ll &x, ll &y)
{
    if(b==0)
    {
        x=1;y=0;return a;
    }
    ll x1,y1;
    ll g=eg(b,a%b,x1,y1);
    x=y1;
    y=x1-(a/b)*y1;
    return g;
}

ll modinv(ll a,ll m)
{
    ll x,y;
    ll g=eg(a,m,x,y);
    if(g!=1) return -1;
    x%=m;
    if(x<0) x+=m;
    return x;
}





ll mod(ll x, ll p)
{
 x%=p;
 if(x<0) x+=p;
 return x;   
}

point padd(point P, point Q, ll p, ll a)
{
    if(P.infinity) return Q;
    if(Q.infinity) return P;

    ll x1=P.x,x2=Q.x;
    ll y1=P.y,y2=Q.y;

    // P + (-P) = O
    if(x1==x2 && mod(y1+y2,p)==0)
        return {0,0,true};

    ll m;

    if(x1!=x2)
    {
        ll nm=mod(y2-y1,p);
        ll dnm=mod(x2-x1,p);
        ll inv=modinv(dnm,p);

        m=mod(nm*inv,p);
    }
    else
    {
        if(y1==0)
            return {0,0,true};

        ll nm=mod(3*x1*x1+a,p);
        ll dnm=mod(2*y1,p);
        ll inv=modinv(dnm,p);

        m=mod(nm*inv,p);
    }

    ll x3=mod(m*m-x1-x2,p);
    ll y3=mod(m*(x1-x3)-y1,p);

    return {x3,y3,false};
}

point scalar_mult(ll k,point P,ll p,ll a)
{
    point res={0,0,true};

    while(k>0)
    {
        if(k&1)
            res=padd(res,P,p,a);

        P=padd(P,P,p,a);
        k>>=1;
    }

    return res;
}


point point_neg(point P,ll p )
{
    return {P.x,mod(-P.y,p)};
}

void print_point(point p )
{
            cout << "("
             << p.x
             << ", "
             << p.y
             << ")";
}




int main()
{

ll p=17;
ll a=2;
ll b=2;

ll k=7;// random 

point G={5,1,false};
ll d=7;
point Q=scalar_mult(d,G,p,a);

cout<<" Point , Q = ";
print_point(Q);
cout<<endl;

// message 1 
    ll m1=2;
    ll k1=3;

    // M1 = m1G
    point M1=scalar_mult(m1,G,p,a);

    // C11 = k1G
    point C11=scalar_mult(k1,G,p,a);

    // C12 = M1 + k1Q
    point k1Q=scalar_mult(k1,Q,p,a);
    point C12=padd(M1,k1Q,p,a);


    cout<<"\nMESSAGE 1 = ";
    print_point(M1);

    cout<<"\nCIPHER 1 = (";
    print_point(C11);
    cout<<" , ";
    print_point(C12);
    cout<<")"<<endl;

    // ==================================================
    // MESSAGE 2
    // ==================================================

    ll m2=3;
    ll k2=5;

    // M2 = m2G
    point M2=scalar_mult(m2,G,p,a);

    // C21 = k2G
    point C21=scalar_mult(k2,G,p,a);

    // C22 = M2 + k2Q
    point k2Q=scalar_mult(k2,Q,p,a);
    point C22=padd(M2,k2Q,p,a);


    cout<<"\nMESSAGE 2 = ";
    print_point(M2);

    cout<<"\nCIPHER 2 = (";
    print_point(C21);
    cout<<" , ";
    print_point(C22);
    cout<<")"<<endl;

    // now adding  those 2 points 
    point tmp1=padd(C11,C21,p,a);
    point tmp2=padd(C12,C22,p,a);

    // now decrypting 
    point s = scalar_mult(d,tmp1,p,a);
    point t5=point_neg(s,p);
    point dec=padd(tmp2,t5,p,a);

    cout<<"FINAL DECRYPTED = ";
    print_point(dec);
    cout<<endl;



}