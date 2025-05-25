#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <vector>
#include <string>
#include <cassert>
#include "A1m.h"
#include "A1q.h"
#include "A1rq.h"
#include "A1r.h"


// Глобальная переменная для подсчета сравнений
size_t charComparisons = 0;
// Компаратор с подсчетом посимвольных сравнений
struct CountingComparator {
    bool operator()(const std::string& a, const std::string& b) const {
        size_t minLen = std::min(a.size(), b.size());
        for (size_t i = 0; i < minLen; ++i) {
            ++charComparisons;
            if (a[i] < b[i]) return true;
            if (a[i] > b[i]) return false;
        }
        return a.size() < b.size();
    }
};



class StringGenerator {
public:
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#%:;^&*()-";

    // Генерирует случайную строку длиной length
    std::string generateRandomString(int length =10) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, alphabet.size() - 1);

        std::string result;
        for (int i = 0; i < length; ++i) {
            result += alphabet[distrib(gen)];
        }
        return result;
    }
    // Генерирует вектор из count случайных строк длиной length
    std::vector<std::string> generateRandomVectorOfString(int count = 100, int length = 10) {
        std::vector<std::string> results;
        for (int i = 0; i < count; ++i) {
            results.push_back(generateRandomString(length));
        }
        return results;
    }
    // Свапает 5 процентов строк в векторе
    std::vector<std::string> swapStringInVector(std::vector<std::string>& vec) {
        std::sort(vec.begin(), vec.end());
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, vec.size() - 1);

        int swapCount = static_cast<int>(vec.size() * 0.05);
        for (int i = 0; i < swapCount; ++i) {
            int idx1 = distrib(gen);
            int idx2 = distrib(gen);
            if (idx1 != idx2) {
                std::swap(vec[idx1], vec[idx2]);
            }
        }
        return vec;
    }
    // Генерирует обратно отсортированный массив
    std::vector<std::string> generateReverseSorted(int size, int length = 10) {
        auto vec = generateRandomVectorOfString(size, length);
        std::sort(vec.begin(), vec.end());
        std::reverse(vec.begin(), vec.end());
        return vec;
    }

    // Генерирует почти отсортированный массив
    std::vector<std::string> generateAlmostSorted(int size, int length = 10) {
        auto vec = generateRandomVectorOfString(size, length);
        std::sort(vec.begin(), vec.end());
        swapStringInVector(vec); // свапает 5% элементов
        return vec;
    }
};

class StringSortTester {
public:
    // Измени тип времени на микросекунды
    using micros = std::chrono::microseconds;

    void writeResultToCSV(const std::string& filename, int arraySize, double timeMs, size_t comparisons) {
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << arraySize << "," << timeMs << "," << comparisons << "\n";
            file.close();
        } else {
            std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
        }
    }

    template<typename SortFunc>
    void averageSortResults(const std::vector<std::string>& arr, SortFunc sortFunc, int runs, const std::string& csvFile) {
        double totalTime = 0;
        size_t totalComparisons = 0;

        for (int i = 0; i < runs; ++i) {
            std::vector<std::string> copy = arr;
            charComparisons = 0;
            auto start = std::chrono::high_resolution_clock::now();
            sortFunc(copy.begin(), copy.end(), CountingComparator());
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration_cast<micros>(end - start).count();
            totalComparisons += charComparisons;
        }

        double avgTime = totalTime / runs;
        size_t avgComparisons = totalComparisons / runs;
        writeResultToCSV(csvFile, arr.size(), avgTime, avgComparisons);
    }
    void averageMergeSortResults(const std::vector<std::string>& arr, int runs, const std::string& csvFile) {
        double totalTime = 0;
        size_t totalComparisons = 0;

        for (int i = 0; i < runs; ++i) {
            std::vector<std::string> copy = arr;
            charComparisons = 0;
            auto start = std::chrono::high_resolution_clock::now();
            stringMergeSort(copy, 0, copy.size() - 1);
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration_cast<micros>(end - start).count();
            totalComparisons += charComparisons;
        }

        double avgTime = totalTime / runs;
        size_t avgComparisons = totalComparisons / runs;
        writeResultToCSV(csvFile, arr.size(), avgTime, avgComparisons);
    }
    void averageQuickSortResults(const std::vector<std::string>& arr, int runs, const std::string& csvFile) {
        double totalTime = 0;
        size_t totalComparisons = 0;

        for (int i = 0; i < runs; ++i) {
            std::vector<std::string> copy = arr;
            charComparisons = 0;
            auto start = std::chrono::high_resolution_clock::now();
            StringQuickSort(copy, 0, copy.size() - 1);
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration_cast<micros>(end - start).count();
            totalComparisons += charComparisons;
        }

        double avgTime = totalTime / runs;
        size_t avgComparisons = totalComparisons / runs;
        writeResultToCSV(csvFile, arr.size(), avgTime, avgComparisons);
    }
    void averageMSDRadixSortResults(const std::vector<std::string>& arr, int runs, const std::string& csvFile) {
        double totalTime = 0;
        size_t totalComparisons = 0;

        for (int i = 0; i < runs; ++i) {
            std::vector<std::string> copy = arr;
            charComparisons = 0;
            auto start = std::chrono::high_resolution_clock::now();
            MsdRadixSort(copy, 0, copy.size(), 0);
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration_cast<micros>(end - start).count();
            totalComparisons += charComparisons;
        }

        double avgTime = totalTime / runs;
        size_t avgComparisons = totalComparisons / runs;
        writeResultToCSV(csvFile, arr.size(), avgTime, avgComparisons);
    }
    void averageRadixSortResults(const std::vector<std::string>& arr, int runs , const std::string& csvFile) {
        double totalTime = 0;
        size_t totalComparisons = 0;

        for (int i = 0; i < runs; ++i) {
            std::vector<std::string> copy = arr;
            charComparisons = 0;
            auto start = std::chrono::high_resolution_clock::now();
            RadixSort(copy, 0, copy.size() - 1, 0);
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration_cast<micros>(end - start).count();
            totalComparisons += charComparisons;
        }

        double avgTime = totalTime / runs;
        size_t avgComparisons = totalComparisons / runs;
        writeResultToCSV(csvFile, arr.size(), avgTime, avgComparisons);
    }
};







