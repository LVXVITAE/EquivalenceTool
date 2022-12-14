#include<iostream>
using namespace std;
int main(){
    int a,A;
    string s,S;
    char c;
    cin>>a>>s>>A>>S>>c;
    int num=0;
    for(auto ch : s){
        if(ch=='s'||ch=='S')num++;
    }
    for(auto ch : S){
        if(ch=='s'||ch=='S')num++;
    }
    cout<<num<<endl;
    return 0;
}