# Assignment 1 *(20 pts)*

**Deadline: Wednesday, October 9, 2019 by 1:59:59 PM**

**Early Turn-In: Sunday, October 6, 2019 by 11:59:59 PM (10% bonus)**

The goal of this assignment is to become familiar with the setup that will be used for future
assignments, such as the use of a virtual machine and the included turn-in script, as well as the
basics of working with gdb and writing programs in x86 assembly.

## Getting Started

To complete this assignment, you will be provided with a VirtualBox VM pre-populated with the
assignment files.

### VM Image

In order to match the environment in which your submission will be graded, all work for this
assignment must be done on the VirtualBox VM we provide, named `pa1box`. You can download the VM
image [**here**](https://drive.google.com/uc?id=1thaE-D_uMTqgGl6xdcTrE19lgAgkb2H-&export=download).

The VM is configured with two users: `student`, with password `hacktheplanet`; and `root`, with
password `hackallthethings`. The VM is configured with SSH on port 2222. Please note that SSH is
disabled for `root`, so you can only SSH in as the `student` user. You can still log in as `root`
using `su` or by logging into the VM directly.

To SSH into the VM:

```
ssh -p 2222 student@127.0.0.1
```

To copy files from your computer to the VM:

```
scp -P 2222 -r /path/to/files/ student@127.0.0.1:/home/student
```

To copy files from the VM to your computer:

```
scp -P 2222 student@127.0.0.1:/path/to/files/ /destination/path
```

## Part 1: Using GDB *(10 pts)*

Files for this sub-assignment are located in the `gdb` subdirectory of the `student` user's home
directory in the VM image; that is, `/home/student/gdb`. SSH into the VM and `cd` into that
directory to begin working on it.

Inside the `gdb` directory, you'll find `fib.c`, a C program demonstrating the Fibonacci sequence;
a `Makefile`; and `hw1.txt`, in which you'll record your responses to the questions below. The
first step is to compile `fib` by running `make` on the command line.

To run the `fib` executable in GDB, run `gdb fib`.
I recommend the following workflow in GDB:

1. **Starting.** Set breakpoints that you can later use for analysis:
    - `b foo` &mdash; break at function `foo`
    - `b *0x08048489` &mdash; break at the instruction at address 0x08048489
    - `r` &mdash; run the executable
2. **Analyzing.** Examine memory, registers, etc; disassemble code; show stack frames, backtrace,
   etc; and more:
    - `disas foo` &mdash; disassemble function `foo`
    - `i r` &mdash; view registers
    - `where` &mdash; view stack frames
    - `x <loc>` &mdash; examine memory
    - `x $eip` &mdash; examine current instruction pointer
    - `x /10x $esp` &mdash; examine 10 words at top of stack
    - `x /10x buf` &mdash; examine 10 words in `buf`
    - `x /10i $eip` &mdash; examine 10 instructions starting at instruction pointer
    - `x /10i foo` &mdash; examine 10 instructions starting at `foo`
3. **Continuing.** Continue analysis:
    - `c` &mdash; continue execution until next breakpoint/watchpoint
    - `si` &mdash; step to the next instruction
    - `s` &mdash; step to the next line of source code

Note that this is only a cursory overview of GDB; much more info is available from online
resources.

### Assignment Instructions

Complete the following exercises and **fill out [`hw1.txt`](../resources/hw1.txt)** with your answers.

1. What is the value, in hex, of the `ecx` register when the function `f` is called? *(2 pts)*
2. Which register stores the value of the variable `i` in the function main? *(2 pts)*
3. What is the address, in hex, of the function `f`? *(2 pts)*
4. What is the name of the 6th instruction of the function `f`? *(2 pts)*
5. When `f` completes after being called from `main`, to which address in `main` does control
   return? Write your answer in hex form. *(2 pts)*

### Submission

Submit `hw1.txt` to "1a. gdb" on Gradescope. Login details can be found on the [about page](../about).
Gradescope will check that it has successfully detected your answers, but it will not give you your grade
until the due date.

## Part 2: `echo` in x86 *(10 pts)*

Files for this sub-assignment are located in the `x86` subdirectory of the `student` user's home
directory in the VM image; that is, `/home/student/x86`. SSH into the VM and `cd` into that
directory to begin working on it.

For this part, you will be implementing a simplified version of the familiar `echo` command, using
raw x86 assembly code. The goal of this assignment is to familiarize you with writing programs
directly in x86.

Your `echo` command must behave as follows:

- When run with a single command line argument (e.g., `./echo Hello`):
    1. Prints that argument back to the console's standard output (stdout).
    2. Prints a trailing newline (`\n`).
    3. Exits with code 0.
- When run with too few command line arguments (e.g., `./echo`) or too many (e.g., `./echo Hello
  World`):
    1. Prints *exactly* the error message `This command expects exactly one argument.` &mdash;
       followed by a trailing newline (`\n`) &mdash; to the console's standard *error* (stderr).
    2. Exits with code 1.

Your code should be written in the file `echo.s` inside the `x86` directory. A heavily-commented
example `echo.s` is provided, which simply prints the message `Hello World` (followed by a trailing
newline) to stdout. Your job is to modify this program to meet the specification for `echo` above.

A `Makefile` is included, so you can build the `echo` binary by running `make` from the command line.

### Helpful Hints

- In a Linux program, stdout is file descriptor number 1 and stderr is number 2.
- Linux programs start with `argc` at the top of the stack, accessible at `0(%esp)` from
  x86-assembly programs. Below it is `argv`, the array of pointers to *(null-terminated)* strings
  passed into the program as arguments. So `argv[0]` can be accessed from x86-assembly programs at
  `4(%esp)`, `argv[1]` at `8(%esp)`, `argv[2]` at `12(%esp)`, and so on.
- `argv[0]` is the name of the program executed, *not* the first argument, which is `argv[1]` if
  supplied (or `8(%esp)` for our purposes). Then `argc` (or `0(%esp)`) will be 1 if the program was
  not passed any arguments, 2 if it was passed 1 argument, and so on.
- This [table of Linux system calls](https://syscalls.kernelgrok.com/) may come in handy.

### Submission


Submit `echo.s` to "1b. x86 echo" on Gradescope. Login details can be found on the [about page](../about).

## Bugs

If you find a bug in this assignment please create an issue
[here](https://github.com/PLSysSec/cse127-winter19/issues).
