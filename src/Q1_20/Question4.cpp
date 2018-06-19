#include "Question4.h"

i64 Question4::Solve() {

    i64 max = 100001;

    for (int i = 999; i > 111; i--) {

        if (max >= i * 999) break;

        for (int j = 999; j > 111; j--) {
            i64 num = i * j;
            if (num > max && utility::IsPalindrome<i64>(num)) {
                max = num;
            }
        }
    }

    return max;

}
