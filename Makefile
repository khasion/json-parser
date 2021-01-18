CC=g++

make:	
	$(CC) json.cpp json_main.cpp -std=c++11 -o parser 
clean:
	rm parser
