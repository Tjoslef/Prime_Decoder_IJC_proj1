# makefile
   # Řešení IJC-DU1, příklad a)/b), 19.3.2025
   # Autor: Josef Pasek, FIT
   # Přeloženo: gcc 14.2.1
# makefile
CFLAGS = -std=c11 -O2 -pedantic -Wall -Wextra -Werror -g
INLINE = -DUSE_INLINE
32BIT =
eratosthenes_SOURCES = prime.c eratosthenes.c error.c
steg-decode_SOURCES = ppm.c steg-decode.c error.c eratosthenes.c utf8_check.c
OBJ_DIR = obj
eratosthenes_OBJECTS = $(addprefix $(OBJ_DIR)/, $(eratosthenes_SOURCES:.c=.o))
steg_decode_OBJECTS = $(addprefix $(OBJ_DIR)/, $(steg-decode_SOURCES:.c=.o))

all: prime-i prime steg-decode

run: prime-i prime
	ulimit -s  50000
	./prime-i && ./prime

prime-i: $(addprefix $(OBJ_DIR)/, $(eratosthenes_SOURCES:.c=-i.o))
	$(CC) $(CFLAGS) $(INLINE) $(32BIT) $(TIME) -o $@ $^

prime: $(eratosthenes_OBJECTS)
	$(CC) $(CFLAGS)  $(32BIT) $(TIME) -o $@ $^

steg-decode: $(steg_decode_OBJECTS)
	$(CC) $(CFLAGS) $(32BIT) -o $@ $^

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(32BIT) -c $< -o $@

$(OBJ_DIR)/%-i.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(32BIT) $(INLINE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


32bit: 32BIT = -m32
32bit: all
time : TIME= -DTIME
#for test
test : prime
	ulimit -s 5000000
	./prime | factor > eratosthenes_factors.txt
	@echo "Eratosthenes test completed. Output in eratosthenes_factors.txt"

clean:
	rm -f prime-i prime steg-decode
	rm -rf $(OBJ_DIR)
