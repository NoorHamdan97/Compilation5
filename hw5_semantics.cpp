#include "hw5_semantics.hpp"
#include <sstream>


//add argument with type t to the argument list of the function 
void Param::add_argument(string t) {
	argument.push_back(t);
}

//print the parametrer
void Param::print_param() {
	vector<string> new_argument;
	for (string str : argument) {
			new_argument.push_back(str);
	}
	if (type == "function") {
		printID(id, offset, makeFunctionType(return_type, new_argument));
	}
	else {
			printID(id, offset, type);
	}
}

void SymbolTable::add_param_id(string id_name, string type) {
	Param p(id_name, type, argument_offset);
	argument_offset--;
	paramaters.push_back(p);
}

int SymbolTable::add_variable_id(string id_name, string type) {
	Param p(id_name, type, local_variable_offset);
	int temp = local_variable_offset;
	local_variable_offset++;
	paramaters.push_back(p);
	return temp;
}

//add a new symbolTable for a new scope with type "type"
void StackClass::add_scope(string type) {
	if (type == "global_scope" && tables_stack.size() == 0) {
		SymbolTable new_s(type, 0, -1);
		offsets_stack.push_back(0);
		tables_stack.push_back(new_s);
	}
	else {
		int size = offsets_stack.size();
		SymbolTable new_s(type, offsets_stack[size - 1], -1);
		offsets_stack.push_back(offsets_stack[size - 1]);
		tables_stack.push_back(new_s);
	}
}

//remove the symbolTable of the last scope from the tables_stack 
void StackClass::remove_scope() {
	int size = tables_stack.size();
	if (size == 0) {
		return;
	}
	//endScope();
	tables_stack.pop_back();
	offsets_stack.pop_back();
}

int StackClass::insert_id(string id_name, string type) {
	int size = offsets_stack.size();
	offsets_stack[size - 1] += 1;
	size = tables_stack.size();
	int offset = tables_stack[size - 1].add_variable_id(id_name, type);
	return offset;
}


bool StackClass::add_func(string id_name, string type) {
	Param f(id_name, "function", type);
	if (id_name == "print") {
		f.argument.push_back("STRING");
	}
	if (id_name == "printi") {
		f.argument.push_back("INT");
	}
	tables_stack[0].paramaters.push_back(f);
	return true;
}


bool StackClass::insert_param_for_func(string id_name, string type) {
	int size = tables_stack[0].paramaters.size();
	tables_stack[0].paramaters[size - 1].add_argument(type);
	size = tables_stack.size();
	tables_stack[size - 1].add_param_id(id_name, type);
	return true;
}

string StackClass::update(string type)
{
	if (type == "BOOL")
		return "i1";
	if (type == "BYTE")
		return "i8";
	if (type == "VOID")
		return "void";
	return "i32";
}

string StackClass::print_arguments() {
	stringstream res;
	int size1 = tables_stack[0].paramaters.size();
	int size = tables_stack[0].paramaters[size1 - 1].argument.size();
	res << "(";
	for (int i = 0; i < size; ++i) {
		res << update(tables_stack[0].paramaters[size1 - 1].argument[i]);
		if (i + 1 < size)
			res << ",";
	}
	res << ")";
	return res.str();

}


//checks if there is a parameter witch is not a function with the name "name" in all the scope we start checking from the current scope 
bool StackClass::symbol_tables_contains(string name) {
	int table_size = tables_stack.size();
	if (table_size == 0) {
		return false;
	}
	for (int i = table_size - 1; i >= 0; i--) {
		int param_size = tables_stack[i].paramaters.size();
		if (param_size == 0) {
			continue;
		}
		for (int j = 0; j < param_size; j++) {
			if (tables_stack[i].paramaters[j].type != "function"
				&& tables_stack[i].paramaters[j].id == name) {
				return true;
			}
		}
	}
	return false;
}

//checks if one of the scope is a while scope
bool StackClass::check_after_while() {
	int table_size = tables_stack.size();
	if (table_size == 0) {
		return false;
	}
	for (int i = table_size - 1; i >= 0; --i) {
		if (tables_stack[i].scope_type == "while") {
			return true;
		}
	}
	return false;
}


//checks if there is a function with the name "name" 
bool StackClass::symbol_tables_contains_function(string name) {
	int table_size = tables_stack.size();
	int param_size = tables_stack[0].paramaters.size();
	if (table_size == 0 || param_size == 0) {
		return false;
	}
	for (int i = 0; i < param_size; i++) {
		if (tables_stack[0].paramaters[i].type == "function"
			&& tables_stack[0].paramaters[i].id == name) {
			return true;
		}
	}
	return false;
}


//return the parametere withe the name "name" we are checking from the current scope 
//and if we didn't find it in the current scope we check in the older scope until we check in the root
Param* StackClass::get_param(string name) {
	int table_size = tables_stack.size();
	if (table_size == 0) {
		return NULL;
	}
	for (int i = table_size - 1; i >= 0; i--) {
		int param_size = tables_stack[i].paramaters.size();
		if (param_size == 0) {
			continue;
		}
		for (int j = 0; j < param_size; j++) {
			if (tables_stack[i].paramaters[j].id == name) {
				return &(tables_stack[i].paramaters[j]);
			}
		}
	}
	return NULL;
}

//return the fuction with the name "name"
Param* StackClass::get_function(string name) {
	int table_size = tables_stack.size();
	int param_size = tables_stack[0].paramaters.size();
	if (table_size == 0 || param_size == 0) {
		return NULL;
	}
	for (int i = 0; i < param_size; i++) {
		if (tables_stack[0].paramaters[i].type == "function"
			&& tables_stack[0].paramaters[i].id == name) {
			return &(tables_stack[0].paramaters[i]);
		}
	}
	return NULL;

}

