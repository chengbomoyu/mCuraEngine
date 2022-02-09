#include <iostream> 
#include "Application.h"
#include "utils/logoutput.h"

int main(int argc, char **argv){
    std::cerr << std::boolalpha; //brief 让输出流将bool解析成为true或者 false。
    cura::Application::getInstance().run(argc, argv);
    return 0;
}
