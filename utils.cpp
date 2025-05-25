//
// Created by Vadim Zenin on 25/05/2025.
//

#include "utils.h"
#include <algorithm>
#include <string>
#include <vector>
extern size_t charComparisons;

// Функция сравнения с подсчетом посимвольных сравнений (используется в собственных функциях из контеста)
bool compareStrings(const std::string& a, const std::string& b) {
    size_t minLen = std::min(a.size(), b.size());
    for (size_t i = 0; i < minLen; ++i) {
        ++charComparisons;
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return a.size() < b.size();
}
