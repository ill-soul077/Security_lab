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

point G={5,1,false};
ll d=7;
point Q=scalar_mult(d,G,p,a);

cout<<" Point , Q : "<<endl;
print_point(Q);

}