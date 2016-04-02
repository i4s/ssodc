#include "header.hpp"
#include <Windows.h> 

int main()
{
    int origin, type;
    std::string text;

    std::cout << "Enter a number (origin): ";
    std::cin >> origin;

    std::cout << "Enter a number (type): ";
    std::cin >> type;
  
    std::cout << "Enter text here: ";
    std::cin >> text;

    // Вызываем функции интерфейса, некоторые аргументы взяты
    // просто по принципу совпадения типа данных аргумента функции
    // исключительно в целях проверки корректного вывода.

    get_origin(text);
    get_type(text);

    put_alert(origin, type, text);

    get_alert(origin, type, text);
    get_alerts(origin, type);
    get_alerts(origin);

    remove_alert(origin, type, text);
    remove_alerts(origin, type);
    remove_alerts(origin);

    clear_alert(origin);

    save_alert(origin, type, text);
    ignore_alert(origin, type, text, type);

    system("pause");
    return 0;
}