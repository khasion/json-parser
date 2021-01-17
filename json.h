#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

enum vType
{
	t_null,
	t_num,
	t_float,
	t_string,
	t_bool,
	t_array,
	t_object,
	t_pair
};

class Value
{
public:
	Value ();
	Value (double n);
	Value (std::string str);
	Value (bool b);
	Value (std::initializer_list<Value> v);
	/*Getters */
	vType 					getType(void) 	{ return type;}
	double 					getNum(void) 	{ return n;}
	std::string 			getString(void) {return str;}
	bool 						getBool(void) 	{ return b;}
	Value* 					getIndex(int i) {return (i < edges.size()) ? edges[i] : NULL;}
	std::vector<Value*>& getEdges(void)	{ return edges;}
	Value*					getNext(void)	{ return next;}
	std::string				getKey(void)	{ return key;}
	/*Setters */
	void setVal (vType _t) 				{ type = _t;}
	void setVal(double _n) 				{ n = _n;}
	void setVal (std::string _str)	{ str = _str;}
	void setVal(bool _b) 				{ b = _b;}
	void setVal(Value& _v) 				{ edges.push_back(&_v);}
	void setKey(std::string _key) 	{ key = _key;}

	std::string toString(void);
	void Clone (Value v) {
		key 	= v.getKey();
		type 	= v.getType();
		n		= v.getNum();
		str	= v.getString();
		b		= v.getBool();
		edges	= v.getEdges();
	}
	/*<--------  Operator Overloading------>*/
	Value &operator+=(Value& v);
	Value &operator<<=(Value& v);
	Value &operator[](int);
	Value &operator[](std::string);
	Value &operator[](Value& v);
	Value &operator>>=(Value& v);
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
	std::string key = "";
	vType type;
	double n;
	std::string str;
	bool b;
	std::vector<Value*> edges;
	Value* next = nullptr;
};

void 	dfs_print (std::ostream &os, Value* v);
Value &dfs_find (std::string s, Value* v);

class Json
{
private:
	Value val;
public:
	Json() {}
	Value& getVal() 				{ return val;}
	Json &operator=(Value v) 	{ val = v; return *this;}
	Json &operator+=(Value& v);
	Json &operator<<=(Value& v);
	Value &operator[](int);
	Value &operator[](std::string);

	friend std::ostream &operator<<(std::ostream &os, Json &j)
	{
		int i = 0;
		Value* v = &j.getVal();
		os << "{";
		dfs_print(os, v);
		os << "}";
		os << std::endl;
		return os;
	}
};