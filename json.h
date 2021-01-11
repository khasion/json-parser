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
	vType 						getType() 		{ return type;}
	int 							getNum() 		{ return n;}
	std::string 				getString()		{ return str;}
	bool 							getBool() 		{ return b;}
	Value* 						getNext(int i) { return (i < edges.size()) ? edges[i] : NULL;}
	std::vector<Value*> 		getEdges(void)	{ return edges;}
	/*Setters */
	void setType (vType t) 				{ this->type = t;}
	void setNum(int n) 					{ this->n = n;}
	void setString (std::string str) { this->str = str;}
	void setBool(bool b) 				{ this->b = b;}
	void setNext(Value& v) 				{ edges.push_back(&v);}

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