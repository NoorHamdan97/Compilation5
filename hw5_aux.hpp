#ifndef __PARSE_H_
#define __PARSE_H_

#include <string>
using namespace std;


typedef struct {
	string type;
	string str;
} Node;

class Num : public Node{
	public:
		Num(string str1) {
			str = str1;
			type = "INT";
		}
};

class Id : public Node{
	public:
		Id(string str1) {
			str = str1;
		}
};

class String: public Node{
	public:
		String(string str1) {
			str = str1;
			type = "STRING";
		}
};

class BinOp: public Node{
	public:
		BinOp(string str1) {
			str = str1;
		}
};

class MulOp: public Node{
	public:
		MulOp(string str1) {
			str = str1;
		}
};

class EqOp: public Node{
	public:
		EqOp(string str1) {
			str = str1;
		}
};

class RelOp: public Node{
	public:
		RelOp(string str1) {
			str = str1;
		}
};


#define YYSTYPE Node*
#endif