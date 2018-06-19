#ifndef EULER_CPP_QUESTION5_H
#define EULER_CPP_QUESTION5_H


#include "../globals.h"
#include "../QuestionPrimes.h"
#include "../helpers/utility.h"

class Question5 : public QuestionPrimes {

private:
    bool IsDivisibleByAllUpTo20(i64 num);

public:

    i64 Solve() override;

};


#endif //EULER_CPP_QUESTION5_H
