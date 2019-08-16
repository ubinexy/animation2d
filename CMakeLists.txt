cmake_minimum_required(VERSION 3.14)
project(2d_Animation)

set(CMAKE_CXX_STANDARD 14)

add_executable(2d_Animation main.cpp character.cpp character.h Entity.h AEntity.cpp AEntity.h Controller.cpp Controller.h AController.h AnimationSet.h BController.h)