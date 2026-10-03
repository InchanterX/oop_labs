#include <iostream>
#include <vector>

void radix_sort(std::vector<int32_t>& arr) {

}


void print_array(const std::vector<int32_t>& arr) {
    for (const auto& el : arr) {
        std::cout << el << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int32_t> arr{942, 77, 105, 809, 748, 444, 3, 206, 812, 42, 5, 901};
    print_array(arr);


    return 0;
}