#include "Question15.h"

i64 Question15::Solve() {

    long double num = 1;

    for(int i = 1; i < 21; i++) {
        long double j = floorl(i);
        num *= (20 + j) / j;
    }

    return llroundl(num);
}
