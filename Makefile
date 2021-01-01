CC=g++

make:	
	$(CC) json.c json_main.c -o parser
clean:
	rm parser
