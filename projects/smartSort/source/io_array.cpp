#include <iostream>
#include "io_array.hpp"

void IOArray::print_array(int arr[],const int& arr_size) {
    std:: cout << "result of sorting" << "\n";
    for (int i = 0 ; i < arr_size ; i++) {
        std::cout << arr[i] << " ";}
    std::cout << "\n";
}