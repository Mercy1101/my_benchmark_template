cmake_minimum_required(VERSION 3.17)

set(EXECUTABLE_EXE_NAME my_benchmark_template)
project(${EXECUTABLE_EXE_NAME})
# 可执行文件生成路径
set(EXECUTABLE_OUTPUT_PATH ../bin/)
#aux_source_directory(${PROJECT_SOURCE_DIR}/tools_benchmark BENCHMARK_SOURCE_FILE)

# 添加静态库的连接路径
# link_directories(${PROJECT_SOURCE_DIR}/lib/benchmark/Release/)
link_directories(${PROJECT_SOURCE_DIR}/lib/benchmark/)

# main函数
set(SOURCES
    src/benchmark_template.cc
#    ${BENCHMARK_SOURCE_FILE}
)

# 把源文件添加进工程中
add_executable(${EXECUTABLE_EXE_NAME} 
  ${SOURCES}
)

# 设置包含路径
target_include_directories(${EXECUTABLE_EXE_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/benchmark
)

target_link_libraries(${EXECUTABLE_EXE_NAME} benchmark.lib)
target_link_libraries(${EXECUTABLE_EXE_NAME} benchmark_main.lib)

if (MSVC)
target_link_libraries(${EXECUTABLE_EXE_NAME} Shlwapi.lib) # 链接库
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4") # 设置警告等级为4
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /WX") # 设置警告视为错误
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /std:c++latest") # 设置使用最新C++标准
endif (MSVC)