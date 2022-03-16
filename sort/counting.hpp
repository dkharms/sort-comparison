#pragma once

#include <vector>
#include <algorithm>

namespace sort {
    void countingSort(std::vector<int> &arr) {
        int maximal = *std::max_element(arr.begin(), arr.end());
        std::vector<int> res(arr.size());
        std::vector<int> count(maximal + 1, 0);
        for (const auto &number : arr) {
            count[number]++;
        }
        for (int i = 1; i < maximal + 1; ++i) {
            count[i] += count[i - 1];
        }
        for (int i : arr) {
            res[count[i] - 1] = i;
            count[i]--;
        }
        for (int i = 0; i < arr.size(); ++i) {
            arr[i] = res[i];
        }
    }
}
