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
#define ERASE(x) ;erase(&x)
//#define ERASE ;delete &

#define SIZE_OF(x)		sizeOf(x)
#define IS_EMPTY(x)		isEmpty(x)
#define HAS_KEY(x,str)	hasKey(x, str)
#define TYPE_OF(x)		getType(x)

#define PRINT ;std::cout << std::endl <<

#define PROGRAM_BEGIN int main() {
#define PROGRAM_END ;std::cout<<std::endl;return 0;}