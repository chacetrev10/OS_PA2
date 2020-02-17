
#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

#define BUFFER_SIZE 1024

/* Define device_buffer and other global data structures you will need here */

int currentBuffer = 0;
char *device_buffer;
int openCount =0;
int closeCount =0;



	

ssize_t pa2_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	
	
	if (*offset + length < BUFFER_SIZE){
		copy_to_user(buffer, device_buffer+*offset, length);
		*offset+=length;
		printk(KERN_ALERT "%d bytes read\n", length);

	}else{
		copy_to_user(buffer, device_buffer+*offset, BUFFER_SIZE- *offset);	
		printk(KERN_ALERT "%d bytes read before end of buffer was reached\n", BUFFER_SIZE- *offset);
		*offset = BUFFER_SIZE;	
		

	}
	printk(KERN_ALERT "Current offset location after read: %d", *offset);
	/* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
	/* length is the length of the userspace buffer*/
	/* offset will be set to current position of the opened file after read*/
	/* copy_to_user function: source is device_buffer and destination is the userspace buffer *buffer */

	return 0;
}



ssize_t pa2_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{

	if (*offset + length < BUFFER_SIZE){
		copy_from_user(device_buffer+*offset,buffer,  length);
		printk(KERN_ALERT "%d bytes written\n", length);
		*offset+=length;

	}else{
		copy_from_user(device_buffer+*offset, buffer, BUFFER_SIZE- *offset);	
		printk(KERN_ALERT "%d bytes written  before end of buffer was reached\n", BUFFER_SIZE- *offset);
		*offset = BUFFER_SIZE;	
		

	}
	printk(KERN_ALERT "Current offset location after write: %d", *offset);
	/* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
	/* length is the length of the userspace buffer*/
	/* current position of the opened file*/
	/* copy_from_user function: destination is device_buffer and source is the userspace buffer *buffer */

	return 0;
}


int pa2_char_driver_open (struct inode *pinode, struct file *pfile)
{	
	openCount+=1;
	printk(KERN_ALERT "The device has been opened %d times" , openCount);
	/* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
	return 0;
}

int pa2_char_driver_close (struct inode *pinode, struct file *pfile)
{
	closeCount+=1;
	printk(KERN_ALERT "The device has been closed %d times" , closeCount);
	printk(KERN_ALERT"Closed");
	
	/* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
	return 0;
}

loff_t pa2_char_driver_seek (struct file *pfile, loff_t offset, int whence)
{

	switch(whence){
		case 0:
			if (offset <= BUFFER_SIZE && offset > -1){	
				pfile->f_pos = offset;
				printk(KERN_ALERT"current offset location: %d", offset);
			}else{
				printk(KERN_ALERT"%d is out of bounds", offset);
				return -1;
			}
			break;

		case 1:
			if (pfile->f_pos + offset <= BUFFER_SIZE && pfile->f_pos+ offset > -1){
				pfile->f_pos += offset;
				printk(KERN_ALERT"current offset location: %d", pfile->f_pos);
			}else{
				printk(KERN_ALERT "%d is out of bounds", pfile->f_pos + offset);
				return -1;
			}
			break;

		case 2:
			if(offset > -1 && BUFFER_SIZE - offset > -1){
				pfile->f_pos= BUFFER_SIZE - offset;
				printk(KERN_ALERT"current offset location: %d", pfile->f_pos);
			}else{
				printk(KERN_ALERT "%d is out of bounds", BUFFER_SIZE - offset);
				return -1;
			}
			break;

		default:
			printk(KERN_ALERT "%d is not a valid value for whence", whence);


	}
	/* Update open file position according to the values of offset and whence */
	return 0;
}

struct file_operations pa2_char_driver_file_operations = {

	.owner = THIS_MODULE,
	.read = pa2_char_driver_read,
	.write = pa2_char_driver_write,
	.open = pa2_char_driver_open,
	.release = pa2_char_driver_close,
	.llseek = pa2_char_driver_seek

	
	/* add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code*/
};

static int pa2_char_driver_init(void)
{	
	register_chrdev(240,"pa2_character_device",&pa2_char_driver_file_operations);
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
	/* print to the log file that the init function is called.*/
	/* register the device */
	return 0;
}

static void pa2_char_driver_exit(void)
{
	unregister_chrdev(240,"pa2_character_device");
	printk(KERN_ALERT "exiting %s function\n",__FUNCTION__);
	kfree(device_buffer);
	/* print to the log file that the exit function is called.*/
	/* unregister  the device using the register_chrdev() function. */
}

module_init(pa2_char_driver_init);
module_exit(pa2_char_driver_exit);

/* add module_init and module_exit to point to the corresponding init and exit function*/

