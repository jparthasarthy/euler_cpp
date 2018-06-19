#ifndef EULER_CPP_QUESTION8_H
#define EULER_CPP_QUESTION8_H

#include "../globals.h"
#include "../IQuestion.h"


class Question8 : public IQuestion{

public:
    i64 Solve() override;

public:
    i64 AdjacentProduct(std::string::const_iterator start, std::string::const_iterator end);

};


#endif //EULER_CPP_QUESTION8_H
