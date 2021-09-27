CC := gcc
#CFLAGS := -m32 -static -U_FORTIFY_SOURCE -fno-stack-protector -zexecstack
CFLAGS := -m32 -O0 -ggdb -static -U_FORTIFY_SOURCE -fno-stack-protector -zexecstack -no-pie
CXXFLAGS := -m32 -O0 -ggdb -static -U_FORTIFY_SOURCE -fno-stack-protector -zexecstack -no-pie

all: example example2

clean:
	-rm example
	-rm example2

example: example.c
example2: example2.cpp
