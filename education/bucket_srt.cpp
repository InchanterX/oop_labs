#include <iostream>
#include <vector>

void insertion_sort(std::vector<double>& arr) {
    std::size_t n = static_cast<std::size_t>arr.size();
    if (n <= 1) return;

    for (std::size_t i = 1; i < n; i++) {
        double key = arr[i];
        std::size_t j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j] = key;
    }
}

void print_array(const std::vector<double>& arr) {
    for (const auto& el : arr) {
        std::cout << el << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int32_t> arr{4.1, 3.4, 1.2, 5.4, 12.6, -3.3, 4.9};
    print_array(arr);
    insertion_sort(arr);
    print_array(arr);
    return 0;
}