#ifndef EULER_CPP_SORTING_H
#define EULER_CPP_SORTING_H

#include <cmath>
#include <cinttypes>

namespace sorting {

    template<typename T>
    void HeapSort(T *data, int count);

    template<typename T>
    void InsertionSort(T *data, int count);

    template<typename T>
    void IntroSort(T *data, int count);

    template<typename T>
    void QuickSort(T *data, int count);


} // sorting



#endif //EULER_CPP_SORTING_H
