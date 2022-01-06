override CFLAGS := -Wall -Wextra -O2 -ggdb -fsanitize=address -fno-omit-frame-pointer
# override WORKAROUND := -lcrypt

all: plugin.so main
clean:
	rm -f plugin.so main
.PHONY: all clean

plugin.so: plugin.c Makefile
	gcc -shared -o $@ -lcrypt $(CFLAGS) $<

main: main.c Makefile
	gcc -o $@ -ldl $(WORKAROUND) $(CFLAGS) $<
