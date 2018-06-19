#include <iostream>
#include "utility.h"

template<typename T>
bool utility::IsPalindrome(T num) {

    int size = 0;
    short arr[50] = {0};

    while (num) {
        arr[size++] = static_cast<short>(num % 10);
        num /= 10;
    }

    int low = 0;
    int high = size - 1;
    bool flag = true;

    while (high > low) {
        if (arr[high--] != arr[low++]) {
            flag = false;
            break;
        }
    }

    return flag;

}

template<typename T>
T utility::Factorial(T num) {

    if (num == 0) return 1;

    T result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }

    return result;

}

template<typename T>
T utility::Power(T base, int exponent) {

    int result = 1;

    while (exponent) {
        if (exponent & 1) {
            result *= base;
        }

        exponent >>= 1;
        base *= base;
    }

    return result;
}

template bool utility::IsPalindrome<i64>(i64 num);

template bool utility::IsPalindrome<int>(int num);

template i64 utility::Factorial<i64>(i64 num);

template int utility::Factorial<int>(int num);

template i64 utility::Power(i64 base, int exponent);

template int utility::Power(int base, int exponent);

