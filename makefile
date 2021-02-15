SRC=listing30.c
OUTPUT=test.ppm

all:
	$(CC) $(SRC)
	./a.out > $(OUTPUT)
	open $(OUTPUT)

clean:
	rm a.out $(OUTPUT)

.PHONY: all clean
