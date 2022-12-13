#include<iostream>
#include<string>
using namespace std;
int main(){
    int i;char c;string s;
    cin>>i>>c>>s;
    i+=c;
    for(auto si : s)i+=si;
    cout<<i<<endl;
    return 0;
}