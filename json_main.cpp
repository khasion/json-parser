#include "JSONlang.h"


PROGRAM_BEGIN
//define emptyObj json with empty object
JSON(emptyObj)  = OBJECT {}
//define emptyArray json with empty array
JSON(emptyArray) = ARRAY
//define book json with an object containing data for a book
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

//define week_temperatures json with an array of numbers
JSON(week_temperatures) = ARRAY [
	NUMBER(20),
	NUMBER(19.5),
	NUMBER(19),
	NUMBER(20),
	NUMBER(19),
	NUMBER(18.5),
	NUMBER(19)
	]

	//define students json with an array of objects representing students
JSON(students) = ARRAY [
	OBJECT {
		KEY(name)  : STRING("Kevin Malone"),
		KEY(id) : NUMBER(4444),
		KEY(grades) : ARRAY[
			OBJECT { 
				KEY(hy100) : NUMBER(9.5) 
			},
			OBJECT { KEY(hy150) : NUMBER(9) }
			]
	}
]




//change 3rd day temperature from 19 to 22
SET week_temperatures[2] ASSIGN NUMBER(22)
//add email address for 1st student
SET students[0]["email"]ASSIGN STRING("csd404@csd.uoc.gr")
//assign new object in emptyObj json
SET emptyObj ASSIGN OBJECT{ KEY(a) : STRING("alpha")}

//appends values 23, 22, 20 to the end of the temperature array
SET week_temperatures APPEND (NUMBER(23), NUMBER(22), NUMBER(20))
//appends a grade for course hy255
SET students[0]["grades"]APPEND OBJECT { KEY(hy255) : NUMBER(9) }

ERASE (book["author"]["age"])

PRINT book["title"]
//prints:Gone Girl
PRINT book["author"]
 //prints:{firstname:”Gillian”,surname:“Flynn”,age:45}
 PRINT book
 //prints: the whole json for book
 PRINT HAS_KEY(book, "author")
 //prints: true
 // prints: Book has key author? True
 PRINT STRING("Book has key author? "), HAS_KEY(book, "author")


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
	/*JSON(week_temp) = ARRAY [NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
										NUMBER(19), NUMBER(18.5), NUMBER(19)]
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
	SET week_temp APPEND (NUMBER(23), NUMBER(22), NUMBER(20))
	PRINT(week_temp)

	PRINT std
	SET std[0]["last"] ASSIGN KEY(last) : STRING("edited")
	SET std[1]	APPEND OBJECT {KEY(AM) : NUMBER(1111)}
	ERASE(std)
	PRINT std

	PRINT empty_obj
	SET empty_obj ASSIGN OBJECT{KEY(a) : STRING("alpha")}
	SET empty_obj["new"] ASSIGN STRING("not found")
	PRINT empty_obj
	ERASE(empty_obj)

	PRINT SIZE_OF(week_temp)
	PRINT IS_EMPTY(empty_obj)
	PRINT HAS_KEY(empty_obj, "a")
	PRINT TYPE_OF(empty_obj)
	PRINT (STRING("HAS KEY? "), HAS_KEY(empty_obj, "a"))

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