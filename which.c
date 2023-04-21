#include "main.h"

/**
 * which - gets location of the command path
 * Discription:
 *
 * @cmd: the string command
 * Return: the full path
*/
char *which(char **cmd, const char *path)
{
	char *path_token, *path_copy, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	if (*cmd == NULL)
	{
		perror("\n***which() Error cmd null***\n");
		return (NULL);
	}

	printf("\nwhich()\n");
	printf("cmd = %s\n", *cmd);
	printf("cmd_len = %lu\n", strlen(*cmd));
	printf("PATH = \"%s\"\n", PATH);
	printf("path = %s\n", path);

	if (path)
	{
		path_copy = strdup(path);
		command_length = strlen(*cmd);
		path_token = strtok(path_copy, ":");
		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
			if (file_path == NULL)
			{
				perror("\n***which() File_PATH Error***\n");
				return (NULL);
			}
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, *cmd);
			strcat(file_path, "\0");

			printf("\nfile_path = %s\nlength = %lu",
					file_path, strlen(file_path));

			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(*cmd, &buffer) == 0)
		{
			return (*cmd);
		}
		return (NULL);
	}
	return (NULL);
}
