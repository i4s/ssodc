#include "base_sql_connection.hpp"

namespace ssodc {
namespace database_controller {

base_sql_connection::base_sql_connection()
{
	this->db_name = "dbname=testdb ";
    this->user_name = " user=";
    this->user_password = " password=";
    this->hostaddr = " hostaddr=";
    this->port = " port=";
}
base_sql_connection::base_sql_connection(std::string user_name, std::string user_password, \
	std::string hostaddr, std::string port)
{
    this->contain_conn_str(user_name, user_password, hostaddr, port);
    std::cout << connection_string << std::endl;
    try
    {
        pqxx::connection C(this->connection_string);
        if(!this->check_connection(C)) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
        }
        C.disconnect();
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what) 
        exit(EXIT_FAILURE);
    }
}
void base_sql_connection::create_user(std::string user_name, std::string user_password, \
    std::string hostaddr, std::string port)
{
    this->contain_conn_str(user_name, user_password, hostaddr, port);
    std::cout << connection_string << std::endl;
    try 
    {
        pqxx::connection C(this->connection_string);
        if(!this->check_connection(C)) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
        }
        C.disconnect();
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        exit(EXIT_FAILURE);
    }
}
void base_sql_connection::create_table(std::string table_charact)
{
    try
    {
        pqxx::connection C(connection_string);
        if(!this->check_connection(C)) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
        }
        pqxx::work W(C);
        W.exec(table_charact);
        W.commit();
        std::cout << "Table created successfully" << std::endl;
        C.disconnect();
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        exit(EXIT_FAILURE);
    }
}
void base_sql_connection::insert_to_table(std::string table_info)
{
    try
    {
        pqxx::connection C(connection_string);
        if(!this->check_connection(C)) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
        }
        pqxx::work W(C);
        W.exec(table_info);
        W.commit();
        std::cout << "Records created successfully" << std::endl;
        C.disconnect();
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        exit(EXIT_FAILURE);
    }
}
void base_sql_connection::select_from_table(UCI number_of_table)
{
    try
    {
        pqxx::connection C(connection_string);
        if(!this->check_connection(C)) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
        }
        this->command_ = "SELECT * from " + tables_names[number_of_table];
        pqxx::nontransaction N(C);
    
        pqxx::result R(N.exec(this->command_));
     
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); c++) 
        {
            std::cout << tables_charact[number_of_table] 
                << c[0].as<int>() << std::endl;
            std::cout << tables_charact[number_of_table] 
                << c[1].as<std::string>() << std::endl;
            //TODO(for me): initialization the object with appropriate type,  
            //setting info 
        }
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        exit(EXIT_FAILURE);
    }
}
void base_sql_connection::update_table(std::string changing_info, \
    UCI number_of_table, std::string ID)
{
    try
    {
        pqxx::connection C(connection_string);
        if(!this->check_connection(C)) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
        }
        pqxx::work W(C);
        this->command_ = "UPDATE " + tables_names[number_of_table] + \
            " set SOURCE_PATH = " + changing_info + " where ID=" + ID;
        W.exec(this->command_);
        W.commit();
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        exit(EXIT_FAILURE);
    }     
}
void base_sql_connection::delete_from_table(UCI number_of_table, std::string ID)
{
    try
    {
        pqxx::connection C(connection_string);
        if(!this->check_connection(C)) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
        }
        pqxx::work W(C);
        this->command_ = "DELETE from " + tables_names[number_of_table] \
            + " where ID=" + ID;
        W.exec(command_);
        W.commit();
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        exit(EXIT_FAILURE);
    }
}

bool base_sql_connection::check_connection(pqxx::connection& C)
{
    return (C.is_open()) ? true : false;
}
void base_sql_connection::contain_conn_str(std::string user_name, \
    std::string user_password, std::string hostaddr, std::string port)
{
    this->db_name = "dbname=testdb";
    this->user_name = " user=" + user_name;
    this->user_password = " password=" + user_password;
    this->hostaddr = " hostaddr=" + hostaddr;
    this->port = " port=" + port;
    this->connection_string = this->db_name + this->user_name + \
        this->user_password + this->hostaddr + this->port;
}

base_sql_connection::~base_sql_connection()
{
}

}
}
