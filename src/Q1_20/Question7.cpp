#include "Question7.h"

i64 Question7::Solve() {

    int count = 2;
    i64 num = 3;

    while (count < 10001) {
        num += 2;
        if (IsPrime(num))
            count++;
    }

    return num;
}
