#include <iostream>

#include "bubble_sort.hpp"
#include "io_array.hpp"

int main(){

    //TODO: array input
    int arr [] = {2,8,65,5};
    const int arr_size = std::size(arr);

    //TODO: sorting
    bubbleSort::sort(arr,arr_size);

    //TODO: output result
    IOArray::print_array(arr,arr_size);
}
