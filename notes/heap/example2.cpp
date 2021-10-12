#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>

class Base {
  public:
    Base(uint32_t x) : x(x) {};
    uint32_t x;
    virtual void f() {
      printf("base: %x!\n", x);
    }
};

class Derived: public Base {
  public:
    Derived(uint32_t x) : Base(x) {};
    void f() {
      printf("derived: %x!\n", x);
    }
};

void print_base(Base* obj) {
  printf("obj = %p\n", obj);
  obj->f();
}


// Alloc-alloc, free-free
void example1() {
  Base* b = new Base(0xdeadbeef);
  print_base(b);
  
  Derived* d = new Derived(0x41414141);
  print_base(d);

  delete b;
  delete d;
}

// Alloc-free, alloc-free
void example2() {
  Base* b = new Base(0xdeadbeef);
  print_base(b);
  delete b;

  Derived* d = new Derived(0x41414141);
  print_base(d);
  delete d;
}


// User after free
void example3() {
  Base* b = new Base(0xdeadbeef);
  print_base(b);
  delete b;

  Derived* d = new Derived(0x41414141);

  print_base(b); // use after free
}

// Double free
void example4() {
  Base* b = new Base(0xdeadbeef);
  print_base(b);
  delete b;
  delete b;
}

void foo(Base* _this) {
  printf("foo: %x!\n", _this->x);
}

uint32_t fake_vtable[1] =  { (uint32_t) foo };

// Overflow buffer in the heap
void example5(char** argv) {
  char* buf = (char*)malloc(10);
  Base* b = new Base(0xdeadbeef);
  print_base(b);

  // copy into buffer
  strcpy(buf, argv[2]);

  // print class
  print_base(b);
}

// Use after free again
void example6(char** argv) {
  Base* b = new Base(0xdeadbeef);
  print_base(b);
  delete b;

  // Allocate buffer and copy string into buffer
  char* buf = (char*) malloc(8);
  strcpy(buf, argv[2]);

  // print class
  print_base(b);
}



int main(int argc, char**argv) {
  switch (strtol(argv[1], NULL, 10)) {
    case 1: example1(); return 0;
    case 2: example2(); return 0;
    case 3: example3(); return 0;
    case 4: example4(); return 0;
    case 5: example5(argv); return 0;
  // TRIGGER: ./example2 5 $(perl -e 'print ("A"x16);print pack("I!",0x80f9068);print("BBBB")')
    case 6: example6(argv); return 0;
  // TRIGGER: ./example2 6 $(perl -e 'print pack("I!",0x80f9068);print("BBBB")')
  }
  return 0;
}
