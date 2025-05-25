//
// Created by Vadim Zenin on 25/05/2025.
//

#include "A1q.h"
#include <cassert>
#include <compare>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <utility>
#include <vector>
#include "utils.h"
extern size_t charComparisons;
std::mt19937 rnd = std::mt19937{std::random_device{}()};

void StringQuickSort(std::vector<std::string>& arr, int left, int right) {
    if (left >= right) return;

    std::string pivot = arr[left + rnd() % (right - left + 1)];

    std::vector<std::string> r_less, r_equal, r_greater;

    for (int i = left; i <= right; ++i) {
        if (compareStrings(arr[i], pivot)) {
            r_less.push_back(arr[i]);
        } else if (compareStrings(arr[i], pivot)) {
            r_greater.push_back(arr[i]);
        } else {
            r_equal.push_back(arr[i]);
        }
    }

    int idx = left;
    for (const auto& s : r_less) arr[idx++] = s;
    for (const auto& s : r_equal) arr[idx++] = s;
    for (const auto& s : r_greater) arr[idx++] = s;

    StringQuickSort(arr, left, left + r_less.size() - 1);
    StringQuickSort(arr, right - r_greater.size() + 1, right);
}
