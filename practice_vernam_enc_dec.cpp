#include<bits/stdc++.h>
using namespace std;
#define int long long


string vernam(string msg,string key){
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

signed main(){
    string msg,key;

    cout<<"Give message : ";
    getline(cin,msg);
    cout<<"Give key (same length as message) : ";
    getline(cin,key);

    while(key.size()!=msg.size()){
        cout<<"Key and message must have the same length"<<endl;
        cout<<"Give valid key : ";
        if(!getline(cin,key)) return 1;
    }

    string enc=vernam(msg,key);
    string dec=vernam(enc,key);

    cout<<"Encrypted (hex) : ";
    print_hex(enc);
    cout<<endl;
    cout<<"Decrypted : "<<dec<<endl;

    return 0;
}
