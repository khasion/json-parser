#include "json.h"

void dfs_print (std::ostream &os, Value* v) {
	std::vector<Value*> e = v->getEdges();
	os << v->toString();

	if (v->getType() == t_array) {os << "[";}
	if (v->getType() == t_object) {os << "{";}
	Value* tmp = v->getNext();
	for (auto it = e.cbegin(); it != e.cend(); ++it) {
		if ( (v->getType() != t_array && v->getType() != t_object)
				|| it != e.cbegin()) {
				os << ", ";
		}
		dfs_print(os, *it);
	}
	if (v->getType() == t_array) {os << "]";}
	if (v->getType() == t_object) {os << "}";}
}
Value* dfs_find (std::string s, Value* v) {
	if (v->getKey().compare(s) == 0) {
		return v;
	}
	std::vector<Value*> e = v->getEdges();
	for (auto it = e.cbegin(); it != e.cend(); ++it) {
		Value *tmp = dfs_find(s, (*it));
		if (v != nullptr) {
			return v;
		}
	}
	return nullptr;
}
void removeFromParents (Value* v) {
	std::vector<Value*> p = v->getParents();
	for (auto it = p.cbegin(); it != p.cend(); ++it) {
		std::vector<Value*> e = (*it)->getEdges();
		for (auto jt = e.cbegin(); jt != e.cend(); ++jt) {
			if ((*jt) == v) {jt = e.erase(jt);}
			if (jt == e.cend()) { break;}
		}
	}
}
void dfs_erase (Value* v) {
	std::vector<Value*> e = v->getEdges();
	if (!e.empty()) {
		for (auto it = e.cbegin(); it != e.cend(); ++it) {
			dfs_erase(*it);
		}
	}
	removeFromParents(v);
	free(v);
}

Json::Json () {}

Value &Json::operator[](int n) {
	return *(val.getIndex(n));
}

Value &Json::operator[](std::string s) {
	if (val.getKey().compare(s) == 0) { return val;}
	std::vector<Value*> e = val.getEdges();
	Value* v;
	if (!e.empty()) {
		for (auto it = e.cbegin(); it != e.cend(); ++it) {
			if ((*it)->getKey().compare(s) == 0) {
				v = *it;
				return *v;
			}
		}
	}
	v = new Value();
	val.getEdges().push_back(v);
	v->getParents().push_back(&val);
	return *v;
}
Json &Json::operator+=(Value& v) {
	Value* tmp = &v;
	while (tmp) {
		val.getEdges().push_back(tmp);
		tmp->getParents().push_back(&val);
		tmp = tmp->getNext();
	}
	return *this;
}
Json &Json::operator<<=(Value& v) {
	val.Clone(v);
	return *this;
}
void Json::operator delete (void* j) {
	dfs_erase(&(static_cast<Json*>(j))->getVal());
	free(j);
}

Value::Value()
{
	type = t_null;
}

Value::Value(double n)
{
	type = t_num;
	this->n = n;
}
Value::Value(std::string str)
{
	type = t_string;
	this->str = str;
}
Value::Value(bool b)
{
	type = t_bool;
	this->b = b;
}

Value::Value (std::initializer_list<Value> v) {
	type = t_object;
	for (auto it = v.begin(); it != v.end(); ++it) {
		Value* temp = new Value();
		temp->Clone ((*it));
		edges.push_back(temp);
		temp->getParents().push_back(this);
	}
}

std::string Value::toString (void) {
	std::string tmp = "";
	std::ostringstream ss;

	if (this->key.size() > 0) {
		tmp += key + " : ";
	}

	switch (this->getType()) {
		case t_null:
			tmp += "NULL";
			break;
		case t_float:
		case t_num:
			ss << this->n;
			tmp += ss.str();
			break;
		case t_string:
			tmp += this->str;
			break;
		case t_bool:
			tmp += (b ? "TRUE" : "FALSE");
			break;
		default:
			break;
	}
	return tmp;
}

std::ostream &operator<<(std::ostream &os, Value &v) {
	dfs_print(os, &v);
	return os;
}

Value &Value::operator+=(Value &v){
	Value* tmp = &v;
	while (tmp) {
		this->edges.push_back(tmp);
		tmp->getParents().push_back(this);
		tmp = tmp->next;
	}
	return *this;

}

Value &Value::operator<<=(Value &v) {
	this->Clone(v);
	return *this;
}
Value &Value::operator[](Value &v)
{
	Value* tmp;
	tmp = &v;
	while (tmp) {
		this->edges.push_back(tmp);
		tmp->getParents().push_back(this);
		tmp = tmp->next;
	}
	this->type = t_array;
	return *this;
}
Value &Value::operator[](int n) {
	return *(this->getIndex(n));
}
Value &Value::operator[](std::string s) {
	if (getKey().compare(s) == 0) { return *this;}
	std::vector<Value*> e = getEdges();
	Value* v;
	for (auto it = e.cbegin(); it != e.cend(); ++it) {
		if ((*it)->getKey().compare(s) == 0) {
			v = *it;
			return *v;
		}
	}
	v = new Value();
	edges.push_back(v);
	v->getParents().push_back(this);
	return *v;
}

Value &Value::operator>>=(Value& v) {
	key 	= str;
	type 	= v.getType();
	n 		= v.getNum();
	str 	= v.getString();
	b		= v.getBool();
	edges	= v.getEdges();
	return *this;
}

Value &Value::operator,(Value &v)
{
	Value* tmp = this;
	while (tmp->next) {
		tmp = tmp->next;
	}
	tmp->next = &v;
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
			v.getParents().push_back(this);
			tmp = this;
			break;
		case t_object:
			this->edges.push_back(&v);
			v.getParents().push_back(this);
			tmp = this;
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
		int n1 = this->getNum(), n2 = v.getNum();
		tmp = new Value((double)(n1 % n2));
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
void Value::operator delete (void* v) {
	dfs_erase(static_cast<Value*>(v));
}

int sizeOf(Json obj){
	return obj.getVal().getEdges().size();
}

int sizeOf(Value* v){
	return v->getEdges().size();
}

std::string isEmpty(Json obj){
	Value val = obj.getVal();
	return (!val.getEdges().size()) ? "TRUE" : "FALSE";
}

std::string isEmpty(Value *v){
	return (!v->getEdges().size()) ? "TRUE" : "FALSE";
}

std::string hasKey(Json& obj, std::string s) {
	Value* tmp = dfs_find(s, &obj.getVal());
	return (tmp != nullptr) ? "TRUE" : "FALSE";
}

std::string hasKey(Value *v, std::string s){
	Value* tmp = dfs_find(s, v);
	return (tmp != nullptr) ? "TRUE" : "FALSE";
}

std::string getType(Json obj){
	switch (obj.getVal().getType()) {
		case t_null: 		return "null";
		case t_num:			return "number";
		case t_float:		return "float";
		case t_string:		return "string";
		case t_bool:		return "bool";
		case t_array:		return "array";
		default :			return "object";
	}
}

std::string getType(Value *v){
	switch (v->getType()) {
		case t_null: 		return "null";
		case t_num:			return "number";
		case t_float:		return "float";
		case t_string:		return "string";
		case t_bool:		return "bool";
		case t_array:		return "array";
		default :			return "object";
	}
}