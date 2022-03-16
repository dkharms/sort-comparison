#pragma once

#include <vector>
#include <utility>

namespace sort {
    void bubbleSort(std::vector<int> &arr) {
        size_t length = arr.size();
        for (int outer = 0; outer < length; ++outer) {
            for (int inner = 0; inner < length - 1; ++inner) {
                if (arr[inner] > arr[inner + 1]) {
                    std::swap(arr[inner], arr[inner + 1]);
                }
            }
        }
    }

    void bubbleSortIversonOne(std::vector<int> &arr) {
        size_t length = arr.size();
        for (int outer = 0; outer < length; ++outer) {
            bool swapped = false;
            for (int inner = 0; inner < length - 1; ++inner) {
                if (arr[inner] > arr[inner + 1]) {
                    std::swap(arr[inner], arr[inner + 1]);
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
    }

    void bubbleSortIversonTwo(std::vector<int> &arr) {
        size_t length = arr.size();
        size_t max_bound = length - 1;
        for (int outer = 0; outer < length; ++outer) {
            bool swapped = false;
            int swap_index = 0;
            for (int inner = 0; inner < max_bound; ++inner) {
                if (arr[inner] > arr[inner + 1]) {
                    std::swap(arr[inner], arr[inner + 1]);
                    swapped = true;
                    swap_index = inner;
                }
            }
            max_bound = swap_index;
            if (max_bound == 0 || !swapped) {
                break;
            }
        }
    }
}