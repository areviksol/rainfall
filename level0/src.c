#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	int num;

	__uid_t uid ;
	__gid_t gid ;
	
	num = atoi(argv[1]);
	if (num == 423)
	{
		char* command_argumnets[2];
		command_argumnets[0] = strdup("/bin/sh");
		command_argumnets[1] = NULL;
		uid = geteuid();
		gid = getegid();

		setresgid(gid, gid, gid);
		setresuid(uid, uid, uid);

		execve(command_argumnets[0], argv, NULL);
	}
	else
	{
		printf("No !\n");
	}
}