#include "main.h"

ssize_t _get_command_line(char **input, size_t *n, int stream)
{
	char *buffer;
	ssize_t bytes_read, total_bytes_read;

	buffer = (char *) malloc(sizeof(char) * 1024);

	if (buffer == NULL)
		return (-1);

	bytes_read = read(stream, buffer, 1024);

	if (bytes_read == -1)
	{
		perror("An error occurred while trying to read the file.");
		free(buffer);
		return (-1);
	}
	else if (bytes_read == 0)
	{
		free(buffer);
		return (-1);
	}

	for (total_bytes_read = 0; buffer[total_bytes_read]; total_bytes_read++)
		if (DEBUG)
			printf("getline() input length %lu\tinput %s\n", total_bytes_read, buffer);
	*n = sizeof(char) * (total_bytes_read + 1);
	if (*input != NULL)
	{
		free(*input);
	}
	*input = (char *) malloc(*n);
	if (*input == NULL)
	{
		perror("\n***getline() pointer realloc error***\n");
		*n = 0;
		free(buffer);
		return (-1);
	}
	strncpy(*input, buffer, total_bytes_read);
	strcat(*input, "\0");

	if (DEBUG)
	{
		printf("\n_get_command_line()\n");
		printf("user: input: %s\n", *input);
		printf("info: bytes_read: %lu\n", bytes_read);
	}

	free(buffer);

	return (total_bytes_read);
}
