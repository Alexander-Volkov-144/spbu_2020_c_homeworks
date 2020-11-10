cmake_minimum_required(VERSION 3.17)
project(spbu_2020_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB library/commonUtils/numericOperations.c)

add_library(stackd STATIC library/stackd/stackd.c)
add_library(list STATIC library/list/list.c)
add_library(bst STATIC library/bst/bst.c)

add_library(complexNumber library/complexNumber/complexNumber.c)

add_executable(task_1 homework_1/task_1.c)
add_executable(task_2 homework_1/task_2.c library/commonUtils/reverseArray.c)
add_executable(task_3 homework_1/task_3.c)
add_executable(task_4 homework_1/task_4.c)
add_executable(task_5 homework_1/task_5.c)
add_executable(task_2.1 homework_2/task_2.1.c)
add_executable(task_2.3 homework_2/task_2.3.c)
add_executable(task_2.5 homework_2/task_2.5.c)
add_executable(task_2.4 homework_2/task_2.4.c)
add_executable(task_2.2 homework_2/task_2.2.c)
target_link_libraries(task_2.2 m)
add_executable(task_4.1 homework_4/task_4.1.c)
target_link_libraries(task_4.1 stackd)
add_executable(task_3.1 homework_3/task_3.1.c )
target_link_libraries(task_3.1 list)
add_executable(task_3.2 homework_3/task_3.2.c)
target_link_libraries(task_3.2 list)

add_executable(task_4.2 homework_4/task_4.2.c)
add_executable(task_4.3 homework_4/task_4.3.c)

add_executable(task_5.1 homework_5/task_5.1.c)

target_link_libraries(task_5.1 bst)

add_executable(test_1.1 test_1/test_1.1.c)
add_executable(test_1.2 test_1/test_1.2.c)
target_link_libraries(test_1.2 complexNumber)

add_executable(test_2.3 test_2/test_2.3.c)
target_link_libraries(test_2.3 list)