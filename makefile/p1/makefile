CC = cc
OBJ = main.o sum.o mul.o sub.o divi.o
.PHONY: clean distclean install uninstall

calc:	$(OBJ)
	$(CC) $(OBJ) -o calc
%.o: %.c header.h
	$(CC) -c $< -o $@
clean:
	@echo "cleaning up..."
	@rm -f $(OBJ) 
install: 
	@echo "Installing.."
	cp calc /usr/local/bin/calc
	@echo "done! type calc to run it..."

distclean: clean
	@echo "removing excutable file.."
	@rm -f calc

#clean:
#	@echo "cleaning up..."
#	@rm -f $(OBJ) calc

#	rm -f *.o calc  #-f (force): "Remove files without prompting, and don't complain if they don't exist."

#	rm *.o calc    #f you run make clean twice, the second time it will fail. Why? Because the files are already gone! The rm command will return an error ("No such file or directory"), and Make will yell at you.





#main.o: main.c header.h
#	$(CC) -c main.c -o main.o
#sum.o: sum.c header.h
#	$(CC) -c sum.c -o sum.o
#mul.o: mul.c header.h
#	$(CC) -c mul.c -o mul.o
#sub.o: sub.c header.h
#	$(CC) -c sub.c -o sub.o
#divi.o: divi.c header.h
#	$(CC) -c divi.c -o divi.o
#clean:
#	rm main.o sum.o mul.o sub.o divi.o calc
