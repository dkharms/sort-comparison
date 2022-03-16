#pragma once

#include <vector>
#include <utility>

namespace sort {
    void selectionSort(std::vector<int> &arr) {
        size_t length = arr.size();
        for (int outer = 0; outer < length; ++outer) {
            int min_index = outer;
            for (int inner = outer + 1; inner < length; ++inner) {
                if (arr[inner] < arr[min_index]) {
                    min_index = inner;
                }
            }
            if (min_index != outer) {
                std::swap(arr[outer], arr[min_index]);
            }
        }
    }
}