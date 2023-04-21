#include "main.h"

int is_builtin(char **command_array)
{
	if (command_array == NULL)
		return (0);
	if (command_array[0] == NULL)
		return (0);
	
	if (strcmp(command_array[0], "exit") == 0)
		return (1);
	else if (strcmp(command_array[0], "env") == 0)
		return (1);

	return (0);	
}

int builin_handler(char **command_array, char **envp)
{
	if (command_array == NULL)
		return (0);
	if (command_array[0] == NULL)
		return (0);

	if (strcmp(command_array[0], "exit") == 0)
	{
		if (command_array[1] != NULL)
			exit(atoi(command_array[1]));
		else
			exit(0);
	}
	else if (strcmp(command_array[0], "env") == 0)
	{
		unsigned int i;
		
		i = 0;
		while (envp[i] != NULL)
		{
			printf("%s\n", envp[i]);
			i++;
		}
		return (0);
	}


	return (1);
}
