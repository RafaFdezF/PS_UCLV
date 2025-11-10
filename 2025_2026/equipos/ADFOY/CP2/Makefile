CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGETS = ejercicio4 ejercicio5 ejercicio5a ejercicio6

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

.PHONY: all clean