# Demo code

gcc asan initializes intercepts only once.

When the intercepted function is in a library that isn't available at that time, calling that function results in calling a nullptr (segfault).

Now usually a program should be linked against the libraries it is using, but if a plugin is loaded later, and that plugin also links the original library it needs, asan still fails to find the library (i.e. doesn't retry searching for the intercepted target).

Additionally the crash output is completely useless (missing backtrace and the name of the intercepted function).

```
$ make
gcc -shared -o plugin.so -lcrypt -Wall -O2 -ggdb -fsanitize=address -fno-omit-frame-pointer plugin.c
gcc -o main -ldl  -Wall -O2 -ggdb -fsanitize=address -fno-omit-frame-pointer main.c
$ ./main 
Found plugin run function: 0x7f79959891a0
AddressSanitizer:DEADLYSIGNAL
=================================================================
==207166==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x000000000000 bp 0x7fff4f16c8d0 sp 0x7fff4f16c8c8 T0)
==207166==Hint: pc points to the zero page.
==207166==The signal is caused by a READ memory access.
==207166==Hint: address points to the zero page.
    #0 0x0  (<unknown module>)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (<unknown module>) 
==207166==ABORTING
```
