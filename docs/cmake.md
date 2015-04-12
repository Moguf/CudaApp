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
######ファイルはCMakeLists.txtに記述する
```cmake
# {PRO_DICT}/CmakeLists.txt
cmake_minimum_required(VERSION 2.8)
project(hello)
add_executable(hello hello.cpp)
```
######補足的な情報
```
# リリースビルド用オプション
set(CMAKE_C_FLAGS_RELEASE "-Wall -O2")
# デバッグビルド用オプション
set(CMAKE_C_FLAGS_DEBUG "-g")
# ビルドのタイプはリリース
set(CMAKE_BUILD_TYPE Release)

# バージョン番号
set(serial "1.0.0")
# 共有ライブラリのバージョン番号
set(soserial "1")
# ビルドするためにインクルードするヘッダーファイルの場所
include_directories("${PROJECT_SOURCE_DIR}")
# 共有ライブラリとしてビルド
add_library(unarray SHARED unarray.c)
# バージョン番号の適用
set_target_properties(unarray PROPERTIES VERSION ${serial} SOVERSION ${soserial})
# 共有ライブラリのインストール指定
install(TARGETS unarray LIBRARY DESTINATION lib)
# 共有ライブラリ用ヘッダーファイルのインストール指定
install(FILES unarray.h DESTINATION include)
```
実行方法
```shell
cmake .
make
```