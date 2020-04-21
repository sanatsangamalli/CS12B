#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char **argv)
{
	int fd;													//int representing file descriptor.
	ssize_t bytesRead = 1, bytesWritten = 1;				//initialized variables for bytes read and written
	uint8_t buf[1024];										//array of bytes named buf
	if(argc == 1)											//base case where there are no arguments
	{
		while(bytesRead > 0)								//while loop runs while there are arguments to be read
		{
			bytesRead = read(STDIN_FILENO, buf, 1024);		//read returns number of characters read, then set to bytesRead using macro STDIN_FILENO
			bytesWritten = write(STDOUT_FILENO, buf, bytesRead);	//write returns number of characters written, then set to bytesWritten using macro STDOUT_FILENO
		}
	}
	for(int i = 1; i < argc; i++)							//for loop to run through all the arguments starts at 1 because argv[0] is always the program being executed
	{
		fd = open(argv[i], O_RDONLY);						//set file descriptor by calling open function and passing in the current argument and using the read only flag
		if(fd == -1)										//if fd is -1 then file did not open and error case is handled
		{
			perror("cat");
			exit(errno);
		}
		do													//do while loop runs while number of bytesRead because there are arguments to be read
		{
			bytesRead = read(fd, buf, 1024);				//read returns number of characters read, then set to bytesRead
			if(bytesRead == -1)								//if the number of bytes read is -1 then there is an error and the error case is handled
			{
				perror("cat");
				exit(errno);
			}
			bytesWritten = write(STDOUT_FILENO, buf, bytesRead);		//write returns number of characters written, then set to bytesWritten
			if(bytesWritten == -1)							//if the number of bytes written is -1 there is an error and the error case is handled
			{
				perror("cat");
				exit(errno);
			}			
		}while(bytesRead > 0);								//while condition
		int closed = close(fd);								//closes open file descriptor
		if(closed == -1)									//if closed is -1 there is an error and the error case is handled
		{
			perror("cat");
			exit(errno);
		}
		write(STDOUT_FILENO, "\n", 1);						//this makes a new line after each file is added
	}
	return 0;												//return statement 
}