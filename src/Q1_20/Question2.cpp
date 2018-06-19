#include "Question2.h"


i64 Question2::Solve() {

    int f1 = 1;
    int f2 = 2;

    i64 sum = 0;

    while (f2 < 4000000) {
        if (f2 % 2 == 0) {
            sum += f2;
        }

        std::swap(f1, f2);
        f2 += f1;
    }
    return sum;

}
