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
    TEST(InputModuleTest,read_input){
        std::string test_dir = "./InputTest";
        InputModule im = InputModule(test_dir);
        ASSERT_EQ(im.get_exes().size(),4);
        ASSERT_EQ(im.get_srcs().size(),4);
        for(int i=0;i<4;i++){
            if(im.get_srcs()[i]=="InputTest/t1.cpp"){
                EXPECT_EQ(compilation_successful("InputTest/t1.exe"),true);
                EXPECT_EQ(im.get_exes()[i],"InputTest/t1.exe");
            }else if (im.get_srcs()[i]=="InputTest/t2.cpp"){
                EXPECT_EQ(compilation_successful("InputTest/t2.exe"),false);
                EXPECT_EQ(im.get_exes()[i],"Fail to compile");
            }else if (im.get_srcs()[i]=="InputTest/t3.c"){
                EXPECT_EQ(compilation_successful("InputTest/t3.exe"),true);
                EXPECT_EQ(im.get_exes()[i],"InputTest/t3.exe");
            }else if (im.get_srcs()[i]=="InputTest/t4.c"){
                EXPECT_EQ(compilation_successful("InputTest/t4.exe"),false);
                EXPECT_EQ(im.get_exes()[i],"Fail to compile");
            }else{
                ASSERT_TRUE(false);
                std::cerr<<"Unknown file\n";
            }        
        }        
    }
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}