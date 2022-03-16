#pragma once

#include <vector>
#include <utility>

namespace sort {
    void insertionSort(std::vector<int> &arr) {
        size_t length = arr.size();
        for (int outer = 1; outer < length; ++outer) {
            int inner = outer - 1;
            int pivot = arr[outer];
            while ((inner >= 0) && (arr[inner] > pivot)) {
                arr[inner + 1] = arr[inner];
                --inner;
            }
            arr[inner + 1] = pivot;
        }
    }

    int binSearch(const std::vector<int> &arr, int low, int high, int target) {
        while (high - low > 1) {
            int middle = (low + high) / 2;
            if (arr[middle] > target) {
                high = middle;
            } else {
                low = middle;
            }
        }

        return low;
    }

    void insertionSortBinary(std::vector<int> &arr) {
        size_t length = arr.size();
        for (int outer = 1; outer < length; ++outer) {
            int inner = outer - 1;
            int index = binSearch(arr, -1, inner + 1, arr[outer]);
            for (int swapper = inner; swapper > index; --swapper) {
                std::swap(arr[swapper], arr[swapper + 1]);
            }
        }
    }
}