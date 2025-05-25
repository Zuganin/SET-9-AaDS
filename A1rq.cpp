//
// Created by Vadim Zenin on 25/05/2025.
//

#include "A1rq.h"
#include <iostream>
#include <cassert>
#include <compare>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <utility>
#include <vector>
#include "A1q.h"
extern size_t charComparisons;

int alphabet = 74;

int charAt(const std::string& s, int d) {
    ++charComparisons;
    return d < s.size() ? static_cast<unsigned char>(s[d]) : -1;
}



void RadixSort(std::vector<std::string>& arr, int left, int right, int d) {
    if (right - left <= alphabet) {
        StringQuickSort(arr, left, right - 1);
        return;
    }
    const int R = 256;
    std::vector<int> count(R + 2, 0);
    for (int i = left; i < right; ++i)
        count[charAt(arr[i], d) + 2]++;
    for (int r = 0; r < R + 1; ++r)
        count[r + 1] += count[r];
    std::vector<std::string> aux(right - left);
    for (int i = left; i < right; ++i)
        aux[count[charAt(arr[i], d) + 1]++] = arr[i];
    for (int i = 0; i < right - left; ++i)
        arr[left + i] = aux[i];
    for (int r = 0; r < R; ++r)
        if (count[r + 1] > count[r])
            RadixSort(arr, left + count[r], left + count[r + 1], d + 1);
}