#include "main.h"
/**
 * de_allocator- cleans up result
 * @token_array:
 * @count:
 * 
 * Return: result
 */
void de_allocator(token_array result, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(result.tokens[i]);
    }
    free(result.tokens);
    result.num_tokens = 0;
    result.status_code = -1;
}
token_array allocate_token(token_array result, int count, int current_position, int last_position, char* input_string)
{
    result.tokens = realloc(result.tokens, sizeof(char*) * (count+1));
    if (result.tokens == NULL)
    {
	    de_allocator(result, count);
        return (result);
    }
    result.tokens[count] = malloc(sizeof(char) * (current_position-last_position+1));
    if (result.tokens[count] == NULL)
    {
	    de_allocator(result, count);
        return (result);
    }
    strncpy(result.tokens[count], input_string+last_position, current_position-last_position);
    result.tokens[count][current_position-last_position] = '\0';
    count++;
    result.num_tokens = count;
    result.status_code = 0;
    return (result);
}

/**
 * tokenizer - function tokenizes
 * Description:
 * @input_string:
 * @delimiter:
 * Return: A token array
 */

token_array tokenizer(char *input_string, char *delimiter)
{
	token_array result = { NULL, 0, 0 };
	int count = 0;
	int len = strlen(input_string);
	int delim_len = strlen(delimiter);
	int input_position = 0, current_position = 0, last_position = 0;

	while (input_position < len)
	{
		if (strncmp(input_string + input_position, delimiter, delim_len) == 0)
		{
			result = allocate_token(result, count, current_position, last_position, input_string);
			input_position += delim_len;
			last_position = current_position = input_position;
		}
		else
		{
			current_position++;
			input_position++;
		}
	}
	if (current_position > last_position)
	{
		result = allocate_token(result, count, current_position, last_position, input_string);
	}
	result.num_tokens = count;
	result.status_code = 0;
	return (result);
}
