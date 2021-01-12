#include "JSONlang.h"

PROGRAM_BEGIN
	JSON(num) = NUMBER(15) + NUMBER(5) + NUMBER(60)
	JSON(str) = STRING("string1") + STRING("string2") + STRING("string3")
	JSON(emptyArray) = ARRAY
	JSON(boolt) = ARRAY [FALSE || TRUE, TRUE && TRUE, !FALSE]
	JSON(boolf) = ARRAY [FALSE || FALSE, FALSE && TRUE, !TRUE]
	JSON(array) = ARRAY [STRING("this is") + STRING(" an array"), NUMBER(20) + NUMBER(5)]
	JSON(array_plus) = ARRAY [STRING("hello")] +
		ARRAY [STRING("World"), STRING("I'm")] +
		ARRAY [STRING("CSD") + STRING("3521")]
	JSON(obj) = OBJECT {
		KEY(first) 	: STRING("GIANNIS"),
		KEY(last)	: STRING("KASIONIS"),
		KEY(AM)		: NUMBER(3521),
		KEY(grades)	: ARRAY[NUMBER(10), NUMBER(9), NUMBER(8), NUMBER(7)],
		KEY(array)	: ARRAY[
			OBJECT {
				KEY(kati) 	: NUMBER(8),
				KEY(allo)	: ARRAY[STRING("KATI"), STRING("ALLO")]
			}
		]
	}
	PRINT num
	PRINT str
	PRINT emptyArray
	PRINT boolt
	PRINT boolf
	PRINT array
	PRINT array_plus
	PRINT obj
PROGRAM_END