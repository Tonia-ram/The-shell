#include "main.h"

/**
 * main - Simple Shell Main
 *
 * Description: Entrypoint
 *
 * @ac: argument count
 * @argv: argument values array
 *
 * Return: 0 on success
 */
int main(int ac, char **argv, char **envp)
{
	char *prompt = "($) ";
	char *input, *input_copy;
	const char *path = getenv(PATH);

	input = input_copy = NULL;

	if (ac == 1)
	{
		while (1)
		{
			if (input_handler(prompt, &input, &input_copy))
			{
				if (input_parser(&input, &input_copy, argv))
					execute(argv, path, envp);
			}
			else
			{
				break;
			}
			free(input);
			free(input_copy);
		}
	}
	return (0);
}
