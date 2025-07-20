# infotecs_test

add can be opened with parameters:
1. log file name
2. default importane
if paramere is absent -> add take them by default

add gets form console input:
1. message text       (enter means end of message input)
2. message importance (enter means end of importance input,
                      app tries to read first word of input as importance integer value,
                      0 is reserved by default importance level,
                      empty input also means default importance) 

Make commands:
dll: compiles dll 
main: compiles an app
run: launches an app
all: 3 top commands
clean: deletes all compiled files with log txt file 

P.S. in my linux add cant find dll without terminal command:
export LD_LIBRARY_PATH=./
