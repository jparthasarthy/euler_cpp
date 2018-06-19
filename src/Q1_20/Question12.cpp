#include "Question12.h"


i64 Question12::Solve() {

    GeneratePrimes(65500);

    int num = 3;
    int divisor_count = 0;

    int divisor = 2;
    int next_divisor = 0;

    // divisor count algorithm
    while(divisor_count < 500) {

        num++;
        int destructible_num = num;

        if(destructible_num % 2 == 0) destructible_num /= 2;

        next_divisor = 1;

        for (i64 prime : primes_) {
            if(utility::Power(prime, 2) > destructible_num) {
                next_divisor *= 2;
                break;
            }

            int exponent = 1;

            while(destructible_num % prime == 0) {
                exponent++;
                destructible_num /= prime;
            }

            if (exponent > 1) {
                next_divisor *= exponent;
            }

            if (destructible_num == 1) break;
        }

        divisor_count = divisor * next_divisor;
        divisor = next_divisor;

    }

    return (num * (num - 1)) / 2;
}
