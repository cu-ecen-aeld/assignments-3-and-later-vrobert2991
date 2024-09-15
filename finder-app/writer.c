#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char ** argv)
{

if(argc != 3)
{
	syslog(LOG_ERR,"Invalid number of arguments: %d",argc);
	return 1;
}


int fd;
ssize_t bytes_written;
umask(0);
mode_t mode = S_IRWXU | S_IRWXG;
fd = open(argv[1],O_WRONLY | O_CREAT, mode);

openlog(NULL,0,LOG_USER);

if (fd == -1)
{
	syslog(LOG_ERR,"File can not be opened.");
	return 1;
}

bytes_written = write(fd,argv[2],strlen(argv[2]));

if (bytes_written != strlen(argv[2]))
{
	syslog(LOG_ERR,"Write to file failed.");
	return 1;	
}

if (close(fd) == -1)
{
	syslog(LOG_ERR,"File %d could not be closed.",fd);
	return 1;
}
syslog(LOG_ERR,"Writing %s to file %s",argv[2],argv[1]);
return 0;
}
