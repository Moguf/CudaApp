##Cmakeの使い方おさらい
######基本

```c++
// {PRO_DICT}/hello.cpp
#include <iostoream>

int maic(void){
    std::cout<<"hello"<<std::endl;
    return 0;

}
```

```cmake
// {PRO_DICT}/CmakeLists.txt
cmake_minimum_required(VERSION 2.8)
project(hello)
add_executable(hello hello.cpp)
```
