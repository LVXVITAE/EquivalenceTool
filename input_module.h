#ifndef __INPUT_MODULE_H__
#define __INPUT_MODULE_H__
#include<vector>
#include<string>
#include<filesystem>
#include<fstream>
#include<cstdlib>
#include<cstring>
class InputModule{
    private:
    std::string dir{};//./input/dir
    std::vector<std::string> srcs{};
    std::vector<std::string> exes{};
    std::string format{};
    void compile();
    public:
    InputModule(std::string &dir_name);
    InputModule(){}
    std::vector<std::string> &get_srcs(){return srcs;}
    std::vector<std::string> &get_exes(){return exes;}
    std::string &get_format(){return format;}
};

InputModule::InputModule(std::string &dir_name){
    dir = dir_name;
    if(dir.starts_with("./"))dir.erase(dir.begin(),dir.begin()+2);
    for(auto file : std::filesystem::directory_iterator(dir)){
        std::string p = file.path();
        if(p.ends_with(".cpp")||p.ends_with(".c"))
        srcs.push_back(p);
        if(p.ends_with("stdin_format.txt")){
            std::ifstream File_Handler;
            File_Handler.open(p);
            std::getline(File_Handler,format);
            File_Handler.close();
        }
    }
    compile();
}
void InputModule::compile(){
    for(auto src : srcs){
        std::string name = src.substr(0,src.rfind("."));
        int fail = std::system(("g++ "+src+" -o "+name+".exe").c_str());
        if(fail == 0)exes.push_back(name+".exe");
        else exes.push_back("Fail to compile");
    }
}



#endif