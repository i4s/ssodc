#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <iostream>
#include <string>
#include <pqxx/pqxx> 

//using namespace std;
//using namespace pqxx;

namespace ssodc {
namespace database_controller {

/**
*common for all namespace constants
*/

const std::string tables_names[] = { "BASE_PICTURE",
    "PICTURE_PARTS_COORDS",
    "PICTURE_PARTS_ARRAY",
    "CLUSTER_STATUS",
    "CLUSTER_NODE_STATUS",
    "TASK_STATUS"
};
const std::string tables_charact[] = { "CREATE TABLE BASE_PICTURE("  \
    "ID INT PRIMARY KEY     NOT NULL," \
    "SOURCE_PATH    CHAR(80) );"
};
const int num_of_charact[] = {
    2
};

typedef unsigned const int UCI;

/**
*base class with sql server connection 
*/

class base_sql_connection 
{
protected:
	std::string db_name;
    std::string user_name;
    std::string user_password;
    std::string hostaddr;
    std::string port;
    std::string connection_string;
    std::string command_;
public:
    base_sql_connection();
    base_sql_connection(std::string, std::string, std::string, std::string);
    
    /**
    *database interface methods
    */

    void create_user(std::string, std::string, std::string, std::string);
    void create_table(std::string);
    void insert_to_table(std::string);
    void select_from_table(UCI);
    void update_table(std::string, UCI, std::string);
    void delete_from_table(UCI, std::string);

    /**
    *subsidiary methods
    */

    bool check_connection(pqxx::connection& C);
    void contain_conn_str(std::string, std::string, std::string, std::string);
    ~base_sql_connection();
};

}
}