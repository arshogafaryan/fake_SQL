#ifndef FAKE_SQL
#define FAKE_SQL

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

extern std::vector<std::string> buffer;

struct User
{
	std::string name;
	std::string surname;
	std::string age;
};

struct Data
{
	User u;
	User changable_u;
	std::string Command_Name;
	std::string File_Name;

	Data()
	{
		Command_Name = "NIL";
		File_Name = "NIL";
   		u.name = "NIL";
		u.surname = "NIL";
		u.age = "NIL";
		changable_u.name = "NIL";
		changable_u.surname = "NIL";
		changable_u.age = "NIL";
	};
};

std::ostream& operator<<(std::ostream& os, Data& d);
std::vector<std::string> split(const std::string &str, const char* c);
void parse_from_input(Data& d);
void get_operation(Data& d);
void fill_in_buffer(Data& d);
void fill_in_file(Data& d);
void delete_by_name(const std::string name);
void find_by_name(std::string name);
void update_anything(std::string name, std::string replace_with);
void insert_into_file(Data& d);
void SELECT(Data &d);
void UPDATE(Data &d);
void DELETE(Data &d);
void INSERT_INTO(Data &d);


#endif
