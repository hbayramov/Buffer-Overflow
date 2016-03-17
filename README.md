#Buffer Overflow

The objective of this project is to learn how to analyze whether a program has a buffer
overflow (BOF) vulnerability, how to exploit BOF and how to defend against BOF.
BOF is an anomaly that violates memory safety. If you give an input that is longer
than expected length, it would be written out of bounds to a block of fixed pre-
allocated memory. This situation leads to data corruption and crash of the program
or executes malicious codes by changing control flow of the program. To exploit buffer overflow properly, we have to install Ubuntu 14.04.03 LTS 32-Bit version OS.

We have to disable address space randomization (ASR). ASR is able to put address space targets in unpredictable locations. If an attacker attempts to exploit an incorret address space location, the target application will crash, stopping the attack and alerting the system. We don't need these kind of things if we want to write Buffer Overflow exploits. 

Disable ASR

```
$ sudo systcl -w kernel .randomize_va_space=0

[sudo] password for : 

```

1. 0 means No randomization. Everything is static.
2. 1 means Conservative randomization. Shared libraries, stack, mmap(), VDSO and heap are randomized.
3. 2 means Full randomization. In addition to elements listed in the previous point, memory managed through brk() is also randomized.

randomize_va_space value will be set to 2 after reboot. We can disable ASR permanently by adding `sudo nano /etc/sysctl.d/01-disable-aslr.conf` containing `kernel.randomize_va_space=0`

The gcc compiler has a protection scheme called "Stack Guard". BOF attacks will not work with this scheme. We have to add `fno-stack-protector` option to our command. 

`$ gcc -fno-stack-protector -z exestack -g -o sample sample.c`

-g - indicates that you can analyze a program with gdb.
-o - name of executable program.

There are security mechanisms against attacks like BOF that use shell programs like /bin/sh linked to /bin/bash. Thus, privileges for shell are dropped and we can not retain the privileges inside the shell. Therefore, we will use another shell, zsh.

```
$ sudo su

[sudo] password for :

apt-get install zsh

cp /bin/sh /bin/sh.bak

ln -s /bin/zsh /bin/sh

```

## Experiment 1

![valid-input-1](https://github.com/wlgzaor/Buffer-Overflow/blob/master/valid-input-1.png)

We firstly executed these commands to check stack boundaries:

start
info registers

The important registers for us are $esp (top of the stack) and $ebp (bottom of the stack). These registers can tell us that where the bof function starts and ends.  Our bof function starts at 0bfffee90 and ends 0bfffef18.

Then x/80x $esp command executed to examine 80 hexadecimal words, starting at $esp. 


Bof function starts at 0bfffef90 and ends 0bfffef18.  The first word after $ebp actually is a return address of bof but we are gonna talk about this later. 

We also defined breakpoints at *main+48 (at return instruction of main) and *bof+27 (right after strcpy function). Input were sequence of 's' characters (smaller than 100). 

![valid-input-2](https://github.com/wlgzaor/Buffer-Overflow/valid-input-2.png)

Here we can see that 's' (73 in ASCII) characters fill the appropriate field of stack and return address  wasn't overwritten by 's' characters.

![valid-input-3](https://github.com/wlgzaor/Buffer-Overflow/valid-input-3.png)

We checked current eip by typing info frame command and there is no changes. Later we will see that how the instruction pointer changes when user enters invalid input.

EIP holds the memory address of next instruction that would be executed.

Info frame command can give us information about stack frames. Now we will try to interpret these     output that you see above. 

###### Stack level 0

Frame number in backtrace, 0 is current executing frame, which grows downwards, in consistence with the stack.

###### Frame at 0bfffef20

Starting memory address of this stack

###### eip = 08048498 in bof (bof.c: 13); saved eip = 080484be 

We said that eip is register for next instruction to execute. So 0*8048498 will be next instruction to execute (line 13 of bof).  

###### saved eip 

080484be is called return address. Pushed into stack upon CALL (save it for return).

###### Arglist at 0bffef18 

The starting address of arguments

###### Locals at 0bfffef18

The starting address of locals 


###### Previous frame's sp is 0bfffef20 

The previous frame's stack pointer point to (the caller frame), at the moment of calling, it also the starting memory address of called stack frame.

###### Saved Registers

* ebp at 0bffef18 address where ebp register of caller's stack frame saved.  (it is the register, not the caller´s stack address). i.e., corresponding to "PUSH %ebp". "ebp" is the register usually considered as the starting address of the locals of this stack frame, which use "offset" to address. 

* eip at 0bfffef1c as mentioned before, but here is the address of the stack (which contains the value "080484be")


![invalid-input-1](https://github.com/wlgzaor/Buffer-Overflow/invalid-input-1.png)

Now we see that return address (first word after ebp) overwritten to 0737373 (ebp was 0*bfffef18).

![invalid-input-1](https://github.com/wlgzaor/Buffer-Overflow/invalid-input-2.png)

We can check eip register to see changes using info frame. Saved eip updated to 0737373 and there have no instruction like 0737373. So we got segmentation  fault.


## Experiment 2

Will be added after deadline.
