#ifndef EULER_CPP_UTILITY_H
#define EULER_CPP_UTILITY_H

#include "../globals.h"


namespace utility {

    // works for up to a 50 digit number
    template<typename T>
    bool IsPalindrome(T num);

    template<typename T>
    T Factorial(T num);

    template<typename T>
    T Power(T base, int exponent);


} // utility

#endif //EULER_CPP_UTILITY_H
