# Assignment 2 *75 pts + 25pts extra for sploit4*

**Deadline: Wednesday, January 29, 2020 by 1:59:59 PM**

**Early Turn-In: Sunday, January 26, 2020 by 11:59:59 PM (10% bonus)**

The goal of this assignment is to gain hands-on experience with the effects of buffer overflows and other memory-safety bugs. 

**sploit1-sploit3 are required. sploit4 is extra credit!**

- You will be provided a skeleton for implementing these exploits in C.
- You must not discuss your solution with other students until three days after the assignment deadline.
- You may consult any online references you wish.
- If you use any code in your answer that you did not write yourself, you must document that fact. Failure to do so will be considered a violation of the academic integrity policy.

## Getting Started

To complete this assignment you will be provided with a VirtualBox VM and a set of files.

### VM Image

In order to match the environment in which your submission will be graded, all work for this assignment must be done on the VirtualBox VM we have provided, named `pa2box`. You can download the VM image [**here**](https://drive.google.com/a/eng.ucsd.edu/uc?id=11GnFuU7-RC8nlwm9oKAlaGHfVquVGKBz&export=download).

Import the `pa2box.vbox` file into VirtualBox via the `Machine` &rarr; `Add` menu item. *Don't* create a brand-new VirtualBox VM or import the `pa2box-data.vmdk` file on its own: if you do this, you won't have the correct configuration.

After importing the VM, select it in the VirtualBox sidebar and start it with the green arrow button or the `Machine` &rarr; `Start` menu item. The VM is configured with two users: `student`, with password `hacktheplanet`; and `root`, with password `hackallthethings`. Instead of using the command line through VirtualBox, we recommend that you SSH into your VM from another client. The VM image is configured to expose an SSH server on port 2222 of your system's loopback address (`127.0.0.1`).

To SSH into the VM (from your host system running VirtualBox, ***not*** from inside the VM):

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

Please note that SSH is disabled for `root`, so you can only SSH in as the `student` user. You can still log in as `root` using `su` or by logging into the VM directly.

### Assignment Files

Starter files are included inside the `student` home directory of the VM image.

The `targets` directory contains a `Makefile` to generate target executables specific to your PID (as well as a folder called `base`, which you should not modify, used to generate the targets).

Exploit starter code can be found in the `sploits1`-`sploits4` directories: one per each of the four vulnerable target programs. Each of these contains a `Makefile`, a `shellcode.h` header file providing Aleph One's shellcode, and a `sploitN.c` file in which you should write your exploit code (in addition to an `assignment.toml` file, which should not be modified).

You will be writing an exploit for each of the four vulnerable programs provided in the assignment.  Each exploit, when run in the VM with its target installed setuid-root in `/tmp`,  should yield a root shell (`/bin/sh`). You can verify that the shell has been launched as `root` by typing `whoami`, to which you should see the response `root`. You *must* use Aleph One’s shellcode in `shellcode.h`,  as this will be used in the grading scripts.

For each exploit, in addition to your `.c` file, please also create a corresponding file `writeup.txt` containing a brief description of how the exploit works.

## Exploit Generation

To complete the assignment, you will need to: generate targets specific to your PID; use GDB to find vulnerabilities in the targets; and, finally, craft your exploit programs.

### Generating the Targets

Run `make generate` in the `targets` directory to create the four target source files specific to you. This will prompt you for your student ID (`A########` or `U########`), which will be used to randomize portions of the contents of `target1.c`-`target4.c`.

Run `make` to build the target binaries `target1`-`target4`.

Run `sudo make install` to copy the binaries into the `/tmp` directory.

Finally, run `sudo make setuid` to mark the binaries as setuid-root. If you forget this step, then your exploits will end up launching a normal shell instead of a root shell!

### Exploit Notes

For this assignment you should read and have a solid understanding of Aleph One’s “Smashing the Stack for Fun and Profit”.

Aleph One gives code that calculates addresses on the target’s stack based on addresses on the exploit’s stack. However, addresses on the exploit’s stack can change based on how the exploit is executed (working directory, arguments, environment, etc.). **You must therefore hard-code target stack locations in your exploits.**

You should not use a function such as `get_sp()` in the exploits you hand in. You should only modify the `sploitN.c` files and corresponding `writeup.txt` files; i.e., your exploits should work with unmodified Makefiles, targets, etc. In grading, the exploits may be run with a different working directory. Your exploits must work in these cases also.  If you hard-code the target's stack locations into your exploit you should be fine. Your exploit programs should not take any command-line arguments.

Shutting down the VM removes the files in /tmp; if you want to keep them, pause the VM and save its state!

## IMPORTANT: Using the shellcode
The shellcode is defined for you in `shellcode.h` inside each `sploitN/` directory. To use the shellcode in your sploit buffers, please **import the shellcode with `#include` and copy the contents programatically**. You can do this with `memcpy`, `strcpy`, or even just a `for` loop with array assignments. **Please do NOT manually copy-paste the shellcode string literal into your sploitN.c file**. While the sploit will still work, it may break grading.

## Using GDB

To run an exploit in GDB, run, e.g., `gdb sploit1` to execute `sploit1`.

Note that there are **two executables** when we run these programs, since, e.g., `sploit1` will execute `target1`. Because of this, you can use the following sample workflow to get started in GDB:

1. `b main` --- break at `main` in `sploit1.c`
2. `r` --- run the executable `sploit1`
3. `c` --- continue until `main` in `target1.c`
4. `b foo` --- set a breakpoint at `foo` in `target1.c`

Note that you will *not* be able to set breakpoints in `targetN` until the program has started executing `targetN`.
That is, e.g., if you tried to run `b foo` before step 3, you would get the error `Function "foo" not defined.`


Here are some additional GDB commands that may come in handy:

* `p var` --- prints the value of a variable named `var`
* `p buf` --- (if `buf` is an array) prints the contents of an array named `buf`
* `p &buf` --- prints the starting address of an array or variable named `buf`
* `i r` --- view registers
* `i frame` --- view info about the current stack frame
* `i stack` --- view high level info about the stack
* `help <command>` --- get help inside GDB about a particular command


Also refer back to the sample commands in Assignment 1.


Note that this is only a cursory overview of GDB; much more info is available from online
resources.


### Submission
1. Create a file named `PID` in the student home directory on the VM, and put your PID in it (ex: `A12345678`)
2. Run the following command from the student home directory `tar -czvf pa2.tar.gz PID sploit[1-4]/ targets/` This will create a `pa2.tar.gz` in the home directory with all your files in it. You can see what files were zipped by running `tar -tf pa2.tar.gz`
3. `scp` the `pa2.tar.gz` file to your local computer and submit to gradescope.

Note: The autograder will take time to set up, as it'll have to redirect your submissions somewhere else, where your sploits can be tested in the same VirtualBox environment. We'll post an update when it's up. In the meanwhile, you'll know your answer is correct if you followed the instructions above and you were able to get a root shell. 
