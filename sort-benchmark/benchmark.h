#pragma once

#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <functional>
#include <fstream>

namespace benchmark {
    namespace test {
        struct Input {
            std::string benchmarkName;
            std::function<void(std::vector<int> &)> function;

            Input(std::string benchmarkName, std::function<void(std::vector<int> &)> function) {
                this->benchmarkName = benchmarkName;
                this->function = function;
            }
        };

        struct Result {
            std::string benchmarkName;
            int arraySize;
            long long elapsedTime;

            Result(std::string name, int arraySize, long long elapsedTime) {
                this->benchmarkName = name;
                this->arraySize = arraySize;
                this->elapsedTime = elapsedTime;
            }
        };

        class InputGenerator {
        public:
            static std::shared_ptr<std::vector<int>>
            generateArrayRandom(int size, int minimal, int maximal) {
                std::shared_ptr<std::vector<int>> arr = std::make_shared<std::vector<int>>();

                srand(time(nullptr));
                for (int i = 0; i < size; ++i) {
                    arr->push_back(minimal + (rand() % static_cast<int>(maximal - minimal + 1)));
                }

                return arr;
            }

            static std::shared_ptr<std::vector<int>>
            generateAlmostSortedArray(int size, int minimal, int maximal, int step, bool ascending) {
                std::shared_ptr<std::vector<int>> arr = generateArrayRandom(size, minimal, maximal);

                if (ascending) {
                    std::sort(arr->begin(), arr->end());
                } else {
                    std::sort(arr->begin(), arr->end(), std::greater<int>());
                }

                if (step > 0) {
                    for (int i = 0; i < arr->size() - step - 1; i += step + 1) {
                        std::swap(arr->at(i), arr->at(i + step));
                    }
                }

                return arr;
            }
        };
    }

    namespace runner {
        class Sort {
        private:
            std::vector<benchmark::test::Input> benchmarkSuites_;

            bool isSorted(const std::vector<int> &arr) {
                for (int i = 0; i < arr.size() - 1; ++i) {
                    if (arr[i] > arr[i + 1]) {
                        return false;
                    }
                }

                return true;
            }

            test::Result benchmarkSort(std::shared_ptr<std::vector<int>> arr, test::Input input) {
                std::cout << "\t\t[INFO] Sorting array with " << input.benchmarkName << '\n';
                auto copiedArr = *arr;

                auto start = std::chrono::high_resolution_clock::now();
                input.function(copiedArr);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                auto milliseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();

                if (isSorted(copiedArr)) {
                    dumpArray(copiedArr);
                    return test::Result(input.benchmarkName, arr->size(), milliseconds);
                }

                throw std::runtime_error("array is not sorted");
            }

            void runTest(std::shared_ptr<std::vector<int>> arr, std::vector<test::Result> &results) {
                for (const auto &suite : benchmarkSuites_) {
                    auto result = benchmarkSort(arr, suite);
                    results.push_back(result);
                }
            }

            void dumpArray(std::vector<int> &arr) {
                std::ofstream f("array.log", std::ios_base::app);
                for (const auto &item : arr) {
                    f << item << " ";
                }
                f << "\n-----####-----\n";
            }

        public:
            void addTest(std::string name, std::function<void(std::vector<int> &)> function) {
                benchmarkSuites_.emplace_back(name, function);
            }

            std::vector<test::Result> runSuite(int start, int end, int step) {
                std::vector<test::Result> results;

                for (int size = start; size <= end; size += step) {
                    std::cout << "[INFO] Sorting array with size " << size << '\n';

                    auto arrSmall = test::InputGenerator::generateArrayRandom(size, 0, 5);
                    auto arrBig = test::InputGenerator::generateArrayRandom(size, 0, 4000);
                    auto arrAlmostSorted = test::InputGenerator::generateAlmostSortedArray(size, 0, 4000, 10, true);
                    auto arrReverseSorted = test::InputGenerator::generateAlmostSortedArray(size, 0, 4000, 0, false);

                    std::cout << "\t[INFO] Sorting [0-5]" << '\n';
                    dumpArray(*arrSmall);
                    runTest(arrSmall, results);

                    std::cout << "\t[INFO] Sorting [0-4000]" << '\n';
                    dumpArray(*arrBig);
                    runTest(arrBig, results);

                    std::cout << "\t[INFO] Sorting [AlmostSorted]" << '\n';
                    dumpArray(*arrAlmostSorted);
                    runTest(arrAlmostSorted, results);

                    std::cout << "\t[INFO] Sorting [ReverseSorted]" << '\n';
                    dumpArray(*arrReverseSorted);
                    runTest(arrReverseSorted, results);
                }

                return results;
            }
        };
    }

    namespace data {
        class Exporter {
        private:
            std::vector<std::string> headers_;
            std::string delimiter_;

            void writeHeaders(std::ofstream &f) {
                for (const auto &header : headers_) {
                    f << header << delimiter_;
                }
            }

        public:
            Exporter(std::vector<std::string> headers, std::string delimiter) {
                this->headers_ = headers;
                this->delimiter_ = delimiter;
            }

            void saveToFile(std::string filename, std::vector<benchmark::test::Result> &arr) {
                std::ofstream f(filename);
                writeHeaders(f);

                int currentSize = -1;
                for (const auto &item : arr) {
                    if (item.arraySize != currentSize) {
                        currentSize = item.arraySize;
                        f << '\n' << std::to_string(currentSize) << delimiter_;
                    }
                    f << std::to_string(item.elapsedTime) << delimiter_;
                }
            }
        };
    }
}