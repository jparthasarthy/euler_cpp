#include "Question1.h"

i64 Question1::Solve() {
    return SumIncrement(3) + SumIncrement(5) - SumIncrement(15);

}

const i64 Question1::SumIncrement(int num) {

    int p = 999 / num; // p is the number of nums under 1000
    return num * p * (p + 1) / 2;
}