int main() {
    std::vector<std::string> randomStrings;
    std::vector<std::string> almostSortStrings;
    std::vector<std::string> reverseSortStrings;
    StringGenerator generator;
    StringSortTester tester;
    randomStrings = generator.generateRandomVectorOfString(3000, 200);
    almostSortStrings = generator.generateAlmostSorted(3000, 200);
    reverseSortStrings = generator.generateReverseSorted(3000, 200);
    // std::string QuickSortFile1 = "quickSort_random_results.csv";
    // std::string QuickSortFile2 = "quickSort_almost_results.csv";
    // std::string QuickSortFile3 = "quickSort_reverse_results.csv";
    // std::string MergeSortFile1 = "mergeSort_random_results.csv";
    // std::string MergeSortFile2 = "mergeSort_almost_results.csv";
    // std::string MergeSortFile3 = "mergeSort_reverse_results.csv";

    // for (int size = 100; size <= 3000; size += 100) {
    //     std::vector<std::string> subvec(randomStrings.begin(), randomStrings.begin() + size);
    //     tester.averageSortResults(subvec, [](auto begin, auto end, auto comp) { std::sort(begin, end, comp); }, 1, QuickSortFile1);
    //     tester.averageSortResults(subvec, [](auto begin, auto end, auto comp) { std::stable_sort(begin, end, comp); }, 1, MergeSortFile1);
    //     std::cout << size << std::endl;
    // }
    // for (int size = 100; size <= 3000; size += 100) {
    //     std::vector<std::string> subvec = generator.generateAlmostSorted(size, 200);
    //     tester.averageSortResults(subvec, [](auto begin, auto end, auto comp) { std::sort(begin, end, comp); }, 1, QuickSortFile2);
    //     tester.averageSortResults(subvec, [](auto begin, auto end, auto comp) { std::stable_sort(begin, end, comp); }, 1, MergeSortFile2);
    //     std::cout << size << std::endl;
    // }
    // for (int size = 100; size <= 3000; size += 100) {
    //     std::vector<std::string> subvec(reverseSortStrings.begin(), reverseSortStrings.begin() + size);
    //     tester.averageSortResults(subvec, [](auto begin, auto end, auto comp) { std::sort(begin, end, comp); }, 1, QuickSortFile3);
    //     tester.averageSortResults(subvec, [](auto begin, auto end, auto comp) { std::stable_sort(begin, end, comp); }, 1, MergeSortFile3);
    //     std::cout << size << std::endl;
    // }

    std::string StringMergeSortFile1 = "stringMergeSort_random_results.csv";
    std::string StringMergeSortFile2 = "stringMergeSort_almost_results.csv";
    std::string StringMergeSortFile3 = "stringMergeSort_reverse_results.csv";
    std::string StringQuickSortFile1 = "stringQuickSort_random_results.csv";
    std::string StringQuickSortFile2 = "stringQuickSort_almost_results.csv";
    std::string StringQuickSortFile3 = "stringQuickSort_reverse_results.csv";
    std::string MsdRadixSortFile1 = "MsdRadixSort_random_results.csv";
    std::string MsdRadixSortFile2 = "MsdRadixSort_almost_results.csv";
    std::string MsdRadixSortFile3 = "MsdRadixSort_reverse_results.csv";
    std::string RadixSortFile1 = "RadixSort_random_results.csv";
    std::string RadixSortFile2 = "RadixSort_almost_results.csv";
    std::string RadixSortFile3 = "RadixSort_reverse_results.csv";

    for (int size = 100; size <= 3000; size += 100) {
        std::vector<std::string> subvec(randomStrings.begin(), randomStrings.begin() + size);
        tester.averageMergeSortResults(subvec, 1000, StringMergeSortFile1);
        tester.averageQuickSortResults(subvec, 1000, StringQuickSortFile1);
        tester.averageMSDRadixSortResults(subvec, 1000, MsdRadixSortFile1);
        tester.averageRadixSortResults(subvec, 1000, RadixSortFile1);
        std::cout << size << std::endl;
    }
    for (int size = 100; size <= 3000; size += 100) {
        std::vector<std::string> subvec = generator.generateAlmostSorted(size, 200);
        tester.averageMergeSortResults(subvec,1000, StringMergeSortFile2);
        tester.averageQuickSortResults(subvec, 1000, StringQuickSortFile2);
        tester.averageMSDRadixSortResults(subvec, 1000, MsdRadixSortFile2);
        tester.averageRadixSortResults(subvec, 1000, RadixSortFile2);
        std::cout << size << std::endl;
    }
    for (int size = 100; size <= 3000; size += 100) {
        std::vector<std::string> subvec(reverseSortStrings.begin(), reverseSortStrings.begin() + size);
        tester.averageMergeSortResults(subvec, 1000, StringMergeSortFile3);
        tester.averageQuickSortResults(subvec, 1000, StringQuickSortFile3);
        tester.averageMSDRadixSortResults(subvec, 1000, MsdRadixSortFile3);
        tester.averageRadixSortResults(subvec, 1000, RadixSortFile3);
        std::cout << size << std::endl;
    }


    std::cout << "Результаты записаны в CSV файлы." << std::endl;
    return 0;
}