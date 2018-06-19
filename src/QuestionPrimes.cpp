#include <iostream>
#include "QuestionPrimes.h"


i64 QuestionPrimes::NextPrime(i64 current_prime) {

    if (current_prime == 2) return 3;

    i64 prime = current_prime + 2;

    bool is_prime = false;
    while (!is_prime) {

        is_prime = true;
        for (int i = 2; i < (int) sqrt(prime) + 1; i++) {
            if (prime % i == 0) {
                is_prime = false;
                break;
            }
        }

        if (!is_prime) {
            prime += 2;
        }
    }
    return prime;
}

void QuestionPrimes::GeneratePrimes(int limit) {


    // repeated calls can be expensive if the array is large, it this operation is used frequently a member variable
    // for limit can be stored and then the vector can be appended to using NextPrime when the size of primes_ needs
    // to be changed
    primes_.clear();
    // do not want to preallocate limit elements in the vector, especially when it gets very large
    // primes density is modeled by x/ln(x) -> allocated double the space to be safe
    primes_.reserve(static_cast<unsigned int>((2 * limit)/log(limit)));

    auto *primes_bool_array = new int[limit];

    for (int i = 4; i < limit; i += 2) {
        primes_bool_array[i] = 1;
    }

    for (int i = 3; i < std::sqrt(limit); i += 2) {

        if (!primes_bool_array[i]) {
            for (int j = i; i * j < limit; j++) {
                primes_bool_array[i * j] = 1;
            }
        }
    }

    for (int i = 2; i < limit; i++) {
        if (!primes_bool_array[i]) {
            primes_.push_back(i);
        }
    }

    delete[] primes_bool_array;
    primes_.shrink_to_fit();

}

bool QuestionPrimes::IsPrime(i64 num) {

    if (num <= 1) {
        return false;
    } else if (num <= 3) {
        return true;
    } else if (num % 2 == 0 || num % 3 == 0) {
        return false;
    }

    int i = 5;
    while (i * i <= num) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }

        i += 6;
    }
    return true;
}




