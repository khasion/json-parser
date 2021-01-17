#include "json.h"

#define JSON(name) ;Json name; name

#define NUMBER(n) *new Value((double)n)
#define STRING(str) *new Value(std::string(str))
#define KEY(str) *new Value(std::string(#str)) >>= (false) ? *new Value()
#define TRUE *new Value(true)
#define FALSE *new Value(false)
#define ARRAY (*new Value())
#define OBJECT *new Value
#define SET ;
#define ASSIGN <<=
#define APPEND +=
#define ERASE ; delete& 

#define PRINT ;std::cout <<

#define PROGRAM_BEGIN int main() {
#define PROGRAM_END ;return 0;}