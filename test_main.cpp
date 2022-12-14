#include<gtest/gtest.h>
#include<filesystem>
#include<fstream>
#include<string>
namespace{
    class TestMain : public ::testing::Test{
        protected:
        TestMain(){
            system("g++ main.cpp -o JudgeToolTest/judgetest -std=c++20");
            system("JudgeToolTest/judgetest JudgeToolTest/input");
        }        
    };
    bool report_equal(std::string f1,std::string f2){
        std::ifstream eq("JudgeToolTest/output/equal.csv");
        std::string line;
        while (std::getline(eq,line)){
			std::string file1(line.substr(0,line.rfind(','))),file2(line.substr(line.rfind(',')+1,line.rfind('\n')));
            if((f1==file1&&f2==file2)||(f1==file2&&f2==file1))return true;
		}
        eq.close();
        return false;  
    }
    bool report_inequal(std::string f1,std::string f2){
        std::ifstream ineq("JudgeToolTest/output/inequal.csv");
        std::string line;
        while (std::getline(ineq,line)){
			std::string file1(line.substr(0,line.rfind(','))),file2(line.substr(line.rfind(',')+1,line.rfind('\n')));
            if((f1==file1&&f2==file2)||(f1==file2&&f2==file1))return true;
		}
        ineq.close();
        return false;  
    }
    TEST_F(TestMain, test1){
        EXPECT_TRUE(report_equal("JudgeToolTest/input/test1/cont1.cpp","JudgeToolTest/input/test1/cont2.cpp"));
        EXPECT_TRUE(report_equal("JudgeToolTest/input/test1/cont1.cpp","JudgeToolTest/input/test1/t1.cpp"));
        EXPECT_TRUE(report_equal("JudgeToolTest/input/test1/cont1.cpp","JudgeToolTest/input/test1/t3.c"));
        EXPECT_TRUE(report_equal("JudgeToolTest/input/test1/cont2.cpp","JudgeToolTest/input/test1/t1.cpp"));
        EXPECT_TRUE(report_equal("JudgeToolTest/input/test1/cont2.cpp","JudgeToolTest/input/test1/t3.c"));
        EXPECT_TRUE(report_equal("JudgeToolTest/input/test1/t1.cpp","JudgeToolTest/input/test1/t3.c"));

        EXPECT_TRUE(report_inequal("JudgeToolTest/input/test1/cont1.cpp","JudgeToolTest/input/test1/sum.cpp"));
        EXPECT_TRUE(report_inequal("JudgeToolTest/input/test1/cont2.cpp","JudgeToolTest/input/test1/sum.cpp"));
        EXPECT_TRUE(report_inequal("JudgeToolTest/input/test1/t1.cpp","JudgeToolTest/input/test1/sum.cpp"));
        EXPECT_TRUE(report_inequal("JudgeToolTest/input/test1/t3.c","JudgeToolTest/input/test1/sum.cpp"));

        EXPECT_FALSE(report_equal("JudgeToolTest/input/test1/t1.cpp","JudgeToolTest/input/test1/t2.cpp"));
        EXPECT_FALSE(report_equal("JudgeToolTest/input/test1/t3.c","JudgeToolTest/input/test1/t4.c"));
        EXPECT_FALSE(report_equal("JudgeToolTest/input/test1/t3.c","JudgeToolTest/input/test1/t5.py"));
    }
    TEST_F(TestMain,test2){
        EXPECT_TRUE(report_equal("JudgeToolTest/input/test2/print1.cpp","JudgeToolTest/input/test2/print2.cpp"));
        EXPECT_TRUE(report_inequal("JudgeToolTest/input/test2/print1.cpp","JudgeToolTest/input/test2/rprint.cpp"));
        EXPECT_TRUE(report_inequal("JudgeToolTest/input/test2/print2.cpp","JudgeToolTest/input/test2/rprint.cpp"));
    }
    TEST_F(TestMain,test3){
        EXPECT_TRUE(report_equal("JudgeToolTest/input/test3/add1.cpp","JudgeToolTest/input/test3/add2.cpp"));
        EXPECT_TRUE(report_inequal("JudgeToolTest/input/test3/add1.cpp","JudgeToolTest/input/test3/mul.cpp"));
        EXPECT_TRUE(report_inequal("JudgeToolTest/input/test3/add2.cpp","JudgeToolTest/input/test3/mul.cpp"));
    }
}
int main(int argc, char **argv){
  	::testing::InitGoogleTest(&argc, argv);
  	return RUN_ALL_TESTS();
}