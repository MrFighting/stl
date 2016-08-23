cmake_minimum_required(VERSION 3.5)
project(stl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Vector.h test.cpp test.h List.h
        hashtable.h Unorded_Set.h hashtable.cpp Unorderd_Map.h Stack.h Queue.h Priority_Queue.h Memory.h)
add_executable(stl ${SOURCE_FILES})