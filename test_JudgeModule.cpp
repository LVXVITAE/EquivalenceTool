#include"judge_module.h"
#include<gtest/gtest.h>
#include<fstream>
#include<filesystem>
bool in_range(int n,int inf,int sup){
    return inf<=n&&n<=sup;
}
bool is_char(char c){
    return in_range(c,'a','z')||in_range(c,'A','Z');
}
bool is_string(std::string &s){
    for(auto e : s){
        if(!is_char(e))return false;
    }
    return true;
}
void check_int(var &v){
    EXPECT_EQ(v.tp,INT);
    EXPECT_TRUE(in_range(v.val.i,1,10));
}
void check_char(var &v){
    EXPECT_EQ(v.tp,CHAR);
    EXPECT_TRUE(is_char(v.val.c));
}
void check_string(var &v){
    EXPECT_EQ(v.tp,STRING);
    std::string S(v.val.s);
    EXPECT_TRUE(is_string(S));
    EXPECT_TRUE(in_range(S.length(),3,6));
}
bool cmp(var &v1,var &v2){
    
    if(v1.tp!=v2.tp)return false;
    else{
        bool res = true;
        switch (v1.tp)
        {
            case INT:
                res = v1.val.i==v2.val.i;
                break;
            case CHAR:
                res = v1.val.c==v2.val.c;
                break;
            case STRING:
                std::string s1(v1.val.s),s2(v2.val.s);
                res = s1==s2;
            break;
        }  
        return res;  
    }
}
void compile(std::filesystem::path &test_dir){
    for(auto f : std::filesystem::directory_iterator(test_dir)){
        std::filesystem::path p = f.path();
        if(p.extension()==".cpp"||p.extension()==".c"){
            std::string cmd = "g++ "+f.path().string()+" -o " + p.replace_extension(".exe").string();
            system(cmd.c_str());
        }
    }
}
namespace{
    class TestInputGen : public ::testing::Test{
        protected:
        std::string exe1="dummy1";
        std::string exe2="dummy2";
        std::vector<std::string> line{};
        TestInputGen(){
            std::string format;
            std::ifstream f("JudgeModuleTest/test0/stdin_format.txt");
            
            while(std::getline(f,format)){
                line.push_back(format);
            }
        }
    };
    TEST_F(TestInputGen,test00){
        JudgeModule J(exe1,exe2,line[0]);
        std::vector<var> new_input1 = J.input_gen(1);
        check_int(new_input1[0]);
        std::vector<var> new_input2 = J.input_gen(2);
        check_int(new_input2[0]);
        EXPECT_FALSE(cmp(new_input1[0],new_input2[0]));
    }
    TEST_F(TestInputGen,test01){
        JudgeModule J(exe1,exe2,line[1]);
        std::vector<var> new_input1 = J.input_gen(1);
        check_char(new_input1[0]);
        std::vector<var> new_input2 = J.input_gen(2);
        check_char(new_input2[0]);
        EXPECT_FALSE(cmp(new_input1[0],new_input2[0]));
    }
    TEST_F(TestInputGen,test02){
        JudgeModule J(exe1,exe2,line[2]);
        std::vector<var> new_input1 = J.input_gen(1);
        check_string(new_input1[0]);
        std::vector<var> new_input2 = J.input_gen(2);
        check_string(new_input2[0]);
        EXPECT_FALSE(cmp(new_input1[0],new_input2[0]));
    }
    TEST_F(TestInputGen,test03){
        JudgeModule J(exe1,exe2,line[3]);
        std::vector<var> new_input1 = J.input_gen(1);
        check_int(new_input1[0]);
        check_char(new_input1[1]);
        std::vector<var> new_input2 = J.input_gen(2);
        check_int(new_input2[0]);
        check_char(new_input2[1]);
        std::vector<var> new_input3 = J.input_gen(3);
        check_int(new_input3[0]);
        check_char(new_input3[1]);
        EXPECT_FALSE(cmp(new_input1[0],new_input2[0]));
        EXPECT_FALSE(cmp(new_input1[1],new_input3[1]));
    }
    TEST_F(TestInputGen,test04){
        JudgeModule J(exe1,exe2,line[4]);
        std::vector<var> new_input1 = J.input_gen(1);
        check_int(new_input1[0]);
        check_string(new_input1[1]);
        std::vector<var> new_input2 = J.input_gen(2);
        check_int(new_input2[0]);
        check_string(new_input2[1]);
        std::vector<var> new_input3 = J.input_gen(3);
        check_int(new_input3[0]);
        check_string(new_input3[1]);
        EXPECT_FALSE(cmp(new_input1[0],new_input2[0]));
        EXPECT_FALSE(cmp(new_input1[1],new_input3[1]));
    }
    TEST_F(TestInputGen,test05){
        JudgeModule J(exe1,exe2,line[5]);
        std::vector<var> new_input1 = J.input_gen(1);
        check_int(new_input1[0]);
        check_char(new_input1[1]);
        check_string(new_input1[2]);

        std::vector<var> new_input2 = J.input_gen(2);
        check_int(new_input2[0]);
        check_char(new_input2[1]);
        check_string(new_input2[2]);

        std::vector<var> new_input3 = J.input_gen(3);
        check_int(new_input3[0]);
        check_char(new_input3[1]);
        check_string(new_input3[2]);
        std::vector<var> new_input4 = J.input_gen(4);
        check_int(new_input4[0]);
        check_char(new_input4[1]);
        check_string(new_input4[2]);
        EXPECT_FALSE(cmp(new_input1[0],new_input2[0]));
        EXPECT_FALSE(cmp(new_input1[1],new_input3[1]));
        EXPECT_FALSE(cmp(new_input1[2],new_input4[2]));
    }
    TEST_F(TestInputGen,test06){
        JudgeModule J(exe1,exe2,line[6]);
        std::vector<var> new_input1 = J.input_gen(1);
        check_char(new_input1[0]);
        check_int(new_input1[1]);
        check_string(new_input1[2]);
        std::vector<var> new_input2 = J.input_gen(2);
        check_char(new_input2[0]);
        check_int(new_input2[1]);
        check_string(new_input2[2]);
        std::vector<var> new_input3 = J.input_gen(3);
        check_char(new_input3[0]);
        check_int(new_input3[1]);
        check_string(new_input3[2]);
        std::vector<var> new_input4 = J.input_gen(4);
        check_char(new_input4[0]);
        check_int(new_input4[1]);
        check_string(new_input4[2]);
        EXPECT_FALSE(cmp(new_input1[0],new_input2[0]));
        EXPECT_FALSE(cmp(new_input1[1],new_input3[1]));
        EXPECT_FALSE(cmp(new_input1[2],new_input4[2]));
    }
    TEST_F(TestInputGen,test07){
        JudgeModule J(exe1,exe2,line[7]);
        std::vector<var> new_input1 = J.input_gen(1);
        check_string(new_input1[0]);
        check_char(new_input1[1]);
        check_int(new_input1[2]);
        std::vector<var> new_input2 = J.input_gen(2);
        check_string(new_input2[0]);
        check_char(new_input2[1]);
        check_int(new_input2[2]);
        std::vector<var> new_input3 = J.input_gen(3);
        check_string(new_input3[0]);
        check_char(new_input3[1]);
        check_int(new_input3[2]);
        std::vector<var> new_input4 = J.input_gen(4);
        check_string(new_input4[0]);
        check_char(new_input4[1]);
        check_int(new_input4[2]);
        EXPECT_FALSE(cmp(new_input1[0],new_input2[0]));
        EXPECT_FALSE(cmp(new_input1[1],new_input3[1]));
        EXPECT_FALSE(cmp(new_input1[2],new_input4[2]));
    }
    TEST(TestJudge,test1){
        std::filesystem::path test_dir("JudgeModuleTest/test1");
        std::string format;
        std::ifstream f("JudgeModuleTest/test1/stdin_format.txt");
        std::getline(f,format);
        compile(test_dir);
        std::string add1 = "JudgeModuleTest/test1/add1.exe",add2 = "JudgeModuleTest/test1/add2.exe",mul = "JudgeModuleTest/test1/mul.exe";
        JudgeModule add(add1,add2,format);
        JudgeModule add1_mul(add1,mul,format);
        JudgeModule add2_mul(add2,mul,format);
        EXPECT_TRUE(add.compare());
        EXPECT_FALSE(add1_mul.compare());
        EXPECT_FALSE(add2_mul.compare());
    }
    TEST(TestJudge,test2){
        std::filesystem::path test_dir("JudgeModuleTest/test2");
        std::string format;
        std::ifstream f("JudgeModuleTest/test2/stdin_format.txt");
        std::getline(f,format);
        compile(test_dir);
        std::string print1 = "JudgeModuleTest/test2/print1.exe",print2 = "JudgeModuleTest/test2/print2.exe",rprint = "JudgeModuleTest/test2/rprint.exe";
        JudgeModule print(print1,print2,format);
        JudgeModule print1_rprint(print1,rprint,format);
        JudgeModule print2_rprint(print2,rprint,format);
        EXPECT_TRUE(print.compare());
        EXPECT_FALSE(print1_rprint.compare());
        EXPECT_FALSE(print2_rprint.compare());
    }
    TEST(TestJudge,test3){
        std::filesystem::path test_dir("JudgeModuleTest/test3");
        std::string format;
        std::ifstream f("JudgeModuleTest/test3/stdin_format.txt");
        std::getline(f,format);
        compile(test_dir);
        std::string cont1 = "JudgeModuleTest/test3/cont1.exe",cont2 = "JudgeModuleTest/test3/cont2.exe",sum = "JudgeModuleTest/test3/sum.exe";
        JudgeModule cont(cont1,cont2,format);
        JudgeModule cont1_sum(cont1,sum,format);
        JudgeModule cont2_sum(cont2,sum,format);
        EXPECT_TRUE(cont.compare());
        EXPECT_FALSE(cont1_sum.compare());
        EXPECT_FALSE(cont2_sum.compare());
    }
    TEST(TestJudge,test4){
        std::filesystem::path test_dir("JudgeModuleTest/test4");
        std::string format;
        std::ifstream f("JudgeModuleTest/test4/stdin_format.txt");
        std::getline(f,format);
        compile(test_dir);
        std::string count_s = "JudgeModuleTest/test4/count_s.exe",count_S = "JudgeModuleTest/test4/count_S.exe",count_sS = "JudgeModuleTest/test4/count_sS.exe";
        JudgeModule counts_countS(count_s,count_S,format);
        JudgeModule counts_countsS(count_s,count_sS,format);
        JudgeModule countS_countsS(count_S,count_sS,format);
        EXPECT_FALSE(counts_countS.compare());
        EXPECT_FALSE(countS_countsS.compare());
        EXPECT_FALSE(counts_countsS.compare());
    }
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}