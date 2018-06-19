#include "Question9.h"


i64 Question9::Solve() {

    i64 sum = 1000;

    for(i64 a = 0; a < (sum - 3) / 3; a++) {
        for(i64 b = a; b < (sum - 1 - a) /2; b++) {
            i64 c = sum - a - b;

            if(utility::Power(a , 2) + utility::Power(b, 2) == utility::Power(c, 2)) {
                return a * b * c;
            }
        }
    }

    return -1; // fails and cannot find the tripple
}
