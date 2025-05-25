//
// Created by Vadim Zenin on 25/05/2025.
//


#include "A1m.h"
#include <vector>
#include <string>
#include <algorithm>
extern size_t charComparisons;

int lcpLength(const std::string& a, const std::string& b) {
    int len = 0;
    while (len < a.size() && len < b.size() && a[len] == b[len]) {
        ++charComparisons;
        ++len;
    }
    return len;
}


bool lcpCompare(const std::string& a, const std::string& b) {
    int lcp = lcpLength(a, b);
    if (lcp == a.size() && lcp == b.size()) return false;
    if (lcp == a.size()) return true;  // a - префикс b
    if (lcp == b.size()) return false; // b - префикс a

    ++charComparisons;
    int lcpA = lcpLength(a, b);
    int lcpB = lcpLength(b, a);
    if (lcpA != lcpB) return lcpA > lcpB;

    return a < b;
}


void merge(std::vector<std::string>& arr, int left, int mid, int right) {
    std::vector<std::string> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (lcpCompare(arr[i], arr[j])) {
            temp.push_back(arr[i++]);
        } else {
            temp.push_back(arr[j++]);
        }
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);
    for (int k = 0; k < temp.size(); ++k) {
        arr[left + k] = temp[k];
    }
}

void stringMergeSort(std::vector<std::string>& arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    stringMergeSort(arr, left, mid);
    stringMergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}