CC=g++

make:	
	$(CC) json.cpp json_main.cpp -o parser
clean:
	rm parser
