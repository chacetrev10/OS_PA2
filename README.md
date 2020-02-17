# OS_PA2


**Contact Info:**
Chace Trevino
chtr8005@colorado.edu



**Makefile**

-File that contains the command that tells the compiler to create a module of name pa2_char_driver.o




**pa2_char_driver.c**

-This file contains the information that allows the computer to control the connected device. This allows the computer to use the device without knowing explicit details of how the hardware works.




**pa2Test.c**

-Test program that checks to see if the driver's functions are working correctly. 





**To install and configure module/device file:**

1)Download files

2)sudo make -C /lib/modules/$(uname -r)/build M=$PWD modules   
(This will create kernel module which allows you to insert module into kernel)

3)sudo insmod pa2_char_driver.ko 

(Type lsmod or dmesg to see if module was inserted correctly)

4)sudo mknod –m 777 /dev/pa2_character_device c 240 0

(This will create the device file that the device driver is associated with)


**After module is inserted, to build and run test program:**

1)gcc pa2Test.c -o pa2Test 

2)./pa2Test

3)Follow program instructions. When using seek function, corresponding whence values:

whence = 0 (SEEK_SET): the current position is set to the value of the offset
whence = 1 (SEEK_CUR): the current position is incremented by offset bytes (note that offset can be negative). 
whence = 2 (SEEK_END): the current position is set to offset bytes before the end of the file


**When done using LKM:**

sudo rmmod pa2_char_driver

(Type lsmod or dmesg to see if module exited correctly)





