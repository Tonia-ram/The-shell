#include "main.h"

void chomp(char *s)
{
	while(*s && *s != '\n' && *s != '\r')
		s++;
	*s = 0;
}

/**
 * input_handler - parses input from user
 *
 * Discription: First we check the parameter 'char *prompt'for a NULL condition
 * , if not NUll we proceed to print the prompt then store the users input
 * using the function getline() `man getline`. If the users input is either
 * Ctrl + D or exit the function will return a -1 else the input string will
 * be copied to the input_copy variable.
 *
 * @prompt: The string to print as a promt to the user
 * @input: The variable that will be storing the input
 * @input_copy: The varaible that will be storing the copy of the input
 *
 * Return: 1 is success 0 is error
*/
int input_handler(char *prompt, char **input, char **input_copy)
{
	size_t number_of_malloc_bytes_allocated;
	ssize_t number_of_characters_read;

	number_of_characters_read = 0;
	number_of_malloc_bytes_allocated = 0;

	if (prompt == NULL)
		prompt = "($) ";

	write(STDOUT_FILENO, prompt, sizeof(char) * strlen(prompt));

	*input = *input_copy = NULL;

	number_of_characters_read = _get_command_line(input,
			&number_of_malloc_bytes_allocated,
			STDIN_FILENO);
	if (number_of_characters_read == -1)
	{
		printf("Exiting shell....\n");
		return (0);
	}

	*input_copy = malloc(sizeof(char) * number_of_characters_read);

	if (*input_copy == NULL)
	{
		perror("hsh: memory allocation error");
		return (0);
	}
	
	chomp(*input);
	strcpy(*input_copy, *input);

	printf("\ninput_handler()\n");
	printf("input = %s\ninput_copy = %s", *input, *input_copy);

	return (1);
}
