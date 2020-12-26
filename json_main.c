#include "JSONlang.h"

PROGRAM_BEGIN
   JSON(num) = NUMBER(15)
   JSON(str) = STRING("striing")
   JSON(emptyArray) = ARRAY
   JSON(boolt) = TRUE
   JSON(boolf) = FALSE
   JSON(array) = ARRAY [NUMBER(20)]
   PRINT num
   PRINT str
   PRINT emptyArray
   PRINT boolt
   PRINT boolf
PROGRAM_END