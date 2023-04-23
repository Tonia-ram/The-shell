#include "main.h"

char *_strtok(char **input, const char *separator, char **command_array)
{
	int postion;
	position = 0;

	while (*input[position] != '\0')
	{
		if (*input[postion] == separator)
		{
			*command_array[token_position] = malloc(sizeof(char) * token_length + 1);
			if (*command_array[token_position] == NULL)
			{
				perror("_strtok unable to allocate memory for command array");
				return (NULL);
			}
			strncpy(*command_array[token_position], *(*input[position], token_length));
			strcat(*command_array[token_position], "\0");
		}
		position++;
	}
}
