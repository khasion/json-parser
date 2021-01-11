#include "json.h"

void DFS (std::ostream &os, Value* v) {
	std::vector<Value*> e = v->getEdges();
	if (v->getType() != t_array) {
		os << v->toString();
	}

	if (v->getType() == t_array) {os << "[";}
	if (v->getType() == t_object) {os << "{";}
	for (auto it = e.cbegin(); it != e.cend(); ++it) {
		if ( (v->getType() != t_array && v->getType() != t_object)
				|| it != e.cbegin()) {
				os << ", ";
		}
		DFS(os, *it);
	}
	if (v->getType() == t_array) {os << "]";}
	if (v->getType() == t_object) {os << "}";}
}

Value::Value()
{
	//next = NULL;
	type = t_null;
}

Value::Value(int n)
{
	//next = NULL;
	type = t_num;
	this->n = n;
}
Value::Value(std::string str)
{
	//next = NULL;
	type = t_string;
	this->str = str;
}
Value::Value(bool b)
{
	//next = NULL;
	type = t_bool;
	this->b = b;
}

Value::Value (std::initializer_list<Value> v) {
	type = t_object;
	for (auto it = v.begin(); it != v.end(); ++it) {
		Value* temp = new Value();
		temp->setType(t_pair);
		temp->setPair((*it).pair);
		edges.push_back(temp);
	}
}

std::string Value::toString (void) {
	std::string tmp;
	switch (this->getType()) {
		case t_null:
			tmp = "NULL";
			break;
		case t_num:
			tmp = std::to_string(this->n);
			break;
		case t_string:
			tmp = this->str;
			break;
		case t_bool:
			tmp = (b ? "TRUE" : "FALSE");
			break;
		case t_pair:
			tmp = this->pair.first->toString() + " : " + this->pair.second->toString();
			break;
		default:
			tmp = "";
			break;
	}
	return tmp;
}

Value &Value::operator[](Value &v)
{
	this->edges.push_back(&v);
	this->type = t_array;
	return *this;
}

Value &Value::operator>>=(Value& v) {
	this->type = t_pair;
	this->pair = std::make_pair(new Value(this->str), &v);
	this->edges.push_back(&v);
	return *this;
}

Value &Value::operator,(Value &v)
{
	edges.push_back(&v);
	return *this;
}

Value &Value::operator+(Value& v)
{
	Value* tmp 	= NULL;
	Value* tmp2 = NULL;
	try
	{
		if (this->getType() != v.getType()) throw 1;
		switch (this->getType())
		{
		case t_num:
			tmp = new Value(this->getNum() + v.getNum());
			break;
		case t_string:
			tmp = new Value(this->getString().append(v.getString()));
			break;
		case t_array:
			this->edges.push_back(&v);
			tmp = this;
			break;
		case t_object:
			break;
		default:
			throw 1;
			break;
		}
		/*<---- Need to add + overload for OBJECT and ARRAY types later---->*/
	}
	catch (int e)
	{
		std::cout << "JSON values are not compatible" << std::endl;
	}
	return *tmp;	
}

Value &Value::operator-(Value &v)
{
	Value *tmp = NULL;
	try
	{
		if (this->getType() != v.getType()) throw 1;
		if (this->getType() != t_num) throw 2;
		tmp = new Value(this->getNum() - v.getNum());
	}
	catch (int e)
	{
		std::cout << "JSON values are not both numeric" << std::endl;
	}
	return *tmp;
}

Value &Value::operator*(Value &v)
{
	Value *tmp = NULL;
	try
	{
		if (this->getType() != v.getType()) throw 1;
		if (this->getType() != t_num) throw 2;
		tmp = new Value(this->getNum() * v.getNum());
	}
	catch (int e)
	{
		std::cout << "JSON values are not both numeric" << std::endl;
	}
	return *tmp;
}

Value &Value::operator/(Value &v)
{
	Value *tmp = NULL;
	try
	{
		if (this->getType() != v.getType()) throw 1;
		if (this->getType() != t_num) throw 2;
		tmp = new Value(this->getNum() / v.getNum());
	}
	catch (int e)
	{
		std::cout << "Error: Attempted division with non-numeric value" << std::endl;
	}
	return *tmp;
}

Value &Value::operator%(Value &v)
{
	Value *tmp = NULL;
	try
	{
		if (this->getType()!= v.getType()) throw 1;
		if (this->getType() != t_num) throw 2;
		tmp = new Value(this->getNum() % v.getNum());
	}
	catch (int e)
	{
		std::cout << "Error: Attempted division with non-numeric value (modulo)" << std::endl;
	}
	return *tmp;
}

Value &Value::operator<(Value &v)
{
	Value *tmp = NULL;
	try
	{
		if (this->getType() != v.getType()) throw 1;
		if (this->getType() != t_num) throw 2;
		tmp = new Value(this->getNum() < v.getNum());
	}
	catch (int e)
	{
		std::cout << "Error: Attempted comparisson with non-numeric value" << std::endl;
	}
	return *tmp;
}

Value &Value::operator<=(Value &v)
{
	Value *tmp = NULL;
	try
	{
		if (this->getType() != v.getType()) throw 1;
		if (this->getType() != t_num) throw 2;
		tmp = new Value(this->getNum() <= v.getNum());
	}
	catch (int e)
	{
		std::cout << "Error: Attempted comparisson with non-numeric value" << std::endl;
	}
	return *tmp;
}

Value &Value::operator>(Value &v)
{
	Value *tmp = NULL;
	try
	{
		if (this->getType() != v.getType()) throw 1;
		if (this->getType() != t_num) throw 2;
		tmp = new Value(this->getNum() > v.getNum());
	}
	catch (int e)
	{
		std::cout << "Error: Attempted comparisson with non-numeric value" << std::endl;
	}
	return *tmp;
}

Value &Value::operator>=(Value &v)
{
	Value *tmp = NULL;
	try
	{
		if (this->getType() != v.getType()) throw 1;
		if (this->getType() != t_num) throw 2;
		tmp = new Value(this->getNum() >= v.getNum());
	}
	catch (int e)
	{
		std::cout << "Error: Attempted comparisson with non-numeric value" << std::endl;
	}
	return *tmp;
}

Value &Value::operator&&(Value &v)
{
	Value *tmp = NULL;
	try
	{
		if (this->getType() != v.getType()) throw 1;
		if (this->getType() != t_bool) throw 2;
		tmp = new Value(this->getBool() && v.getBool());
	}
	catch (int e)
	{
		std::cout << "Error: Attempted logical comparisson with non-boolean values" << std::endl;
	}
	return *tmp;
}

Value &Value::operator||(Value &v)
{
	Value *tmp = NULL;
	try
	{
		if (this->getType() != v.getType()) throw 1;
		if (this->getType() != t_bool) throw 2;
		tmp = new Value(this->getBool() || v.getBool());
	}
	catch (int e)
	{
		std::cout << "Error: Attempted logical comparisson with non-boolean values" << std::endl;
	}
	return *tmp;
}

Value &Value::operator!()
{
	Value *tmp = NULL;
	try
	{
		switch (this->getType())
		{
		case t_bool:
			tmp = new Value(!this->getBool());
			break;
		default:
			throw 1;
		}
	}
	catch (int e)
	{
		std::cout << "Error: Attempted logical comparisson with non-boolean values" << std::endl;
	}
	return *tmp;
}