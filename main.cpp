#include"judge_tool.h"
#include<iostream>
using namespace std;

int main(int argc, char* argv[]){
    if(argc == 2){
        std::filesystem::path input_dir(argv[1]),//./input
        parent_dir = input_dir.parent_path(),//./
        output_dir = parent_dir/"output";//./output
        system(("mkdir "+ output_dir.string()).c_str());
        system(("touch "+output_dir.string()+"/equal.csv").c_str());
        system(("touch "+output_dir.string()+"/inequal.csv").c_str());
        ofstream eq(output_dir.string()+"/equal.csv"),ineq(output_dir.string()+"/inequal.csv");
        eq<<"file1,file2\n";
        ineq<<"file1,file2\n";
        eq.close();ineq.close();
        for(auto dir : filesystem::directory_iterator(input_dir)){//./input/dir
            string dir_path = dir.path().string(),out_path=output_dir.string();
            JudgeTool judge=JudgeTool(dir_path);
            judge.get_equivalence();
            judge.save(out_path);
        }
    }else{
        cerr<<"Unknown directory.\n";
        return 1;
    }
    return 0;
}