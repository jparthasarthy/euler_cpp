#include "Question6.h"


i64 Question6::Solve() {

    i64 limit = 100;

    i64 sum_of_squares = 0;
    i64 sum_squared = 0;

    for (i64 i = 1; i <= limit; i++) {
        sum_of_squares += utility::Power(i, 2);
        sum_squared += i;
    }

    sum_squared = utility::Power(sum_squared, 2);

    return sum_squared - sum_of_squares;
}
