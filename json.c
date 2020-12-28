#include "json.h"

Value::Value()
{
   next = NULL;
   type = t_null;
}

Value::Value(int n)
{
   next = NULL;
   type = t_num;
   this->n = n;
}
Value::Value(std::string str)
{
   next = NULL;
   type = t_string;
   this->str = str;
}
Value::Value(bool b)
{
   next = NULL;
   type = t_bool;
   this->b = b;
}

vType Value::getType()
{
   return type;
}

int Value::getNum()
{
   return n;
}
std::string Value::getString()
{
   return str;
}
std::string Value::getBool()
{
   return (b ? "true" : "false");
}

Value &Value::operator[](Value &v)
{
   this->v.push_back(v);
   return this->v[0];
}

Value &Value::operator,(Value &v)
{
   next = &v;
   return *this;
}

Value Value::getNext()
{
   return next;
}

Json::Json() {}

Value Json::getVal()
{
   return val;
}

Json &Json::operator=(Value &v)
{
   val = v;
   return *this;
}

Json &Json::operator+(Json &j1, Json &j2)
{
   switch (j1.getVal().getType())
   {
   case t_num:
      switch (j2.getVal().getType())
      {
      case t_num:
         Json jnew = Value::Value(j1.getVal() + j2.getVal());
         return jnew;

         break;
      default:
         cout << "JSON values are not compatible" << endl;
         break;
      }
      break;
   case t_string:
      switch (j2.getVal().getType())
      {
      case t_string:
         std::string str;
         Json jnew = Value::Value(str.append(j1.getVal(), j2.getVal()));
         return jnew;

         break;
      default:
         cout << "JSON values are not compatible" << endl;
         break;
      }
      break;
      /*<---- Need to add + overload for OBJECT and ARRAY types later---->*/
   default:
      break;
   }
}

Json &Json::operator-(Json &j1, Json &j2)
{
   switch (j1.getVal().getType())
   {
   case t_num:
      switch (j2.getVal().getType())
      {
      case t_num:
         Json jnew = Value::Value(j1.getVal() - j2.getVal());
         return jnew;

         break;

      default:
         cout << "JSON values are not both numeric" << endl;
         break;
      }
      break;

   default:
      cout << "Error: Attempted subtraction with non-numeric value" << endl;
      break;
   }
}

Json &Json::operator*(Json &j1, Json &j2)
{
   switch (j1.getVal().getType())
   {
   case t_num:
      switch (j2.getVal().getType())
      {
      case t_num:
         Json jnew = Value::Value(j1.getVal() * j2.getVal());
         return jnew;

         break;

      default:
         cout << "JSON values are not both numeric" << endl;
         break;
      }
      break;

   default:
      cout << "Error: Attempted multiplication with non-numeric value" << endl;
      break;
   }
}

Json &Json::operator/(Json &j1, Json &j2)
{
   switch (j1.getVal().getType())
   {
   case t_num:
      switch (j2.getVal().getType())
      {
      case t_num:
         Json jnew = Value::Value(j1.getVal() - j2.getVal());
         return jnew;

         break;

      default:
         cout << "JSON values are not both numeric" << endl;
         break;
      }
      break;

   default:
      cout << "Error: Attempted division with non-numeric value" << endl;
      break;
   }
}

Json &Json::operator%(Json &j1, Json &j2)
{
   switch (j1.getVal().getType())
   {
   case t_num:
      switch (j2.getVal().getType())
      {
      case t_num:
         Json jnew = Value::Value(j1.getVal() - j2.getVal());
         return jnew;

         break;

      default:
         cout << "JSON values are not both numeric" << endl;
         break;
      }
      break;

   default:
      cout << "Error: Attempted division with non-numeric value (modulo)" << endl;
      break;
   }
}

Json &Json::operator<(Json &j1, Json &j2)
{
   switch (j1.getVal().getType())
   {
   case t_num:
      switch (j2.getVal().getType())
      {
      case t_num:
         Json jnew = Value::Value(j1.getVal() < j2.getVal());
         return jnew;

         break;

      default:
         cout << "JSON values are not both numeric" << endl;
         break;
      }
      break;

   default:
      cout << "Error: Attempted comparisson with non-numeric value" << endl;
      break;
   }
}

Json &Json::operator<=(Json &j1, Json &j2)
{
   switch (j1.getVal().getType())
   {
   case t_num:
      switch (j2.getVal().getType())
      {
      case t_num:
         Json jnew = Value::Value(j1.getVal() <= j2.getVal());
         return jnew;
         break;

      default:
         cout << "JSON values are not both numeric" << endl;
         break;
      }
      break;

   default:
      cout << "Error: Attempted comparisson with non-numeric value" << endl;
      break;
   }
}

Json &Json::operator>(Json &j1, Json &j2)
{
   switch (j1.getVal().getType())
   {
   case t_num:
      switch (j2.getVal().getType())
      {
      case t_num:
         Json jnew = Value::Value(j1.getVal() > j2.getVal());
         return jnew;
         break;

      default:
         cout << "JSON values are not both numeric" << endl;
         break;
      }
      break;

   default:
      cout << "Error: Attempted comparisson with non-numeric value" << endl;
      break;
   }
}

Json &Json::operator>=(Json &j1, Json &j2)
{
   switch (j1.getVal().getType())
   {
   case t_num:
      switch (j2.getVal().getType())
      {
      case t_num:
         Json jnew = Value::Value(j1.getVal() >= j2.getVal());
         return jnew;
         break;

      default:
         cout << "JSON values are not both numeric" << endl;
         break;
      }
      break;

   default:
      cout << "Error: Attempted comparisson with non-numeric value" << endl;
      break;
   }
}

Json &Json::operator&&(Json &j1, Json &j2)
{
   switch (j1.getVal().getType())
   {
   case t_bool:
      switch (j2.getVal().getType())
      {
      case t_bool:
         Json jnew = Value::Value(j1.getVal() && j2.getVal());
         return jnew;
         break;

      default:
         cout << "JSON values are not both boolean" << endl;
         break;
      }
      break;

   default:
      cout << "Error: Attempted logical comparisson with non-boolean values" << endl;
      break;
   }
}

Json &Json::operator||(Json &j1, Json &j2)
{
   switch (j1.getVal().getType())
   {
   case t_bool:
      switch (j2.getVal().getType())
      {
      case t_bool:
         Json jnew = Value::Value(j1.getVal() || j2.getVal());
         return jnew;
         break;

      default:
         cout << "JSON values are not both boolean" << endl;
         break;
      }
      break;

   default:
      cout << "Error: Attempted logical comparisson with non-boolean values" << endl;
      break;
   }
}

Json &Json::operator!(Json &j)
{
   switch (j.getVal().getType())
   {
   case t_bool:
      bool val = j.getVal();
      Json jnew = Value::Value(!val);
      return jnew;
   default:
      cout << "Error: Attempted logical comparisson with non-boolean values" << endl;
      break;
   }
}