cmake_minimum_required(VERSION 3.5)
project(LinkedList CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(NODE_SOURCE
  Node.hpp )

set(LIST_SOURCE
  LinkedList.hpp )

set(EXCEPT_SOURCE
	PrecondViolatedExcept.cpp PrecondViolatedExcept.h )

set(STUDENT_SOURCE
 student_tests.cpp)

 set(POLY_SOURCE
  Polynomial.hpp Polynomial.cpp Term.cpp Term.hpp)

  set(MAIN_SOURCE
  pcalc.cpp)

# create unittests
add_executable(student-tests catch.hpp ${NODE_SOURCE} ${LIST_SOURCE} ${EXCEPT_SOURCE} ${STUDENT_SOURCE} ${POLY_SOURCE})
add_executable(pcalc ${MAIN_SOURCE} ${NODE_SOURCE} ${LIST_SOURCE} ${EXCEPT_SOURCE} ${POLY_SOURCE})

# some simple tests
enable_testing()
add_test(student-tests student-tests)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
  Stack.txx student_tests.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
