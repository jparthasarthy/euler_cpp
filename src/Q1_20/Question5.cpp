#include "Question5.h"

i64 Question5::Solve() {

    GeneratePrimes(20);

    i64 num = utility::Factorial(i64{20}); // start with a number that is guaranteed to be divisible by 1-20

    for (i64 prime : primes_) {

        while (IsDivisibleByAllUpTo20(num / prime)) {
            num /= prime;
        }
    }

    return num;
}

bool Question5::IsDivisibleByAllUpTo20(i64 num) {

    for (int i = 2; i < 21; i++) {

        if (num % i != 0) {
            return false;
        }
    }

    return true;
}
