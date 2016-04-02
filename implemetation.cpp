#include "header.hpp"

int get_origin(std::string str)
{
    std::cout << "\"get_origin\" output: ";
    std::cout << str;
    std::cout << std::endl;

    return 0;
}

int get_type(std::string str)
{
    std::cout << "\"get_type\" output: ";
    std::cout << str;
    std::cout << std::endl;

    return 0;
}

int put_alert(int origin, int type, std::string json_subkey)
{
    std::cout << "\"put_alert\" output: ";
    std::cout << origin << " " << type << " " << json_subkey;
    std::cout << std::endl;

    return 0;
}

int get_alert(int origin, int type, std::string json_subkey)
{
    std::cout << "\"get_alert\" output: ";
    std::cout << origin << " " << type << " " << json_subkey;
    std::cout << std::endl;

    return 0;
}

int get_alerts(int origin, int type)
{
    std::cout << "\"get_alerts\" output: ";
    std::cout << origin << " " << type;
    std::cout << std::endl;

    return 0;
}

int get_alerts(int origin)
{
    std::cout << "\"get_alerts\" output: ";
    std::cout << origin;
    std::cout << std::endl;

    return 0;
}

int remove_alert(int origin, int type, std::string json_subkey)
{
    std::cout << "\"remove_alert\" output: ";
    std::cout << origin << " " << type << " " << json_subkey;
    std::cout << std::endl;

    return 0;
}

int remove_alerts(int origin, int type)
{
    std::cout << "\"remove_alerts\" output: ";
    std::cout << origin << " " << type;
    std::cout << std::endl;

    return 0;
}

int remove_alerts(int origin)
{
    std::cout << "\"remove_alerts\" output: ";
    std::cout << origin;
    std::cout << std::endl;

    return 0;
}

int clear_alert(int key)
{
    std::cout << "\"clear_alert\" output: ";
    std::cout << key;
    std::cout << std::endl;

    return 0;
}

int save_alert(int origin, int type, std::string json_subkey)
{
    std::cout << "\"save_alert\" output: ";
    std::cout << origin << " " << type << " " << json_subkey;
    std::cout << std::endl;

    return 0;
}

int ignore_alert(int origin, int type, std::string json_subkey, time_t ignore_time)
{
    std::cout << "\"ignore_alert\" output: ";
    std::cout << origin << " " << type << " " << json_subkey;
    std::cout << std::endl;

    return 0;
}
