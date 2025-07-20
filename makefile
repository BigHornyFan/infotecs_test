CC = g++
ExeName = test_program

all: dll main run

dll: 
	$(CC) -fPIC -shared src/writer_class.cpp -Iheaders -o libwriter_lib.so
	

main: 
	$(CC) main.cpp -Iheaders -lwriter_lib -L. -o $(ExeName)

run: 
	./$(ExeName) test_log 1
		
clean: 
	rm -rf $(ExeName) *.so *.o *.txt
