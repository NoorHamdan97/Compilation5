#ifndef __IR_H_
#define __IR_H_

#include "bp.hpp"
#include "hw5_aux.hpp"
#include <iostream>

static int current = 0;
static int num = 0;

typedef std::pair<int, BranchLabelIndex> LabelPair;

class TempVar {
public:
	string name;
	int var_id;
	TempVar() {
		this->var_id = current++;
		string var_id_str = to_string(var_id);
		this->name = "%var_" + var_id_str;
		//add to symbol table
	}
};

class newLable {
	int current;
public:
	int val;
	newLable() {
		current = num;
		num++;
	}
	string name() {
		stringstream res;
		res << "@.string_" << current;
		return res.str();
	}
};


class Stmnt : public Node {
public:
	vector<LabelPair> breakList;
	vector<LabelPair> continueList;
	bool is_return;
	Stmnt(bool t = false) {
		is_return = t;
		breakList = vector<LabelPair>();
		continueList = vector<LabelPair>();
	}
};


class MarkerN : public Node {
public:
	vector<LabelPair> nextList; //go to location - bp
};


class Expression : public Node {
public:
	TempVar place;
	int val;
	vector<LabelPair> true_list;
	vector<LabelPair> false_list;
	bool is_param;
	Expression(string type1, string name = "a", bool is2 = true, int val1 = 0) {
		str = name;
		type = type1;
		val = val1;
		is_param = is2;
		place = TempVar();
	}
	Expression(Expression& exp) {
		str = exp.str;
		type = exp.type;
		place = exp.place;
		val = exp.val;
		true_list = vector<LabelPair>();
		false_list = vector<LabelPair>();
		is_param = exp.is_param;
	}
};


class ExpList : public Node {
public:
	int argument_frame_size;
	vector<string> types;
	vector<string> vars;
	ExpList() {
		argument_frame_size = 0;
		types = vector<string>();
		vars = vector<string>();
	}
};

class BranchClass {

public:
	static BranchClass* getInstance() {

		return (!m_instanceBranch) ?
			m_instanceBranch = new BranchClass :
			m_instanceBranch;
	}

private:
	// private constructor and destructor
	BranchClass() { cout << "BranchClass instance created!\n"; }
	~BranchClass() {}

	// private copy constructor and assignment operator
	BranchClass(const BranchClass&);
	BranchClass& operator=(const BranchClass&);

	static BranchClass *m_instanceBranch;
};

BranchClass* BranchClass::m_instanceBranch = nullptr;

#endif