project(lab4-asd)
cmake_minimum_required(VERSION 3.12)   
option(BUILD_TESTS "Build test" ON)

add_executable(main main.cpp Graph.cpp Graph.h) # ����������� main.exe

if(BUILD_TESTS)
  enable_testing()
  add_executable(test1 Test.cpp Graph.cpp Graph.h catch.hpp) # ����������� main.exe
  add_test(test1 test1) # ��������� test1.exe ��� �������� ���������. ���� �������, ���� ��� ���������� ��� 0.
endif()
