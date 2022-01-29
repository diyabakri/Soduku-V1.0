CC = gcc
EXE = Soduku
defult:
	$(CC) Main.c ./source/sodukuBoard.c ./source/unixinput.c -o  $(EXE)
run:
	sudo ./$(EXE)	
val:
	valgrind --leak-check=full ./$(EXE)