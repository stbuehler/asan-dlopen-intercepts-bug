# Demo code

gcc asan initializes intercepts only once.

When the intercepted function is in a library that isn't available at that time, calling that function results in calling a nullptr (segfault).

Now usually a program should be linked against the libraries it is using, but if a plugin is loaded later, and that plugin also links the original library it needs, asan still fails to find the library (i.e. doesn't retry searching for the intercepted target).

Additionally the crash output is completely useless (missing backtrace and the name of the intercepted function).

```
$ make
gcc -shared -o plugin.so -lcrypt -Wall -Wextra -O2 -ggdb -fsanitize=address -fno-omit-frame-pointer plugin.c
gcc -o main -ldl  -Wall -Wextra -O2 -ggdb -fsanitize=address -fno-omit-frame-pointer main.c
$ ./main
Found plugin run function: 0x7fa33ea3b1a0
AddressSanitizer:DEADLYSIGNAL
=================================================================
==208926==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x000000000000 bp 0x7ffed844e1b0 sp 0x7ffed844e1a8 T0)
==208926==Hint: pc points to the zero page.
==208926==The signal is caused by a READ memory access.
==208926==Hint: address points to the zero page.
    #0 0x0  (<unknown module>)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (<unknown module>) 
==208926==ABORTING
```
