#pragma once

#include <algorithm>
#include <vector>
#include <cstdint>

namespace sort {
    void countSort(std::vector<int> &arr, int exp) {
        std::vector<int> output(arr.size(), 0);
        std::vector<int> count(10, 0);

        for (int i : arr) {
            count[(i / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        arr = output;
    }

    void radixSort(std::vector<int> &arr) {
        int maximal = *std::max_element(arr.begin(), arr.end());

        for (int exp = 1; maximal / exp > 0; exp *= 10) {
            countSort(arr, exp);
        }
    }
}

