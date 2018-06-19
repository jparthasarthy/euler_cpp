#include "Question3.h"


i64 Question3::Solve() {

    i64 num = 600851475143;

    i64 largest_prime = 2;
    i64 prime = 2;

    while (num > 1) {

        if (num % prime == 0) {
            largest_prime = prime;
        }

        while (num % prime == 0) {
            num /= prime;
        }

        prime = NextPrime(prime);
    }

    return largest_prime;

}
