cmake_minimum_required(VERSION 3.16)
project(INF2_Labo5 C)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -Wpedantic")
set(CMAKE_C_STANDARD 11)

add_executable(INF2_Labo5 main.c Bateau.h Bateau.c Port.c Port.h Outils.c Outils.h)