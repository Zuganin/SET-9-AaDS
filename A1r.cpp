//
// Created by Vadim Zenin on 25/05/2025.
//

#include "A1r.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <random>
extern size_t charComparisons;
int ascii = 256;
void MsdRadixSort(std::vector<std::string>& arr, int left, int right, int d) {
    if (right - left <= 1) return;

    std::vector<int> count(ascii + 2, 0);

    for (int i = left; i < right; ++i) {
        ++charComparisons;
        int c = (d < arr[i].size()) ? (unsigned char)arr[i][d] + 1 : 0;
        count[c + 1]++;
    }

    for (int r = 0; r < ascii + 1; ++r)
        count[r + 1] += count[r];

    std::vector<std::string> aux(right - left);
    for (int i = left; i < right; ++i) {
        ++charComparisons;
        int c = (d < arr[i].size()) ? (unsigned char)arr[i][d] + 1 : 0;
        aux[count[c]++] = std::move(arr[i]);
    }

    for (int i = 0; i < right - left; ++i)
        arr[left + i] = std::move(aux[i]);

    for (int r = 0; r < ascii + 1; ++r)
        MsdRadixSort(arr, left + count[r], left + count[r + 1], d + 1);
}