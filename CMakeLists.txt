cmake_minimum_required (VERSION 3.0)
project (lottery_benchmark)
add_executable(lottery_benchmark lottery_benchmark.cpp lottery.cpp)

target_link_libraries(lottery_benchmark benchmark pthread)

