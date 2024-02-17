#include <iostream>
#include "menu.hpp"
    
int menu::prompt_menu_input(){    
    int variant;
    std::cout << "Выберите вариант\n"
              << std::endl;
    std::cout << "1. просмотреть содержимое\n"
              << "2. найти минимальный объект\n"
              << "3. найти максимальный объект\n"
              << "4. отсортировать\n"
              << "5. найти среднее кол-во элементов\n"
              << "6. дополнить таблицу\n"
              << "7. выйти\n"
              << std::endl;
    std::cout << ">>> ";
    std::cin >> variant;
    return variant;
}