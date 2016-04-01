#pragma once

/************************************ LIBRARIES ************************************/

#include <iostream>	
#include <ctime>

using namespace std;


/************************************ INTERFACE ************************************/

// ��������� ������ �� config.json
int get_origin(string);
int get_type(string);

// ������� alert
int put_alert(int origin, int type, string json_subkey);

// �������� alerts
int get_alert(int origin, int type, string json_subkey);
int get_alerts(int origin, int type);
int get_alerts(int origin);

// ������� �����
int remove_alert(int origin, int type, string json_subkey);
int remove_alerts(int origin, int type);
int remove_alerts(int origin);

// ������� alert � CLEARED
int clear_alert(int key);


/************************************ BACKEND ************************************/

// ��������� alert
int save_alert(int origin, int type, string json_subkey);

// ������������ alert �� ����� ignore_time
int ignore_alert(int origin, int type, string json_subkey, time_t ignore_time);
  
