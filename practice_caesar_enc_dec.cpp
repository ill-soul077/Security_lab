#include<bits/stdc++.h>
using namespace std;
#define int long long


int modd(int val,int mod){
    val%=mod;
    if(val<0) val+=mod;

    return val;
}

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

signed main(){
    string msg;
    int key;

    cout<<"Give message : ";
    getline(cin,msg);
    cout<<"Give key : ";
    if(!(cin>>key)){
        cout<<"Invalid key"<<endl;
        return 1;
    }

    key=modd(key,26);
    string enc=caesar(msg,key);
    string dec=caesar(enc,-key);

    cout<<"Encrypted : "<<enc<<endl;
    cout<<"Decrypted : "<<dec<<endl;

    return 0;
}
