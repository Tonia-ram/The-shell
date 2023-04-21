#include "main.h"

/**
 * execute - function excecutes the system command
 *
 * Discription:
 *
 * @command_array: command command_array
 *
 * Return: void
*/
void execute(char **command_array, const char *path, char **envp)
{
	char *command, *which_command;

	command = which_command = NULL;


	if (command_array)
	{

		if (is_builtin(command_array))
		{
			if (builin_handler(command_array, envp))
				return;
		}
		command = command_array[0];
		which_command = which(&command, path);

		if (DEBUG)
		{
			printf("\nexecute()\n");
			printf("command_len = %lu\ncommand = %s\n",
					strlen(command), command);
			printf("which_command = %s\n", which_command);
		}
		if (which_command == NULL)
			perror("\n***excute() No Such Command***\n");
		else
		{
			pid_t pid = fork();

			if(pid < 0)
			{
				perror("\n***execute() Fork Failed!***\n");
			}
			else if (pid == 0)
			{
				if (DEBUG)
					printf("\nChild Process %d\n", getpid());
				if (execve(which_command, command_array, NULL) == -1)
					perror("\n***execute() Command Error***\n");
			}
			else
			{
				wait(NULL);
				if (DEBUG)
					printf("\nParent Process %d\n", getpid());
				printf("\n");
			}
		}
	}
	else
	{
		perror("\n***execute() No Arguments given!***\n");
	}
}
