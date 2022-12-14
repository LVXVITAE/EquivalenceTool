#include"input_module.h"
#include <gtest/gtest.h>
bool compilation_successful(std::string exe){
    std::filesystem::path EXE(exe);
    for(auto file : std::filesystem::directory_iterator(EXE.parent_path())){
        if(file.path()==EXE)return true;
    }
    return false;
}
namespace{
    class InputModuleTest :public ::testing::Test{
        protected:
        std::string test_dir = "./InputTest";
        InputModule im{};
        InputModuleTest(){
            im = InputModule(test_dir);
        }        
        void test_t(int i){
            int t=-1;
            if(im.get_srcs()[i]=="InputTest/t1.cpp"){
                EXPECT_EQ(compilation_successful("InputTest/t1.exe"),true);
                EXPECT_EQ(im.get_exes()[i],"InputTest/t1.exe");
                t=0;
            }else if (im.get_srcs()[i]=="InputTest/t2.cpp"){
                EXPECT_EQ(compilation_successful("InputTest/t2.exe"),false);
                EXPECT_EQ(im.get_exes()[i],"Fail to compile");
                t=1;
            }else if (im.get_srcs()[i]=="InputTest/t3.c"){
                EXPECT_EQ(compilation_successful("InputTest/t3.exe"),true);
                EXPECT_EQ(im.get_exes()[i],"InputTest/t3.exe");
                t=2;
            }else if (im.get_srcs()[i]=="InputTest/t4.c"){
                EXPECT_EQ(compilation_successful("InputTest/t4.exe"),false);
                EXPECT_EQ(im.get_exes()[i],"Fail to compile");
                t=3;
            }else{
                ASSERT_TRUE(false);
                std::cerr<<"Unknown file\n";
            }             
        }

    };
    TEST_F(InputModuleTest,test_size){    
        ASSERT_EQ(im.get_exes().size(),4);
        ASSERT_EQ(im.get_srcs().size(),4);
    }
    TEST_F(InputModuleTest,test1){
        test_t(0);
    }
    TEST_F(InputModuleTest,test2){
        test_t(1);
    }
    TEST_F(InputModuleTest,test3){
        test_t(2);
    }
    TEST_F(InputModuleTest,test4){
        test_t(3);
    }
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}