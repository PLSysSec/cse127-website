#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>

struct my_struct {
  uint32_t x;
  void (*f)();
};


struct my_struct* new_struct(uint32_t x, void (*f)()) {
  struct my_struct* p = malloc(sizeof(struct my_struct));
  p->x = x;
  p->f = f;
  return p;
}

void print_struct(struct my_struct* p) {
  printf("p = %p\nx = 0x%x\n", p, p->x);
  p->f();
  printf("\n");
}

void foo() {
  printf("woo! in foo!\n");
}

void bar() {
  printf("woo! in bar!\n");
}


// Alloc-alloc, free-free
void example1() {
  struct my_struct* p = new_struct(0xdeadbeef, foo);
  print_struct(p);

  struct my_struct* q = new_struct(0xdeadbeef, bar);
  print_struct(q);

  free(p);
  free(q);
}

// Alloc-free, alloc-free
void example2() {
  struct my_struct* p = new_struct(0xdeadbeef, foo);
  print_struct(p);
  free(p);

  struct my_struct* q = new_struct(0xdeadbeef, bar);
  print_struct(q);
  free(q);
}

// User after free
void example3() {
  struct my_struct* p = new_struct(0xdeadbeef, foo);
  print_struct(p);
  free(p); // feed here

  struct my_struct* q = new_struct(0xdeadbeef, bar);
  print_struct(p /* note */);  // use after
  free(q);
}

// Double free
void example4() {
  struct my_struct* p = new_struct(0xdeadbeef, foo);
  print_struct(p);
  free(p);
  free(p);
}

// Overflow buffer in the heap
void example5(char** argv) {
  char* buf = malloc(10);
  struct my_struct* p = new_struct(0xdeadbeef, foo);

  // copy into buffer
  strcpy(buf, argv[1]);

  // print struct
  print_struct(p);
}

// Use after free again
void example6(char** argv) {
  struct my_struct* p = new_struct(0xdeadbeef, foo);
  print_struct(p);
  free(p);

  // Allocate buffer and copy string into buffer
  char* buf = malloc(8);
  strcpy(buf, argv[1]); // ok!

  // print struct
  print_struct(p); // use freed p (UAF)
}

int main(int argc, char**argv) {
  // example1();
  // example2();
  // example3();
  // example4();
  // example5(argv);
  // TRIGGER: ./example $(python2 -c "print 'AAAAAAAAAAAABBBBCCCC\xe4\x9f\x04\x08'")
  example6(argv);
  // TRIGGER: ./example $(python2 -c "print 'AAAA\xe4\x9f\x04\x08'")
  return 0;
}
