#pragma once

#include <vector>
#include <algorithm>

namespace sort {
    void merge(std::vector<int> *array, int l, int m, int r) {
        int left_size = m - l + 1;
        int right_size = r - m;

        std::vector<int> left(left_size), right(right_size);
        for (int i = 0; i < left_size; ++i) {
            left[i] = array->at(l + i);
        }
        for (int i = 0; i < right_size; ++i) {
            right[i] = array->at(m + i + 1);
        }

        int ll = 0, rr = 0, pivot = l;
        while (ll < left_size || rr < right_size) {
            if (rr >= right_size || ll < left_size && left[ll] < right[rr]) {
                array->at(pivot) = left[ll];
                ++ll;
            } else {
                array->at(pivot) = right[rr];
                ++rr;
            }
            ++pivot;
        }
    }

    void mergeSort(std::vector<int> &arr) {
        int length = static_cast<int>(arr.size());
        for (int window_size = 1; window_size < length; window_size = 2 * window_size) {
            for (int left = 0; left < length; left += 2 * window_size) {
                int middle = std::min(left + window_size - 1, length - 1);
                int right = std::min(left + 2 * window_size - 1, length - 1);
                merge(&arr, left, middle, right);
            }
        }
    }
}