#include <iostream>
#include <string>
#include <map>
#include <vector>

enum vType
{
	t_null,
	t_num,
	t_string,
	t_bool,
	t_array
};

class Value
{
public:
	Value();
	Value(int n);
	Value(std::string str);
	Value(bool b);
	vType getType();
	int getNum();
	std::string getString();
	std::string getBool();
	Value getNext();
	Value &operator[](Value &v);
	Value &operator,(Value &v);

private:
	vType type;
	int n;
	std::string str;
	bool b;
	std::vector<Value> v;
	Value *next;
};

class Json
{
private:
	Value val;
public:
	Json();
	Value getVal();
	Json &operator=(Value &v);
	friend std::ostream &operator<<(std::ostream &os, Json &j)
	{
		Value v = j.getVal();
		switch (v.getType())
		{
		case t_null:
			os << "NULL" << std::endl;
			break;
		case t_num:
			os << v.getNum() << std::endl;
			break;
		case t_string:
			os << v.getString() << std::endl;
			break;
		case t_bool:
			os << v.getBool() << std::endl;
			break;
		case t_array:
			break;
		}
		return os;
	}
	/*<-------- Comparisson Operator Overloading------>*/
	friend Json &operator+(Json &j1, Json &j2);
	friend Json &operator-(Json &j1, Json &j2);
	friend Json &operator*(Json &j1, Json &j2);
	friend Json &operator/(Json &j1, Json &j2);
	friend Json &operator%(Json &j1, Json &j2);
	friend Json &operator>(Json &j1, Json &j2);
	friend Json &operator<(Json &j1, Json &j2);
	friend Json &operator>=(Json &j1, Json &j2);
	friend Json &operator<=(Json &j1, Json &j2);
	friend Json &operator&&(Json &j1, Json &j2);
	friend Json &operator||(Json &j1, Json &j2);
	friend Json &operator!(Json &j);
};