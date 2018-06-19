#include <iostream>
#include "Question10.h"

i64 Question10::Solve() {

    GeneratePrimes(2000000);

    i64 sum = 0;

    for(i64 prime : primes_) {
        sum += prime;
    }

    return sum;
}
