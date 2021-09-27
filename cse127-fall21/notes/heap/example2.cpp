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
  print_base(b /* note */);
  delete d;
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
  strcpy(buf, argv[1]);

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
  strcpy(buf, argv[1]);

  // print class
  print_base(b);
}



int main(int argc, char**argv) {
  // example1();
  // example2();
  // example3();
  // example4();
  // example5(argv);
  // TRIGGER: ./example2  $(python2 -c "print 'AAAAAAAABBBBCCCC\x68\x80\x0f\x08IIII'")
  example6(argv);

  // TRIGGER: ./example2  $(python2 -c "print '\x68\x80\x0f\x08AAAA'")
  return 0;
}
