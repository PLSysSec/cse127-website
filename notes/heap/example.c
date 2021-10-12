#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct my_struct {
  uint32_t x;
  void (*f)();
};
struct my_struct* new_my_struct(uint32_t x, void (*f)());
void print_my_struct(struct my_struct* p);

struct your_struct {
  uint32_t x[3];
  void (*f)();
};
struct your_struct* new_your_struct(uint32_t x, void (*f)());
void print_your_struct(struct your_struct* p);

void foo() { printf("woo! in foo!\n"); }
void bar() { printf("woo! in bar!\n"); }

void print_header(unsigned int* p);

// Alloc-alloc, free-free
void example1() {
  struct my_struct* p = new_my_struct(0xdeadbeef, foo);
  print_my_struct(p);

  struct your_struct* q = new_your_struct(0xdeadbeef, bar);
  print_your_struct(q);

  print_header(p);
  print_header(q);

  free(p);
  free(q);
}

// Alloc-free, alloc-free
void example2() {
  struct my_struct* p = new_my_struct(0xdeadbeef, foo);
  print_my_struct(p);
  free(p);

  struct my_struct* q = new_my_struct(0xdeadbeef, bar);
  print_my_struct(q);
  free(q);
}

// User after free
void example3() {
  struct my_struct* p = new_my_struct(0xdeadbeef, foo);
  print_my_struct(p);
  free(p); // feed here

  struct my_struct* q = new_my_struct(0xdeadbeef, bar);

  print_my_struct(p);  // use after free
}

// Double free
void example4() {
  struct my_struct* p = new_my_struct(0xdeadbeef, foo);
  print_my_struct(p);
  free(p);
  free(p);
}

// Overflow buffer in the heap
void example5(char** argv) {
  char* buf = malloc(10);
  struct my_struct* p = new_my_struct(0xdeadbeef, foo);

  // copy into buffer
  strcpy(buf, argv[2]);

  // print struct
  print_my_struct(p);
}

// Use after free again
void example6(char** argv) {
  struct my_struct* p = new_my_struct(0xdeadbeef, foo);
  print_my_struct(p);
  free(p);

  // Allocate buffer and copy string into buffer
  char* buf = malloc(8);
  strcpy(buf, argv[2]); // ok!

  // print struct
  print_my_struct(p); // use freed p (UAF)
}

int main(int argc, char**argv) {
  switch (strtol(argv[1], NULL, 10)) {
    case 1: example1(); return 0;
    case 2: example2(); return 0;
    case 3: example3(); return 0;
    case 4: example4(); return 0;
    case 5: example5(argv); return 0;
  // TRIGGER: ./example 5 $(perl -e 'print ("A" x 20); print pack("I!",0x8049940);')
    case 6: example6(argv); return 0;
  // TRIGGER: ./example 6 $(perl -e 'print ("A" x 4); print pack("I!",0x8049940);')
  }
  return 0;
}


// helpers

struct my_struct* new_my_struct(uint32_t x, void (*f)()) {
  struct my_struct* p = malloc(sizeof(struct my_struct));
  p->x = x;
  p->f = f;
  return p;
}

struct your_struct* new_your_struct(uint32_t x, void (*f)()) {
  struct your_struct* p = malloc(sizeof(struct your_struct));
  for (int i = 0; i < 3; i++) {
    p->x[i] = x;
  }
  p->f = f;
  return p;
}

void print_header(unsigned int* p) {
  unsigned header = *(p-1);
  printf("size = 0x%x | . . P = %d\n", header&0xfffffffc, header&1);
}

void print_my_struct(struct my_struct* p) {
  printf("p = %p\nx = 0x%x\n", p, p->x);
  p->f();
  printf("\n");
}

void print_your_struct(struct your_struct* p) {
  printf("p = %p\nx = 0x%x\n...\n", p, p->x[0]);
  p->f();
  printf("\n");
}

