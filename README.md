#Buffer Overflow

The objective of this project is to learn how to analyze whether a program has a buffer
overflow (BOF) vulnerability, how to exploit BOF and how to defend against BOF.
BOF is an anomaly that violates memory safety. If you give an input that is longer
than expected length, it would be written out of bounds to a block of fixed pre-
allocated memory. This situation leads to data corruption and crash of the program
or executes malicious codes by changing control flow of the program. To exploit buffer overflow properly, we have to install Ubuntu 14.04.03 LTS 32-Bit version OS.

We have to disable address space randomization (ASR). ASR is able to put address space targets in unpredictable locations. If an attacker attempts to exploit an incorret address space location, the target application will crash, stopping the attack and alerting the system. We don't need these kind of things if we want to write Buffer Overflow exploits. 

Disable ASR

```$ sudo systcl -w kernel .randomize_va_space=0

[sudo] password for : ```

The gcc compiler has a protection scheme called "Stack Guard". BOF attacks will not work with this scheme. We have to add `fno-stack-protector` option to our command. 

`$ gcc -fno-stack-protector -z exestack -g -o sample sample.c`

-g - indicates that you can analyze a program with gdb.
-o - name of executable program.

There are security mechanisms against attacks like BOF that use shell programs like /bin/sh linked to /bin/bash. Thus, privileges for shell are dropped and we can not retain the privileges inside the shell. Therefore, we will use another shell, zsh.

```$ sudo su

[sudo] password for :`

apt-get install zsh`

cp /bin/sh /bin/sh.bak`

ln -s /bin/zsh /bin/sh```

## Experiment 1

Stay Tuned!
