#pragma once

#include <vector>

namespace sort {
    void fixHeap(std::vector<int> *heap, int root, int size) {
        int left_child = 2 * root + 1;
        int right_child = 2 * root + 2;
        int max = root;
        if (left_child < size && heap->at(max) < heap->at(left_child)) {
            max = left_child;
        }
        if (right_child < size && heap->at(max) < heap->at(right_child)) {
            max = right_child;
        }
        if (max != root) {
            std::swap(heap->at(max), heap->at(root));
            fixHeap(heap, max, size);
        }
    }

    void heapSort(std::vector<int> &arr) {
        for (int i = arr.size() / 2 - 1; i >= 0; --i) {
            fixHeap(&arr, i, arr.size());
        }
        for (int i = arr.size() - 1; i >= 0; --i) {
            std::swap(arr[0], arr[i]);
            fixHeap(&arr, 0, i);
        }
    }
}