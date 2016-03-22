INC=./includes
SRC=./src
OUT=./bin

$(OUT)/lab: $(OUT)/main.o $(OUT)/std.o $(OUT)/child.o
	gcc -o $(OUT)/lab $(OUT)/main.o $(OUT)/std.o $(OUT)/child.o

$(OUT)/main.o: $(SRC)/main.c $(INC)/general.h
	gcc -I$(INC) -o $(OUT)/main.o -c $(SRC)/main.c
$(OUT)/std.o: $(SRC)/std.c $(INC)/general.h
	gcc -I$(INC) -o $(OUT)/std.o -c $(SRC)/std.c
$(OUT)/child.o: $(SRC)/child.c $(INC)/general.h
	gcc -I$(INC) -o $(OUT)/child.o -c $(SRC)/child.c

clean:
	rm $(OUT)/*.o $(OUT)/lab
