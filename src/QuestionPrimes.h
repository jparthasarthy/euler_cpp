#ifndef EULER_CPP_PRIMES_H
#define EULER_CPP_PRIMES_H


#include "globals.h"
#include "IQuestion.h"


class QuestionPrimes : public IQuestion {

protected:
    QuestionPrimes() = default;

    std::vector<i64> primes_;

public:
    ~QuestionPrimes() override = default;

    void GeneratePrimes(int limit); // upper value for the prime array

    i64 NextPrime(i64 current_prime);

    bool IsPrime(i64 num);


};


#endif //EULER_CPP_PRIMES_H
