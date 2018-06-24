cmake_minimum_required(VERSION 3.10)
project(SoftwareCourseDesign)

set(CMAKE_CXX_STANDARD 11)

add_executable(SoftwareCourseDesign main.cpp wordAnalysis.h grammarAnalysis.h wordAnalysis.cpp grammarAnalysis.cpp main2.cpp compile.cpp compile.h semanticAnalysis.cpp semanticAnalysis.h inputSQL.cpp inputSQL.h createTable.cpp createTable.h runJava.cpp)