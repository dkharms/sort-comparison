
/*
 * Порохнин Даниил Алексеевич, БПИ-203.
 * В качестве IDE использовал CLion.
 * Реализованы все сортировки, есть два .csv файла, есть графики для всех сортировок, небольшой отчет.
 *
 * Не написаны комментарии к коду.
 */

#include <memory>

#include "sort/heap.hpp"
#include "sort/quick.hpp"
#include "sort/radix.hpp"
#include "sort/merge.hpp"
#include "sort/bubble.hpp"
#include "sort/counting.hpp"
#include "sort/insertion.hpp"
#include "sort/selection.hpp"
#include "sort-benchmark/benchmark.h"

void
generateHeaders(std::vector <std::string> &arr, std::vector <std::string> &groups, std::vector <std::string> &sorts) {
    for (const auto &group : groups) {
        for (const auto &sort : sorts) {
            arr.push_back(sort + group);
        }
    }
}

void testAllSortings() {
    auto bench = benchmark::runner::Sort();

    std::vector <std::string> groups = {
            "[0-5]", "[0-4000]", "[AlmostSorted]", "[ReverseSorted]",
    };

    std::vector <std::string> sorts = {
            "BubbleSort", "BubbleSortIversonOne", "BubbleSortIversonTwo",
            "InsertionSort", "InsertionSortBinary", "SelectionSort",
            "CountingSort", "HeapSort", "QuickSort",
            "RadixSort", "MergeSort",
    };

    bench.addTest(sorts[0], sort::bubbleSort);
    bench.addTest(sorts[1], sort::bubbleSortIversonOne);
    bench.addTest(sorts[2], sort::bubbleSortIversonTwo);
    bench.addTest(sorts[3], sort::insertionSort);
    bench.addTest(sorts[4], sort::insertionSortBinary);
    bench.addTest(sorts[5], sort::selectionSort);
    bench.addTest(sorts[6], sort::countingSort);
    bench.addTest(sorts[7], sort::heapSort);
    bench.addTest(sorts[8], sort::quickSort);
    bench.addTest(sorts[9], sort::radixSort);
    bench.addTest(sorts[10], sort::mergeSort);

    auto resultsSmall = bench.runSuite(50, 300, 10);
    auto resultsBig = bench.runSuite(100, 4100, 100);

    auto headers = std::vector < std::string > {"Size"};
    generateHeaders(headers, groups, sorts);

    auto exporter = benchmark::data::Exporter(headers, ",");
    exporter.saveToFile("results-small.csv", resultsSmall);
    exporter.saveToFile("results-big.csv", resultsBig);
}

int main() {
    testAllSortings();
}
