#include "JSONlang.h"

PROGRAM_BEGIN
	/*JSON(num) = NUMBER(15) + NUMBER(5) + NUMBER(60)
	JSON(str) = STRING("string1") + STRING("string2") + STRING("string3")
	JSON(emptyArray) = ARRAY
	JSON(boolt) = ARRAY [FALSE || TRUE, TRUE && TRUE, !FALSE]
	JSON(boolf) = ARRAY [FALSE || FALSE, FALSE && TRUE, !TRUE]
	JSON(array) = ARRAY [STRING("this is") + STRING(" an array"), NUMBER(20) + NUMBER(5)]
	JSON(array_plus) = ARRAY [STRING("hello")] +
		ARRAY [STRING("World"), STRING("I'm")] +
		ARRAY [STRING("CSD") + STRING("3521")]
	JSON(obj) = OBJECT {
		KEY(first)	: STRING("GIANNIS"),
		KEY(last)	: STRING("KASIONIS"),
		KEY(AM)		: NUMBER(3521),
		KEY(grades)	: ARRAY[NUMBER(10), NUMBER(9), NUMBER(8), NUMBER(7)],
		KEY(array)	: ARRAY[
			OBJECT {
				KEY(kati) 	: NUMBER(8),
				KEY(allo)	: ARRAY[STRING("KATI"), STRING("ALLO")]
			}
		]
	}*/
	JSON(book) = OBJECT {
		KEY(title) : STRING("Gone Girl"),
		KEY(published) : NUMBER(2012),
		KEY(type) : STRING("Thriller"),
		KEY(author) : OBJECT{
			KEY(firstname) : STRING("GILLIAN"),
			KEY(surname) : STRING("FLYNN"),
			KEY(age) : NUMBER(45)
			}
		}
	JSON(week_temp) = ARRAY [NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
										NUMBER(19), NUMBER(18.5), NUMBER(18)]
	JSON(std) = ARRAY [
		OBJECT {
			KEY(first)	: STRING("Giannis"),
			KEY(last)	: STRING("Kasionis")
		},
		OBJECT {
			KEY(first)	: STRING("Konstantinos"),
			KEY(last)	: STRING("Papadakis")
		}
	]
	JSON(empty_obj) = OBJECT {}

	PRINT(week_temp)
	SET week_temp[2] ASSIGN NUMBER(22)
	SET week_temp APPEND NUMBER(23), NUMBER(22), NUMBER(20)
	PRINT(week_temp)

	PRINT std
	SET std[0]["last"] ASSIGN STRING("edited") 
	SET std[1]	APPEND OBJECT {KEY(AM) : NUMBER(1111)}
	PRINT std

	PRINT empty_obj
	SET empty_obj ASSIGN OBJECT{KEY(a) : STRING("alpha")}
	SET empty_obj["new"] ASSIGN STRING("not found")
	PRINT empty_obj

	/*SET obj["lesson"] ASSIGN NUMBER(3529)

	SET array APPEND STRING("FOO")

	PRINT num
	PRINT str
	PRINT emptyArray
	PRINT boolt
	PRINT boolf
	PRINT array
	PRINT array_plus
	PRINT obj*/
PROGRAM_END