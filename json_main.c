#include "JSONlang.h"

PROGRAM_BEGIN
   JSON(num) = NUMBER(15) + NUMBER(5) + NUMBER(60)
   JSON(str) = STRING("string1") + STRING("string2") + STRING("string3")
   JSON(emptyArray) = ARRAY
   JSON(boolt) = ARRAY [FALSE || TRUE, TRUE && TRUE, !FALSE]
   JSON(boolf) = ARRAY [FALSE || FALSE, FALSE && TRUE, !TRUE]
   JSON(array) = ARRAY [STRING("this is") + STRING(" an array"), NUMBER(20) + NUMBER(5)]
   PRINT num
   PRINT str
   PRINT emptyArray
   PRINT boolt
   PRINT boolf
   PRINT array
PROGRAM_END