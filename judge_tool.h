#ifndef __JUDGE_TOOL_H__
#define __JUDGE_TOOL_H__
#include"input_module.h"
#include"judge_module.h"
class JudgeTool{
    private:
    std::string dir{};//./input/dir
    std::vector<int> parent{};
    std::vector<std::string> srcs{};
    std::vector<std::string> exes{};
    std::string format{}; 
    int Find(int s){
        while (s!=parent[s]){
            s = parent[s];
        }
        return s;
    }
    void Union(int s, int t){
        int rs = Find(s),rt = Find(t);
        parent[rt]=rs;
    }
    public:
    JudgeTool(std::string &dir_path);
    ~JudgeTool();
    void get_equivalence();
    void save(std::string &output_dir);
};
JudgeTool::JudgeTool(std::string &dir_path){
    dir = dir_path;
    InputModule ipmd=InputModule(dir);
    srcs = ipmd.get_srcs();
    exes = ipmd.get_exes();
    format = ipmd.get_format();
    parent = std::vector<int>(srcs.size());
    for(int i = 0;i<parent.size();i++)
    parent[i]=i;
}
JudgeTool::~JudgeTool(){
    for(auto exe : std::filesystem::directory_iterator(dir)){
        if((exe.path().string()).ends_with(".exe")){
            system(("rm "+exe.path().string()).c_str());
        }
    }
}
void JudgeTool::get_equivalence(){

    for(int i = 0;i<parent.size()-1;i++){
        for(int j = i+1; j<parent.size();j++){
            if(Find(i)!=Find(j)&&exes[i]!="Fail to compile"&&exes[j]!="Fail to compile"){
                JudgeModule jud = JudgeModule(exes[i],exes[j],format);
                bool equi = jud.compare();
                if(equi)Union(i,j);
            }
        }
    }

}
void JudgeTool::save(std::string &output_dir){
    if(parent.size()>1){
        std::ofstream eq(output_dir+"/equal.csv",std::ofstream::app),ineq(output_dir+"/inequal.csv",std::ofstream::app);
        for(int i = 0;i<parent.size()-1;i++){
            for(int j=i+1;j<parent.size();j++){
                if(exes[i]!="Fail to compile"&&exes[j]!="Fail to compile"){
                    if(Find(i)==Find(j)){
                        eq<<srcs[i]<<','<<srcs[j]<<'\n';
                    }else{
                        ineq<<srcs[i]<<','<<srcs[j]<<'\n';
                    }
                }
            }
        }
        eq.close();ineq.close();
    }
}
#endif