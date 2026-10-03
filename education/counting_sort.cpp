#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <array>

void counting_sort(std::vector<int32_t>& arr) {
    size_t arr_size = arr.size();
    if (arr_size <= 1) return;

    int32_t min_el = *std::min_element(arr.begin(), arr.end());
    for (std::size_t i = 0; i < arr_size; i++) arr[i] -= min_el;

    int32_t max_el = *std::max_element(arr.begin(), arr.end());
    std::vector<int64_t> count(max_el + 1, 0);
    for (std::size_t i = 0; i < arr_size; i++) count[arr[i]]++;
    for (std::size_t i = 1; i < count.size(); i++) count[i] += count[i - 1];

    std::vector<int32_t> result(arr_size);
    for (std::size_t i = arr_size; i-- > 0; ) {
        result[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (std::size_t i = 0; i < arr_size; i++) arr[i] = result[i] + min_el;
}

void strings_counting_sort(std::string& str) {
    size_t str_size = str.size();
    if (str_size <= 1) return;

    std::array<std::size_t, 256> count{};
    for (std::size_t i = 0; i < str_size; i++) count[static_cast<unsigned char>(str[i])]++;

    std::string result;
    for (std::size_t i = 0; i < count.size(); i++) {
        result += std::string(count[i], i);
    }

    for (std::size_t i = 0; i < str_size; i++) str[i] = result[i];
}

void print_array(const std::vector<int32_t> arr) {
    for (const auto& el : arr) {
        std::cout << el << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int32_t> arr{-2, 4, 10, 3, 534, -12, 42, 56, 12, -4};
    print_array(arr);
    counting_sort(arr);
    print_array(arr);

    std::string str = "cdaebn";
    std::cout << str << '\n';
    strings_counting_sort(str);
    std::cout << str << '\n';
    return 0;
}