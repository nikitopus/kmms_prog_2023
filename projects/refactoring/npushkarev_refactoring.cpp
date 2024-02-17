#include <iostream>
#include <random>

void invert_array(int *arr, const int n);
void init_array(int *arr, const int array_size, const int max_value);
void print_array(const char *const comment, int *arr, const int n);

int main()
{
    const int array_size = 20;
    const int max_value = 100;
    int arr[array_size];

    init_array(arr, array_size, max_value);

    print_array("Random array:", arr, array_size);

    invert_array(arr, array_size);

    print_array("Array inverse:", arr, array_size);

    return 0;
}

void invert_array(int *arr, const int n)
{
    int buff;
    for (int i = 0; i < n / 2; i++)
    {
        buff = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = buff;
    }
}

void print_array(const char *const comment, int *arr, const int n)
{
    const char space = ' ';
    std::cout << comment << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << space;
    }
    std::cout << std::endl;
}

void init_array(int *arr, const int array_size, const int max_value)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dis(0, max_value);
    for (int i = 0; i < array_size; i++)
    {
        arr[i] = dis(mt);
    }
}
