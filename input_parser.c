#include "main.h"

/**
 * free_command_array_elements - Frees command array memory
 *
 * Description: Frees command array memory
 *
 * @command_array: Array storing commands
 * @last_position: Last position allocated memory in array
 *
 * Return: 1 if success 0 if failure
 */
int free_command_array_elements(char **command_array,unsigned int last_position)
{
	unsigned int input_position_free;

	perror("\n***Command array memory malloc error***\n");
	for (input_position_free = 0; input_position_free <= last_position;
			input_position_free++)
		free(command_array[input_position_free]);
	free(command_array);
	return (0);
}

/**
 * token_splitter - Splits the tokens by delimeter into given array
 *
 * Description: Splits the tokens by delimeter into given array
 *
 * @input: Input string
 * @seperator: delimeter
 * @command_array: Array to store split commands
 *
 * Return: 1 if success 0 if failure
 */
int token_splitter(char **input, const char *seperator, char **command_array)
{
	char *token;
	unsigned int input_position, i;

	if (seperator == NULL)
	{
		perror("\n***token_counter() seperator/delimeter is NULL***\n");
		return (0);
	}

	if (input == NULL || *input == NULL)
	{
		perror("\n***token_counter() input is NULL***\n");
		return (0);
	}

	token = strtok(*input, seperator);

	for (input_position = 0; token != NULL; input_position++)
	{
		command_array[input_position] = malloc(sizeof(char) * (strlen(token)));
		if (command_array[input_position] == NULL)
			free_command_array_elements(command_array, input_position);
		strcpy(command_array[input_position], token);
		printf("\ntoken = %s\n", token);
		token = strtok(NULL, seperator);
	}
	command_array[input_position] = NULL;

	printf("\ntoken_splitter()\n");
	for (i = 0; command_array[i]; i++)
		printf("length = %lu\ncommand_array[%d] = %s\n",
				strlen(command_array[i]), i, command_array[i]);

	free (token);
	return (1);
}

/**
 * token_counter - Counts the number of tokens
 *
 * Description: Counts the number of tokens
 *
 * @input: The input string
 * @seperator: the delimeter
 *
 * Return: 0 if failure or number of tokens
 */
unsigned int token_counter(char **input, const char *seperator)
{
	char *token;
	unsigned int token_count;

	if (seperator == NULL)
	{
		perror("\n***token_counter() seperator/delimeter is NULL***\n");
		return (0);
	}

	if (input == NULL || *input == NULL)
	{
		perror("\n***token_counter() input is NULL***\n");
		return (0);
	}

	token = strtok(*input, seperator);
	token_count = 0;

	while (token != NULL)
	{
		printf("\ntoken = %s\n", token);
		token_count++;
		token = strtok(NULL, seperator);
	}

	token_count++;

	free(token);

	printf("\ntoken_counter()\ninput = %s\ntoken_count = %d",
			*input, token_count);
	return (token_count);
}

/**
 * input_parser - parses input from user
 *
 * Discription: parse input from user
 *
 * @seperator: The string to print as a promt to the user
 * @input: The variable that will be storing the input
 * @input_copy: The varaible that will be storing the copy of the input
 * @command_array: Array of characters that will be storing the commands
 *
 * Return: 1 if success 0 if error
*/
int input_parser(char **input, char **input_copy,
		char **command_array)
{
	unsigned int token_count;
	int result;

	token_count = token_counter(input, " ");

	if (token_count == 1)
	{
		perror("\n***No Argument was given***\n");
		return (0);
	}

	*command_array = malloc(sizeof(char *) * token_count);

	if (*command_array == NULL)
	{
		perror("\n***Command Array Malloc Error!!***\n");
		return (0);
	}

	result = token_splitter(input_copy, " ", command_array);

	return (result);
}
