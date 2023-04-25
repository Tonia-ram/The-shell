#include "main.h"

int setenv_var(const char* name, const char* value)
{
    int status = setenv(name, value, 1);
    if (status != 0) {
        perror("setenv");
    }
    return status;
}

int unsetenv_var(const char* name) {
    int status = unsetenv(name);
    if (status != 0) {
        perror("unsetenv");
    }
    return status;
}
int change_directory(const char *path)
{
    int ret = chdir(path);
    if (ret == -1) {
        perror("chdir");
        return EXIT_FAILURE;
    }
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working directory: %s\n", cwd);
	setenv_var("PWD", cwd);
    }
    else
    {
        perror("getcwd");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

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
	else if (strcmp(command_array[0], "setenv") == 0)
		return (1);
	else if (strcmp(command_array[0], "unsetenv") == 0)
		return (1);
	else if (strcmp(command_array[0], "cd") == 0)
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
	else if (strcmp(command_array[0], "setenv") == 0)
	{
		if (command_array[1] == NULL || command_array[2] == NULL)
       			return (0);
		setenv_var(command_array[1], command_array[2]);
	}
	else if (strcmp(command_array[0], "unsetenv") == 0)
	{
	if (command_array[1] == NULL)
		return (0);
	unsetenv_var(command_array[1]);
	}
	else if (strcmp(command_array[0], "cd") == 0)
	{
		if (command_array[1] == NULL)
		{
		change_directory(getenv("HOME"));
		}
		else
		{
			if (strcmp(command_array[1], "-") == 0)
			{
				change_directory(getenv("OLD_PWD"));
			}
			else 
			{
				change_directory(command_array[1]);
			}
		}
	}
	return (1);
}
