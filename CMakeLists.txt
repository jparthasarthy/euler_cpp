cmake_minimum_required(VERSION 3.8)
project(euler_cpp)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp
        src/globals.h
        src/IQuestion.h
        src/Q1_20/Question1.cpp
        src/Q1_20/Question1.h
        src/Q1_20/1_20.h
        src/Q1_20/Question2.cpp
        src/Q1_20/Question2.h
        src/QuestionPrimes.cpp
        src/QuestionPrimes.h
        src/Q1_20/Question3.cpp
        src/Q1_20/Question3.h
        src/helpers/utility.cpp
        src/helpers/utility.h
        src/Q1_20/Question4.cpp
        src/Q1_20/Question4.h
        src/helpers/sorting.cpp
        src/helpers/sorting.h
        src/Q1_20/Question5.cpp
        src/Q1_20/Question5.h
        src/Q1_20/Question6.cpp
        src/Q1_20/Question6.h
        src/Q1_20/Question7.cpp
        src/Q1_20/Question7.h
        src/Q1_20/Question8.cpp
        src/Q1_20/Question8.h
        src/Q1_20/Question9.cpp
        src/Q1_20/Question9.h
        src/Q1_20/Question10.cpp
        src/Q1_20/Question10.h
        src/Q1_20/Question11.cpp
        src/Q1_20/Question11.h
        src/Q1_20/Question12.cpp
        src/Q1_20/Question12.h
        src/Q1_20/Question13.cpp
        src/Q1_20/Question13.h
        src/Q1_20/Question14.cpp
        src/Q1_20/Question14.h
        src/Q1_20/Question15.cpp
        src/Q1_20/Question15.h
        src/helpers/BigInt/BigIntImpl.cpp
        src/helpers/BigInt/BigIntImpl.h
        src/Q1_20/Question17.cpp
        src/Q1_20/Question17.h
        src/helpers/BigInt/BigIntUtility.cpp
        src/helpers/BigInt/BigIntUtility.h
        src/helpers/BigInt/BigInt.h)

add_executable(euler_cpp ${SOURCE_FILES})