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
	char *cmd = NULL;

	if (values)
	{
		cmd = values[0];

		if (execve(cmd, values, NULL) == -1)
		{
			perror("Error:");
		}
	}
}
