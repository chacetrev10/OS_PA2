# OS_PA2


**Contact Info:**
Chace Trevino
chtr8005@colorado.edu

**cs3753_add.c**

-This file is the source code for the system call that completes the addition of two integers and copies result to user space.

Path: /home/kernel/linux-hwe-4.15.0/arch/kernel/cs3753_add.c



**Makefile**

-File that contains the command that tells the compiler to create a module of name pa2_char_driver.o




**pa2_char_driver.c**

-This file contains the information that allows the computer to control the connected device. This allows the computer to use the device without knowing explicit details of how the hardware works.

Path: /home/kernel/linux-hwe-4.15.0/arch/x86/entry/syscalls/syscall_64.tbl



**pa2Test.c**

-Contains the prototypes for all of the OS system calls

Path: /home/kernel/linux-hwe-4.15.0/include/linux/syscalls.h




**To compile and run program:**

cd Desktop

#OPTIONAL if you want to input your own custom numbers

nano addTest.c

#change first two int parameters to whatever values you want to add together

gcc addTest.c -o addTest

./addTest



