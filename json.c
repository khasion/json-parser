#include "json.h"

Value::Value () {
   next = NULL;
   type = t_null;
}

Value::Value(int n) {
   next = NULL;
   type = t_num;
   this->n = n;
}
Value::Value(std::string str) {
   next = NULL;
   type = t_string;
   this->str = str;
}
Value::Value(bool b) {
   next = NULL;
   type = t_bool;
   this->b = b;
}

vType Value::getType() {
   return type;
}

int Value::getNum() {
   return n;
}
std::string Value::getString() {
   return str;
}
std::string Value::getBool() {
   return (b ? "true" : "false");
}

Value &Value::operator[](Value &v) {
   this->v.push_back(v);
   return this->v[0];
}

Value &Value::operator,(Value &v) {
   next = &v;
   return *this;
}

Value Value::getNext() {
   return next;
}

Json::Json() {}

Value Json::getVal() {
   return val;
}
Json &Json::operator=(Value &v) {
   val = v;
   return *this;
}