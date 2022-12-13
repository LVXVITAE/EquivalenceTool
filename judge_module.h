#ifndef __JUDGE_MODULE_H__
#define __JUDGE_MODULE_H__
#include<vector>
#include<string>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include <array>
enum type{INT,CHAR,STRING};
typedef struct var_{
    enum type tp;
    union {
        int i;
        char c;
        char *s;
    }val;
}var;
class JudgeModule{
    private:
    std::string exe1{};
    std::string exe2{};
    std::string format{};
    std::vector<var> input1{};
    public:
    std::vector<var> input_gen(int k);
    JudgeModule(std::string &e1,std::string &e2,std::string &f){
        exe1 = e1;
        exe2 = e2;
        format = f;
    }
    bool compare();
};
std::vector<var> JudgeModule::input_gen(int k){
    std::vector<var> gened_input;
    int i = 0;
    while(i<format.length()){
        var v;
        if(format[i] == 'i'){
            i += 3;
            int inf,sup;
            while(format[i] != '(')i++;
            int j = i+1;
            while(format[j] != ',')j++;
            inf = stoi(format.substr(i+1,j));
            i=j;
            j=i+1;
            while(format[j] != ')')j++;
            sup = stoi(format.substr(i+1,j));
            int randint = (rand() % (sup-inf+1))+inf;
            if(k>1&&gened_input.size()==k-2){
                while(randint == input1[k-2].val.i)randint = (rand() % (sup-inf+1))+inf;
            }
            v.tp = INT;
            v.val.i = randint;
            i = j+1;
        }else if(format[i] == 'c'){
            i += 4;
            int randchar = 1;
            while(!((int)'a'<=randchar&&randchar<=(int)'z'||(int)'A'<=randchar&&randchar<=(int)'Z'))randchar = (rand() % ('z'-'A'+1))+'A';
            if(k>1&&gened_input.size()==k-2){
                while (randchar == input1[k-2].val.c&&!((int)'a'<=randchar&&randchar<=(int)'z'||(int)'A'<=randchar&&randchar<=(int)'Z')){
                    randchar = (rand() % ('z'-'A'+1))+'A';
                }
            }
            v.tp=CHAR;
            v.val.c = (char)randchar;
        }else if(format[i] == 's'){
            i += 6;
            int inf,sup;
            while(format[i] != '(')i++;
            int j = i+1;
            while(format[j] != ',')j++;
            inf = stoi(format.substr(i+1,j));
            i=j;
            j=i+1;
            while(format[j] != ')')j++;
            sup = stoi(format.substr(i+1,j));
            int randlen = (rand() % (sup-inf+1))+inf;
            char* str = new char[randlen+1];
            str[randlen] = '\0';
            for(int l = 0;l<randlen;l++){
                int randchar = 1;
                while(!((int)'a'<=randchar&&randchar<=(int)'z'||(int)'A'<=randchar&&randchar<=(int)'Z'))randchar = (rand() % ('z'-'A'+1))+'A';
                str[l]=(char)randchar;
            }
            if(k>1&&gened_input.size()==k-2){
                while (strcmp(input1[k-2].val.s,str)==0){
                    for(int l = 0;l<randlen;l++){
                    int randchar = 1;
                    while(!((int)'a'<=randchar&&randchar<=(int)'z'||(int)'A'<=randchar&&randchar<=(int)'Z'))randchar = (rand() % ('z'-'A'+1))+'A';
                        str[l]=(char)randchar;
                    }
                }  
            }
            v.tp=STRING;
            v.val.s = str;
            i=j+1;
        }
        gened_input.push_back(v);
        while(i<format.length()&&format[i] == ' ')i++;
    }
    if(k==1)input1 = gened_input;
    return gened_input;
}
bool JudgeModule::compare(){
    bool eq = true;
    int inputnum = std::count(format.begin(),format.end(),' ')+1;
    system("touch in out1 out2");
    for(int k=1;k<=inputnum+1&&eq==true;k++){
        std::vector<var> in = input_gen(k);
        std::string ip="";
        
        for(int r=0;r<inputnum;r++){
            if(in[r].tp==INT){
                ip=ip+std::to_string(in[r].val.i)+"\n";
            }else if(in[r].tp==CHAR){
                ip = ip +in[r].val.c+"\n";
            }else if(in[r].tp=STRING){
                ip = ip +std::string(in[r].val.s)+"\n";
            }
        }
        ip[ip.length()-1] ='\n';
        std::ofstream fileop("in");
        fileop<<ip;
        fileop.close();
        int rt1 = system(("timeout 10 "+exe1+" < in > out1").c_str()),rt2 = system(("timeout 10 "+exe2+ "< in > out2").c_str());
        if(rt1==0&&rt2==0){
            std::string res1="",res2="";
            std::ifstream o1("out1"),o2("out2");
            o1>>res1;
            o2>>res2;
            eq = res1==res2;
            o1.close();o2.close();
        }
    }
    system("rm in out1 out2");
    return eq;
}
#endif