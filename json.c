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

Value &Value::operator+(Value &v1, Value &v2)
{
   try
   {
      switch (v1.getType())
      {
      case t_num:
         switch (v2.getType())
         {
         case t_num:
            Value newval = Value::Value(v1 + v2);
            return newval;

            break;
         default:
            throw 1;
            break;
         }
         break;
      case t_string:
         switch (v2.getType())
         {
         case t_string:
            std::string str;
            Value newval = Value::Value(str.append(v1, v2));
            return newval;
            break;
         default:
            throw 2;
         }
      }
      break;
      /*<---- Need to add + overload for OBJECT and ARRAY types later---->*/
   default:
      break;
   }
   catch (int e)
   {
      cout << "JSON values are not compatible" << endl;
   }
}

Value &Value::operator-(Value &v1, Value &v2)
{
   try
   {
      switch (v1.getType())
      {
      case t_num:
         switch (v2.getType())
         {
         case t_num:
            Value newval = Value::Value(v1 - v2);
            return newval;

            break;

         default:
            throw 1;
         }
         break;

      default:
         throw 2;
      }
   }
   catch (int e)
   {
      cout << "JSON values are not both numeric" << endl;
   }
}

Value &Value::operator*(Value &v1, Value &v2)
{
   try
   {
      switch (v1.getType())
      {
      case t_num:
         switch (v2.getType())
         {
         case t_num:
            Value newval = Value::Value(v1 * v2);
            return newval;
            break;

         default:
            throw 1;
         }
         break;

      default:
         throw 2;
      }
   }
   catch (int e)
   {
      cout << "JSON values are not both numeric" << endl;
   }
}

Value &Value::operator/(Value &v1, Value &v2)
{
   try
   {
      switch (v1.getType())
      {
      case t_num:
         switch (v2.getType())
         {
         case t_num:
            Value newval = Value::Value(v1 - v2);
            return newval;
            break;

         default:
            throw 2;
         }
         break;

      default:
         throw 1;
      }
   }
   catch (int e)
   {
      cout << "Error: Attempted division with non-numeric value" << endl;
   }
}

Value &Value::operator%(Value &v1, Value &v2)
{
   try
   {
      switch (v1.getType())
      {
      case t_num:
         switch (v2.getType())
         {
         case t_num:
            Value newval = Value::Value(v1 - v2);
            return newval;
            break;

         default:
            throw 2;
         }
         break;

      default:
         throw 1;
      }
   }
   catch (int e)
   {
      cout << "Error: Attempted division with non-numeric value (modulo)" << endl;
   }
}

Value &Value::operator<(Value &v1, Value &v2)
{
   try
   {
      switch (v1.getType())
      {
      case t_num:
         switch (v2.getType())
         {
         case t_num:
            Value newval = Value::Value(v1 < v2);
            return newval;

            break;

         default:
            throw 2;
         }
         break;

      default:
         throw 1;
      }
   }
   catch (int e)
   {
      cout << "Error: Attempted comparisson with non-numeric value" << endl;
   }
}

Value &Value::operator<=(Value &v1, Value &v2)
{
   try
   {
      switch (v1.getType())
      {
      case t_num:
         switch (v2.getType())
         {
         case t_num:
            Value newval = Value::Value(v1 <= v2);
            return newval;
            break;

         default:
            throw 2;
         }
         break;

      default:
         throw 1;
      }
   }
   catch (int e)
   {
      cout << "Error: Attempted comparisson with non-numeric value" << endl;
   }
}

Value &Value::operator>(Value &v1, Value &v2)
{
   try
   {
      switch (v1.getType())
      {
      case t_num:
         switch (v2.getType())
         {
         case t_num:
            Value newval = Value::Value(v1 > v2);
            return newval;
            break;

         default:
            throw 2;
         }
         break;

      default:
         throw 1;
      }
   }
   catch (int e)
   {
      cout << "Error: Attempted comparisson with non-numeric value" << endl;
   }
}

Value &Value::operator>=(Value &v1, Value &v2)
{
   try
   {
      switch (v1.getType())
      {
      case t_num:
         switch (v2.getType())
         {
         case t_num:
            Value newval = Value::Value(v1 >= v2);
            return newval;
            break;

         default:
            throw 2;
         }
         break;

      default:
         throw 1;
      }
   }
   catch (int e)
   {
      cout << "Error: Attempted comparisson with non-numeric value" << endl;
   }
}

Value &Value::operator&&(Value &v1, Value &v2)
{
   try
   {
      switch (v1.getType())
      {
      case t_bool:
         switch (v2.getType())
         {
         case t_bool:
            Value newval = Value::Value(v1 && v2);
            return newval;
            break;

         default:
            throw 2;
         }
         break;

      default:
         throw 1;
      }
   }
   catch (int e)
   {
      cout << "Error: Attempted logical comparisson with non-boolean values" << endl;
   }
}

Value &Value::operator||(Value &v1, Value &v2)
{
   try
   {
      switch (v1.getType())
      {
      case t_bool:
         switch (v2.getType())
         {
         case t_bool:
            Value newval = Value::Value(v1 || v2);
            return newval;
            break;

         default:
            throw 2;
         }
         break;

      default:
         throw 1;
      }
   }
   catch (int e)
   {
      cout << "Error: Attempted logical comparisson with non-boolean values" << endl;
   }
}

Value &Value::operator!(Json &j)
{
   try
   {
      switch (j.getVal().getType())
      {
      case t_bool:
         bool val = j.getVal();
         Value newval = Value::Value(!val);
         return newval;
      default:
         throw 1;
      }
   }
   catch (int e)
   {
      cout << "Error: Attempted logical comparisson with non-boolean values" << endl;
   }
}
