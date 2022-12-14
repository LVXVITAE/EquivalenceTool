#include "judge_tool.h"
#include <gtest/gtest.h>

namespace
{
  	class JudgeToolTest : public ::testing::Test{
  	protected:
    std::string test_dir = "JudgeToolTest";
    JudgeTool judge{};
    JudgeToolTest(){
    	judge = JudgeTool(test_dir);
		judge.get_equivalence();
    }
	bool check_srcs(std::string src){
		for(auto file : judge.get_srcs()){
			if(file==src)return true;
		}
		return false;
	}
	bool check_exes(std::string exe){
		for(auto file : judge.get_exes()){
			if(file==exe)return true;
		}
		return false;
	}
	bool compilation_successful(std::string exe){
		std::filesystem::path EXE(exe);
		for(auto file : std::filesystem::directory_iterator(EXE.parent_path())){
			if(file.path()==EXE)return true;
		}
		return false;
	}
	int idx(std::string src){
		for(int i=0;i<judge.get_srcs().size();i++){
			if(judge.get_srcs()[i]==src)return i;
		}
		return -1;
	}
  	};
	
  	TEST_F(JudgeToolTest, testinit){
		EXPECT_EQ(judge.get_dir(),"JudgeToolTest");
		EXPECT_EQ(judge.get_format(),"int(1,100) char string(1,20)");
		EXPECT_TRUE(check_srcs("JudgeToolTest/cont1.cpp"));
		EXPECT_TRUE(check_srcs("JudgeToolTest/cont2.cpp"));
		EXPECT_TRUE(check_srcs("JudgeToolTest/sum.cpp"));
		EXPECT_TRUE(check_srcs("JudgeToolTest/t1.cpp"));
		EXPECT_TRUE(check_srcs("JudgeToolTest/t2.cpp"));
		EXPECT_TRUE(check_srcs("JudgeToolTest/t3.c"));
		EXPECT_TRUE(check_srcs("JudgeToolTest/t4.c"));
		EXPECT_FALSE(check_srcs("JudgeToolTest/t5.py"));
		EXPECT_FALSE(check_srcs("JudgeToolTest/stdin_format.txt"));

		EXPECT_TRUE(compilation_successful("JudgeToolTest/cont1.exe"));
		EXPECT_TRUE(compilation_successful("JudgeToolTest/cont2.exe"));
		EXPECT_TRUE(compilation_successful("JudgeToolTest/sum.exe"));
		EXPECT_TRUE(compilation_successful("JudgeToolTest/t1.exe"));
		EXPECT_FALSE(compilation_successful("JudgeToolTest/t2.exe"));
		EXPECT_TRUE(compilation_successful("JudgeToolTest/t3.exe"));
		EXPECT_FALSE(compilation_successful("JudgeToolTest/t4.exe"));
		EXPECT_FALSE(compilation_successful("JudgeToolTest/t5.exe"));
		EXPECT_FALSE(compilation_successful("JudgeToolTest/stdin_format.exe"));
  	
		EXPECT_TRUE(check_exes("JudgeToolTest/cont1.exe"));
		EXPECT_TRUE(check_exes("JudgeToolTest/cont2.exe"));
		EXPECT_TRUE(check_exes("JudgeToolTest/sum.exe"));
		EXPECT_TRUE(check_exes("JudgeToolTest/t1.exe"));
		EXPECT_FALSE(check_exes("JudgeToolTest/t2.exe"));
		EXPECT_TRUE(check_exes("JudgeToolTest/t3.exe"));
		EXPECT_FALSE(check_exes("JudgeToolTest/t4.exe"));
		EXPECT_FALSE(check_exes("JudgeToolTest/t5.exe"));
		EXPECT_FALSE(check_exes("JudgeToolTest/stdin_format.exe"));
	}
	TEST_F(JudgeToolTest,equivalence){
		
		EXPECT_TRUE(judge.equal(idx("JudgeToolTest/cont1.cpp"),idx("JudgeToolTest/cont2.cpp")));
		EXPECT_TRUE(judge.equal(idx("JudgeToolTest/cont1.cpp"),idx("JudgeToolTest/t1.cpp")));
		EXPECT_TRUE(judge.equal(idx("JudgeToolTest/cont1.cpp"),idx("JudgeToolTest/t3.c")));
		EXPECT_TRUE(judge.equal(idx("JudgeToolTest/cont2.cpp"),idx("JudgeToolTest/t1.cpp")));
		EXPECT_TRUE(judge.equal(idx("JudgeToolTest/cont1.cpp"),idx("JudgeToolTest/t3.c")));
		EXPECT_TRUE(judge.equal(idx("JudgeToolTest/t1.cpp"),idx("JudgeToolTest/t3.c")));
		
		EXPECT_FALSE(judge.equal(idx("JudgeToolTest/t1.cpp"),idx("JudgeToolTest/t2.c")));
		EXPECT_FALSE(judge.equal(idx("JudgeToolTest/t3.cpp"),idx("JudgeToolTest/t4.c")));
		EXPECT_FALSE(judge.equal(idx("JudgeToolTest/cont1.cpp"),idx("JudgeToolTest/sum.cpp")));
	}
	TEST_F(JudgeToolTest,save){
		system("mkdir out && touch out/equal.csv out/inequal.csv");
		judge.save("out");
		std::string line;
		std::ifstream eq("out/equal.csv");
		while (std::getline(eq,line)){
			std::string file1(line.substr(0,line.rfind(','))),file2(line.substr(line.rfind(',')+1,line.rfind('\n')));
			EXPECT_TRUE(judge.equal(idx(file1),idx(file2)));
		}
		eq.close();
		std::ifstream ineq("out/inequal.csv");
		while (std::getline(eq,line)){
			std::string file1(line.substr(0,line.rfind(','))),file2(line.substr(line.rfind(',')+1,line.rfind('\n')));
			EXPECT_FALSE(judge.equal(idx(file1),idx(file2)));
		}
		ineq.close();
		system("rm -rf out");
	}

}
int main(int argc, char **argv){
  	::testing::InitGoogleTest(&argc, argv);
  	return RUN_ALL_TESTS();
}