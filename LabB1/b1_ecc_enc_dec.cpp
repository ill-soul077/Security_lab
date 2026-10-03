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

int mod_inv(int a,int mod){
    return mod_pow(a,mod-2,mod);
}

int modd(int val,int mod){
    val=val%mod;
    if(val<0) val+=mod;

    return val;
}

point point_add(point p,point q,int mod,int a){

    if(p.inf) return q;
    if(q.inf) return p;

    if(p.x==q.x && modd(p.y+q.y,mod)==0){
        return {0,0,true};
    }

    int m=-1;
    if(p.x==q.x and p.y==q.y){
        m=(((3*p.x*p.x+a)%mod)*mod_inv(2*p.y,mod))%mod;
    }else{

        m=(q.y-p.y)*(mod_inv(q.x-p.x,mod))%mod;
    }

    int x3=modd(m*m-p.x-q.x,mod);
    int y3=modd(m*(p.x-x3)%mod-p.y,mod);

    return {x3,y3,false};
}

point mul(int k,point p,int mod,int a){
    point ans={0,0,true};

    while(k){
        if(k%2) ans=point_add(ans,p,mod,a);

        p=point_add(p,p,mod,a);
        k=k/2;
    }
    return ans;
}

point point_neg(point P,int p){

    P.y=modd(-P.y,p);

    return P;
}

void print_point(point P){

    if(P.inf){
        cout<<"INF";
        return;
    }

    cout<<"("<<P.x<<","<<P.y<<")";
}

signed main(){

    int p=17;
    int a=2;
    int b=2;

    int d=7;
    point G={5,1,false};
    point beta=mul(d,G,p,a);

    point msg={13,7,false};
    int k=3;
    point c1=mul(k,G,p,a);
    point c2=point_add(msg,mul(k,beta,p,a),p,a);


    cout<<"Message = ";
    print_point(msg);
    cout<<endl;


    cout<<"Ciphertext = (";

    print_point(c1);

    cout<<" , ";

    print_point(c2);

    cout<<")"<<endl;

    point dc1=mul(d,c1,p,a);
    point dec=point_add(c2,point_neg(dc1,p),p,a);

    print_point(dec);

    cout<<"farhan bokachoda"<<endl;
}
