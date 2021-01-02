#include <iostream>
#include <string>
#include <utility>
#include <vector>

enum vType
{
	t_null,
	t_num,
	t_string,
	t_bool,
	t_array,
	t_object
};

class Value
{
public:
	Value();
	Value(int n);
	Value(std::string str);
	Value(bool b);
	/*Getters */
	vType 		getType() 	{ return type;}
	int 			getNum() 	{ return n;}
	std::string getString()	{ return str;}
	bool 			getBool() 	{ return b;}
	Value* 		getNext() 	{ return next;}
	/*Setters */
	void setType (vType t) 				{ this->type = t;}
	void setNum(int n) 					{ this->n = n;}
	void setString (std::string str) { this->str = str;}
	void setBool(bool b) 				{ this->b = b;}
	void setNext(Value& v) 				{ this->next = &v;}

	std::string toString(void);
	/*<-------- Comparisson Operator Overloading------>*/
	Value &operator[](Value& v);
	Value &operator,(Value& v);
	Value &operator+(Value& v);
	Value &operator-(Value& v);
	Value &operator*(Value& v);
	Value &operator/(Value& v);
	Value &operator%(Value& v);
	Value &operator>(Value& v);
	Value &operator<(Value& v);
	Value &operator>=(Value& v);
	Value &operator<=(Value& v);
	Value &operator&&(Value& v);
	Value &operator||(Value& v);
	Value &operator!(void);
private:
	vType type;
	int n;
	std::string str;
	bool b;
	std::pair<Value*, Value*> pair;
	Value* next;
};

class Json
{
private:
	Value val;
public:
	Json() {}
	Value& getVal() 				{ return val;}
	Json &operator=(Value v) 	{val = v; return *this;}

	friend std::ostream &operator<<(std::ostream &os, Json &j)
	{
		Value* v = &j.getVal();
		os << "{";
		while (v) {
			if (v->getType() != t_array) {
				os << v->toString();
				if (v->getNext()) os << ", ";
			}
			v = v->getNext();
		}
		os << "}";
		os << std::endl;
		return os;
	}
};