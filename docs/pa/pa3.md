# Assignment 3 *100pts*

**Deadline: Thursday, March 7, 2019 by 11:59:59 PM**

**Early Turn-In: Monday, March 4, 2019 by 11:59:59 PM (10% bonus)**

The goal of this assignment is to gain hands-on experience exploiting side channels. This assignment will demonstrate how side channels can be just as dangerous as the control flow vulnerabilities you exploited in Assignment 2.

You will be provided a two skeleton files (`memhack.c` and `timehack.c`) that you will use to exploit side channels present in a target library (`sysapp.c`) to obtain a protected key. You may consult any online references you wish. If you use any code in your answer that you did not write yourselves, you must document that fact. Failure to do so will be considered a violation of the academic integrity policy.

## Getting Started

To complete this assignment you will be provided with a VirtualBox VM and a set of files including a turn-in script.

### VM Image

In order to match the environment in which your submission will be graded, all work for this assignment must be done on the VirtualBox VM we have provided, named `pa3box`. You can download the VM image [**here**](https://drive.google.com/a/eng.ucsd.edu/uc?id=1q6foEy60Iex07_qyCJtQHDHwQ7VQXQWC&export=download).

Import the `pa3box.vbox` file into VirtualBox via the `Machine` &rarr; `Add` menu item. *Don't* create a brand-new VirtualBox VM or import the `pa3box-data.vmdk` file on its own: if you do this, you won't have the correct configuration.

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

Starter files are included inside the `student` user's home directory within the VM image.

There are two parts to this assignment, each with its own subdirectory, `memhack` and `timehack`. Each subdirectory contains exploit starter code (`memhack.c` or `timehack.c`), which imports a library (`sysapp.c`, with the same contents across the two subdirectories) with password-checking functionality vulnerable to side-channel attacks. You should *not* modify `sysapp.c`, only `memhack.c` and `timehack.c`. Each subdirectory contains a `Makefile` for building your exploits.

### Assignment Instructions

You will be writing two exploits, each of which takes advantage of a side channel, to obtain the password in `sysapp.c`. In `memhack.c`, you will exploit a memory-based side channel, and in `timehack.c` you will exploit a timing-based side channel. See Section 2 for specific details. Once both of your exploits can determine the password in `sysapp.c` and call the `hack_system()` function successfully, the assignment is complete. Additionally, for each exploit, provide a brief description of how it works in its corresponding `writeup.txt` file.

### Submitting Your Solutions

To submit your solution for each sub-assignment, run the `gradinator-submit` command from the corresponding `memhack` or `timehack` subdirectory and follow the prompts that appear. You may submit as many times as you like ahead of the deadline, but only your most recent submission will be counted. Note that each of the two sub-assignments ***must be submitted separately***.

For each sub-assignment, after submitting an attempted solution, you'll subsequently receive a message from our auto-grading server to your email address associated with this class. The email will contain a breakdown of the steps it took to grade your assignment, points earned (or not) at each step, and a total score for that sub-assignment. Each one is worth 50 points.

## Exploit Construction

### Memory-Based Side Channel

We recommend you start with the memory-based side channel because it is deterministic and doesn't have problems with noise. Look at the `check_pass()` function in `sysapp.c` and note two things:

1. The password string is passed by reference
2. The memory it points to is checked against the reference password one character at a time.

Now look in `memhack.c` and note how a buffer is allocated such that the page starting at page start is protected (i.e., accessing it will caused a segmentation fault, or SEGV) and the previous 32 characters are allocated. Now look at the demonstration function `demonstrate_signals()`, which shows how referencing any memory in the protected page will produce a fault as well as how to catch that fault in your program. You do not need to use this function; it is merely there to show you how to use signals to capture whether a memory reference touched a page or not.

Now you will want to create a framework (in `memhack.c`) to call `check_pass()` with different inputs and catching any resulting faults so you can determine if part of the password is correct. We suggest a loop over the maximum password size (32 characters) where for the first guess you store the password such that its first character is one byte before page start and then iterate between possible choices for the first character (when you get it right you will get a page fault). Repeat this to guess the entire password. Note that all ASCII symbols from ASCII 33 (`!`) to ASCII 126 (`∼`) can be used in the password. Other hints:

1. You are already given a page protected buffer with enough memory to crack the password. All you
   need to do is use it appropriately for each guess you make. 
2. The `demonstrate_signals` function handles all the segfaults for you. You can re-use almost all of it
   in your code.

### Timing-Based Side Channel

Unlike the memory-based side channel, the timing-based side channel will deal with noise. Go back and look at `check_pass()`. An artificial delay has been added when each character is checked to make your life easier (it’s possible to do the assignment without it but it would require a much more careful methodology). The execution time of `check_pass()` depends on how many characters you guess **correctly**.

Look in `timehack.c` and find a macro there for a function called `rdtsc()` which invokes the processors cycle counter (a clock that increments by one for each processor cycle that passes). In general, treat `rdtsc()` as a free running timer that returns a `long`. Insert a call to `rdtsc()` before the call to `check_pass()` and afterwards. Print the difference between these values to see how long (in cycles) the password checking ran. Run the program a few times. Now change the guess string so the first character is correct. Run again and see how the time difference changes. 

Now automate this entire process, in the style of the original approach in `memhack.c`. Note that unlike the `memhack` attack, the `timehack` problem will have to deal with **noise**. Depending on things like what other programs are running, the status of the cache, the contents of the branch target buffer, etc... there can be significant variability in the amount of time each check takes. This **will** matter in practice. You will want to run a lot of trials before you reach your conclusion about each character. Other hints:

1. Be careful in using `printf`’s.  These can blow out the instruction cache and data caches and perturb your results (i.e. overwhelm the timing effects you are trying to detect).
2. Be careful in averaging across trials. If your process is descheduled in the middle of a measurement, the time cost of that individual trial will be so large that it overwhelms everything else. Instead, the **median** is your friend. However, feel free to experiment if something does not work for you.
3. If time is not continuing to increase as you progress through characters, then you probably made a bad guess earlier. Backtrack.
4. `rdtsc()` will wrap around at some point. You may need to handle this outlier if it is causing issues.
5. Debugging advice: make a big array to hold your timing measurements and print them at the end.
6. Be sure to test a bunch of different passwords. We will when we grade.

### Final Notes

**Do not write a solution that simply checks all passwords exhaustively.** You will not get credit for this. This should be doable in linear time (we will stop programs that are running for excessive periods) and it will basically feel instantaneous for passwords of 8 characters or less (note we will not test passwords over 12 characters). We plan to do the testing/evaluation on our server.
