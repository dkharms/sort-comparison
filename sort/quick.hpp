#pragma once

#include <vector>
#include <utility>

namespace sort {
    int getPivot(std::vector<int> *array, int l, int r) {
        int pivot = array->at((l + r) / 2);
        int left = l, right = r;
        while (!false) {
            while (array->at(left) < pivot) {
                ++left;
            }
            while (array->at(right) > pivot) {
                --right;
            }
            if (left >= right) {
                return right;
            }
            std::swap(array->at(left++), array->at(right--));
        }
    }

    void _quickSort(std::vector<int> *array, int l, int r) {
        if (l < r) {
            int pivot = getPivot(array, l, r);
            _quickSort(array, l, pivot);
            _quickSort(array, pivot + 1, r);
        }
    }

    void quickSort(std::vector<int> &arr) {
        _quickSort(&arr, 0, arr.size() - 1);
    }
}