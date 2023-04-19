#include "main.h"

/**
 * execute - function excecutes the system cmd
 * Discription:
 *
 * @values: cmd values
 * Return: void
*/
void execute(char **values)
{
	char *cmd = NULL, *actual_command = NULL;

	if (values)
	{
		cmd = values[0];
		actual_command = which(cmd);

		if (execve(actual_command, values, NULL) == -1)
		{
			perror("Error:");
		}
	}
}
