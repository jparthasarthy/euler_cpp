#ifndef EULER_CPP_QUESTION1_H
#define EULER_CPP_QUESTION1_H

#include "../globals.h"
#include "../IQuestion.h"

class Question1 : public IQuestion {

public:
    i64 Solve() override;

private:
    const i64 SumIncrement(int num);

};


#endif //EULER_CPP_QUESTION1_H
