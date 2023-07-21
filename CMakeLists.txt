cmake_minimum_required(VERSION 2.5)

project(mymuduo)

# mymuduo 最终编译为 so动态库, 设置动态库路径, 放在根目录的lib文件夹下
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -fPIC")

# 定义 参与编译的源代码文件, (.) 是所有文件
aux_source_directory(. SRC_LIST)


# 编译生成动态库, 最终会生成 lib/mymuduo.so
add_library(mymuduo SHARED ${SRC_LIST})