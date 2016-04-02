#pragma once

/************************************ LIBRARIES ************************************/

#include <iostream>	
#include <ctime>
#include <string>

/************************************ INTERFACE ************************************/

// ��������� ������ �� config.json
int get_origin(std::string);
int get_type(std::string);

// ������� alert
int put_alert(int origin, int type, std::string json_subkey);

// �������� alerts
int get_alert(int origin, int type, std::string json_subkey);
int get_alerts(int origin, int type);
int get_alerts(int origin);

// ������� �����
int remove_alert(int origin, int type, std::string json_subkey);
int remove_alerts(int origin, int type);
int remove_alerts(int origin);

// ������� alert � CLEARED
int clear_alert(int key);


/************************************ BACKEND ************************************/

// ��������� alert
int save_alert(int origin, int type, std::string json_subkey);

// ������������ alert �� ����� ignore_time
int ignore_alert(int origin, int type, std::string json_subkey, time_t ignore_time);
  
