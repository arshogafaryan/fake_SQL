#include "fake_SQL.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

std::vector<std::string> buffer;

void parse_from_input(Data& d)
{
	std::string raw_text;
	std::cout << "Input into database (Read syntax documentation):\n";
	getline(std::cin, raw_text);
	std::vector<std::string> splt_text = split(raw_text, " ,:");
	if (splt_text[0] == "INSERT_INTO" && splt_text.size() == 5)
	{
		d.Command_Name = splt_text[0];
		d.File_Name = splt_text[1];
   		d.u.name = splt_text[2];
		d.u.surname = splt_text[3];
		d.u.age = splt_text[4];
	}
	else if (splt_text[0] == "SELECT" && splt_text.size() == 3)
	{
		d.Command_Name = splt_text[0];
		d.File_Name = splt_text[1];
		d.u.name = splt_text[2];
	}
	else if (splt_text[0] == "DELETE" && splt_text.size() == 3)
	{
		d.Command_Name = splt_text[0];
		d.File_Name = splt_text[1];
   		d.u.name = splt_text[2];
	}
	else if (splt_text[0] == "UPDATE" && splt_text.size() == 4)
	{
		d.Command_Name = splt_text[0];
		d.File_Name = splt_text[1];
		d.u.name = splt_text[2];
		d.changable_u.name = splt_text[3];
	}
	else
	{
		throw("ERROR,Invalid syntax.");
	}
}	

void get_operation(Data& d)
{
	if (d.Command_Name == "INSERT_INTO")
	{
		INSERT_INTO(d);
	}
	else if (d.Command_Name == "SELECT")
	{
		SELECT(d);
	}
	else if (d.Command_Name == "DELETE")
	{
		DELETE(d);
	}
	else if (d.Command_Name == "UPDATE")
	{
		UPDATE(d);
	}
	else
	{
		std::cerr << "Error - Invalid Command" << "\n";
	}
}

void find_by_name(const std::string name)
{
	std::vector<std::string> target;
	for (int i = 0; i < buffer.size(); ++i)
	{
		target = split(buffer[i], " :");
		if(target[0] == name)
		{
			std::cout << target[0] << ":" << target[1] << ":" << target[2] << "\n";
		}
	}
}

void delete_by_name(const std::string name)
{
	std::vector<std::string> target;
	for (int i = 0; i < buffer.size(); ++i)
	{
		target = split(buffer[i], " :");
		if(target[0] == name)
		{
			buffer[i].replace(0,buffer[i].size(),"*");
		}
	}
}

void update_name(std::string name, std::string replace_with)
{
	for (int i = 0; i < buffer.size(); ++i)
	{
		if (buffer[i].find(name) == 0)
		{
			buffer[i].replace(buffer[i].find(name), name.length(), replace_with);
		}
	}
}

void fill_in_file(Data& d)
{
	std::ofstream file;
	file.open(d.File_Name, std::ios_base::trunc);
	if (!file.is_open())
	{
		std::cerr << "Could not open the file - '"<< d.File_Name;
     	return;
	}
	for (int i = 0; i < buffer.size(); ++i)
	{
		file << buffer[i] << "\n";
	}
}

void fill_in_buffer(Data& d)
{
	std::fstream file;
	std::string line;
	file.open(d.File_Name);
	if (!file.is_open())
	{
		std::cerr << "Could not open the file - '"<< d.File_Name;
        return;
	}
	while (getline(file,line))
	{
		buffer.push_back(line);
	}
}

void insert_into_file(Data& d)
{
	std::fstream file;
	file.open(d.File_Name, std::ios_base::app);

	file << d.u.name << ":" << d.u.surname << ":" << d.u.age << "\n";
}

void INSERT_INTO(Data& d)
{
	insert_into_file(d);
}

void SELECT(Data& d)
{
	fill_in_buffer(d);
	find_by_name(d.u.name);
}

void DELETE(Data& d)
{
	fill_in_buffer(d);
	delete_by_name(d.u.name);
	fill_in_file(d);
}

void UPDATE(Data& d)
{
	fill_in_buffer(d);
	update_name(d.u.name, d.changable_u.name);
	fill_in_file(d);
}
	
