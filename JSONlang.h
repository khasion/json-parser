#include "json.h"

#define JSON(name) ;Json name; name

#define NUMBER(n) *(new Value(n))
#define STRING(str) *(new Value(std::string(str)))
#define TRUE *(new Value(true))
#define FALSE *(new Value(false))
#define ARRAY (*(new Value()))
#define OBJECT *(new Value())

#define PRINT ;std::cout <<

#define PROGRAM_BEGIN int main() {
#define PROGRAM_END ;return 0;}