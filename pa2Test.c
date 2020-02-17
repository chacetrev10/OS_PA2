#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

 
#define BUFFER_LENGTH 1024              ///< The buffer length (crude but fine)
static char receive[BUFFER_LENGTH];     ///< The receive buffer from the LKM
 
int main(){
   int ret, dev,bytes, currentPos;
   int whence, offset;
   char option= 0;
   char test = 'e';
   char message[BUFFER_LENGTH];

   dev = open("/dev/pa2_character_device", O_RDWR);             // Open the device with read/write access
		    if (dev< 0){
		      perror("Failed to open the device...");
		      return errno;
		   }

   while(option != test){
	   printf("Welcome...\nPress r to read from device\nPress w to write to the device\nPress s to seek into the device\nPress e to exit from the device\n");
	   scanf(" %c", &option);
	   switch(option){

			case 'r':
				printf("Enter number of bytes you would like to read:\n");
				scanf(" %d", &bytes);
				char *receive = malloc(bytes);
				ret = read(dev, receive,bytes);  
				printf("The received message is: [%s]\n", receive);
				break;

			case 'w':
				printf("Enter data you want to write to the device:\n");
				scanf(" %[^\n]%*c", message);
				ret = write(dev, message, strlen(message));
				break;


			case 's':
				printf("Enter an offset value:");
				scanf(" %d", &offset);
				printf("Enter a whence value:");
				scanf(" %d", &whence);
				ret = llseek(dev,offset, whence);
				if ( ret == -1){
					printf("The inputted offset is out of bounds\n");
				}
				break;

			case 'e':
				printf("Goodbye\n");
				break;

			default :
				printf("Sorry %c is not an option\n", option);
				break;

	}

}
	return 0;
}





















   

int main (int argc, char argv[]){
	int dev,ret;
	dev = open("/dev/pa2_character_device");
	ret = write(dev,"hello",strlen("hello"));
	ret = read(dev,get,130);
	printf("%d\n", strlen("hello"));
}
