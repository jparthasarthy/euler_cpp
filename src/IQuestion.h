#ifndef EULER_CPP_IQUESTION_H
#define EULER_CPP_IQUESTION_H

#include "globals.h"

class IQuestion {

public:
    virtual i64 Solve() = 0;

    virtual ~IQuestion() = default;

};


#endif //EULER_CPP_IQUESTION_H
