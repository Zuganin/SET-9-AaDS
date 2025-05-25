cmake_minimum_required(VERSION 3.31)
project(A1)

set(CMAKE_CXX_STANDARD 20)

add_executable(A1 main.cpp
        A1m.cpp
        A1m.h
        A1q.cpp
        A1q.h
        A1r.cpp
        A1r.h
        A1rq.cpp
        A1rq.h
        utils.cpp
        utils.h)
