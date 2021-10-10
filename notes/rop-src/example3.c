#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bar() {
  system("/bin/sh");
}

void func(char *str,size_t len) {
  char buf[10];
  memcpy(buf,str,len);
}

int main(int argc, char**argv) {
  size_t len = strtol(argv[1], NULL, 10);
  func(argv[2], len);
  return 0;
}

// in gdb (stack dependent):
// set args 100 $(perl rop.pl libc)
// set args 100 $(perl rop.pl rop-1)
// exec bar directly:
// ./example3 100 `perl rop.pl bar`
// rop, stack-independent, system:
// ./example3 100 `perl rop.pl rop-2`
