#include "shell.h"

/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * @i: index of repeated char
 * Return: repetitions
 */
int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - checks for syntax errors
 *
 * @input: input string
 * @i: index of error
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_sep_op(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - checks index of the first char
 *
 * @input: input string
 * @i: index of first char
 * Return: 0 on success; 1 on failure
 */
int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - prints a message when syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @i: index of the error
 * @bool: controls error messages
 * Return: void
 */
void print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = _itoa(datash->counter);
	length = _strlen(datash->agv[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->agv[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - checks for syntax error and prints it.
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 on success; 1 on failure
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int start = 0;
	int f_char = 0;
	int index = 0;

	f_char = first_char(input, &start);
	if (f_char == -1)
	{
		print_syntax_error(datash, input, start, 0);
		return (1);
	}

	index = error_sep_op(input + start, 0, *(input + start));
	if (index != 0)
	{
		print_syntax_error(datash, input, start + index, 1);
		return (1);
	}

	return (0);
}
