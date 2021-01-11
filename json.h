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
	t_object,
	t_pair
};

class Value
{
public:
	Value ();
	Value (int n);
	Value (std::string str);
	Value (bool b);
	Value (std::initializer_list<Value> v);
	/*Getters */
	vType 							getType(void) 	{ return type;}
	int 								getNum(void) 	{ return n;}
	std::string 					getString(void){ return str;}
	bool 								getBool(void) 	{ return b;}
	Value* 							getNext(int i) { return (i < edges.size()) ? edges[i] : NULL;}
	std::vector<Value*> 			getEdges(void)	{ return edges;}
	std::pair<Value*,Value*>	getPair(void)	{ return pair;}
	/*Setters */
	void setType (vType _t) 							{ type = _t;}
	void setNum(int _n) 									{ n = _n;}
	void setString (std::string _str) 				{ str = _str;}
	void setBool(bool _b) 								{ b = _b;}
	void setNext(Value& _v) 							{ edges.push_back(&_v);}
	void setPair(std::pair<Value*,Value*> _pair) { pair = std::make_pair(_pair.first, _pair.second);}

	std::string toString(void);
	/*<-------- Comparisson Operator Overloading------>*/
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
	std::pair<Value*, Value*> pair;
private:
	vType type;
	int n;
	std::string str;
	bool b;
	std::vector<Value*> edges;
};

void DFS (std::ostream &os, Value* v);

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
		int i = 0;
		Value* v = &j.getVal();
		os << "{";
		DFS(os, v);
		os << "}";
		os << std::endl;
		return os;
	}
};