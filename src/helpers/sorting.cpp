#include <algorithm>
#include <iostream>
#include "sorting.h"


template<typename T>
int Partition(T *data, int left, int right) {

    int pivot = data[right];
    int i = left;

    for (int j = left; j < right; j++) {

        if (data[j] < pivot) {
            std::swap(data[i++], data[j]);
        }
    }

    data[right] = data[i];
    data[i] = pivot;

    return i;

}

template<typename T>
void MaxHeapify(T *data, int heap_size, int index) {

    int left = (index + 1) * 2 - 1;
    int right = (index + 1) * 2;

    int largest = 0;

    if (left < heap_size && data[left] > data[index]) {
        largest = left;
    } else {
        largest = index;
    }

    if (right < heap_size && data[right] > data[largest]) {
        largest = right;
    }

    if (largest != index) {
        std::swap(data[index], data[largest]);
        MaxHeapify(data, heap_size, largest);
    }
}

// TODO:: Change to iterative
template<typename T>
void QuickSortRecursive(T *data, int left, int right) {

    if (left < right) {

        int partition = Partition(data, left, right);
        QuickSortRecursive(data, left, partition - 1);
        QuickSortRecursive(data, partition + 1, right);
    }

}

template<typename T>
void sorting::HeapSort(T *data, int count) {

    int heap_size = count;

    for (int p = (heap_size - 1) / 2; p >= 0; p--) {
        MaxHeapify(data, heap_size, p);
    }

    for (int i = count - 1; i > 0; i--) {
        std::swap(data[i], data[0]);

        heap_size--;
        MaxHeapify(data, heap_size, 0);
    }
}

template<typename T>
void sorting::InsertionSort(T *data, int count) {

    for (int i = 1; i < count; i++) {
        int j = i;

        while (j > 0) {
            if (data[j - 1] > data[j]) {
                std::swap(data[j], data[j - 1]);
                j--;
            } else {
                break;
            }
        }
    }

}

template<typename T>
void sorting::IntroSort(T *data, int count) {

    int partition_size = Partition(data, 0, count - 1);

    if (partition_size < 16) {
        InsertionSort(data, count);
    } else if (partition_size > 2 * log(count)) {
        HeapSort(data, count);
    } else {
        QuickSortRecursive(data, 0, count - 1);
    }

}

template<typename T>
void sorting::QuickSort(T *data, int count) {

    int left = 0;
    int right = count;

    QuickSortRecursive(data, left, right);

}


template void sorting::HeapSort<int64_t>(int64_t *data, int count);

template void sorting::InsertionSort<int64_t>(int64_t *data, int count);

template void sorting::IntroSort<int64_t>(int64_t *data, int count);

template void sorting::QuickSort<int64_t>(int64_t *data, int count);