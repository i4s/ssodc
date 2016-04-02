#pragma once

/************************************ LIBRARIES ************************************/

#include <iostream>	
#include <ctime>
#include <string>

/************************************ INTERFACE ************************************/

// Получение данных из config.json
int get_origin(std::string);
int get_type(std::string);

// Создать alert
int put_alert(int origin, int type, std::string json_subkey);

// Получить alerts
int get_alert(int origin, int type, std::string json_subkey);
int get_alerts(int origin, int type);
int get_alerts(int origin);

// Удалить алерт
int remove_alert(int origin, int type, std::string json_subkey);
int remove_alerts(int origin, int type);
int remove_alerts(int origin);

// Перевод alert в CLEARED
int clear_alert(int key);


/************************************ BACKEND ************************************/

// Сохранить alert
int save_alert(int origin, int type, std::string json_subkey);

// Игнорировать alert на время ignore_time
int ignore_alert(int origin, int type, std::string json_subkey, time_t ignore_time);
  
