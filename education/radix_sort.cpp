#include <iostream>
#include <vector>
#include <algorithm>

void counting_sort_for_digits(const std::vector<uint32_t>& src, std::vector<std::uint32_t>& dst, unsigned shift, std::uint32_t mask) {
    std::vector<std::size_t> count(std::size_t{mask} + 1, 0);

    for (std::size_t i = 0; i < src.size(); i++) count[(src[i] >> shift) & mask]++;
    for (std::size_t i = 1; i < count.size(); i++) count[i] += count[i - 1];

    for (std::size_t i = src.size(); i-- > 0; ) {
        std::uint32_t digit = (src[i] >> shift) & mask;
        dst[count[digit] - 1] = src[i];
        count[digit]--;
    }
}


void radix_sort(std::vector<int32_t>& arr) {
    const std::size_t n = arr.size();
    if (n <= 1) return;

    const auto [min_it, max_it] = std::minmax_element(arr.begin(), arr.end());
    const std::uint32_t base = static_cast<std::uint32_t>(*min_it);
    const std::uint32_t max_key = static_cast<std::uint32_t>(*max_it) - base;

    const unsigned b = static_cast<unsigned>(std::bit_width(max_key)) - 1;
    if (b == 0) return;

    const unsigned log_n = static_cast<unsigned>(std::bit_width(n)) - 1;
    const unsigned r = std::min(b, log_n);
    const std::uint32_t mask = (r == 32) ? ~std::uint32_t{0} : (std::uint32_t{1} << r) - 1;

    std::vector<std::uint32_t> keys(n);
    for (std::size_t i = 0; i < n; i++) keys[i] = static_cast<std::uint32_t>(arr[i]) - base;
    
    std::vector<std::uint32_t> buffer(n);
    for (unsigned shift = 0; shift < b; shift += r) {
        counting_sort_for_digits(keys, buffer, shift, mask);
        keys.swap(buffer);
    }

    for (std::size_t i = 0; i < n; i++) arr[i] = static_cast<std::int32_t>(keys[i] + base);
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