#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include <iostream>
#include <string>
#include <vector>
#include "hw5_output.hpp"
using namespace std;
using namespace output;


class Param {
public:
	string id;
	string type;
	int offset;
	//string reg;
    //string label;
	//for function
	vector<string> argument;
	string return_type;
	//constructors
	Param(string id_v, string type_v) : id(id_v), type(type_v){}
	Param(string id_v, string type_v, int offset_v) : id(id_v), type(type_v), offset(offset_v) {}
	Param(string id_v, string type_v, string ret_type) : id(id_v), type(type_v), offset(0), return_type(ret_type) {}
	Param(const Param& p) : id(p.id), type(p.type), offset(p.offset), argument(p.argument), return_type(p.return_type) {}

	void add_argument(string t);

	void print_param();
};

class SymbolTable {
public:
	string scope_type;
	vector<Param> paramaters;
	vector<int>ofsset;
	int local_variable_offset;
	int argument_offset;
	SymbolTable(string str) : scope_type(str) {}

	SymbolTable(string str, int local_of, int argument_of) {
		scope_type = str;
		local_variable_offset = local_of;
		argument_offset = argument_of;
	}
	//checks if there is a while scope from the current to parents
	int add_variable_id(string id_name, string type);
	void add_param_id(string id_name, string type);

};

class StackClass {
public:
	vector<SymbolTable> tables_stack;
	vector<int> offsets_stack;
	void add_scope(string type);
	void remove_scope();
	int insert_id(string id_name, string type);
	bool add_func(string id_name, string type);
	/********************************************************************************************/
	string update(string type);
	string print_arguments();
	bool insert_param_for_func(string id_name, string type);
	bool symbol_tables_contains(string name);
	bool symbol_tables_contains_function(string name);
	Param* get_param(string name);
	Param* get_function(string name);
	bool check_after_while();
};

#endif