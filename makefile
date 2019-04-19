CC=gcc
CFLAGS=-O3 -W -Wall
TARGET=interpretador
HDR=$(wildcard *.h)
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
HDRC=$(HDR:.h=.h.gch)

all: $(TARGET) clean
# regras para gerar o executavel
$(TARGET) : .h .c
	$(CC) -o $@ $(OBJ) $(CFLAGS)

# regras de compilação
.c:
	$(CC) -c $(SRC) $(CFLAGS)

.h:
	$(CC) -c $(HDR) $(CFLAGS)

clean:
	rm -rf $(OBJ) $(HDRC)

clear:
	rm -rf $(TARGET)
