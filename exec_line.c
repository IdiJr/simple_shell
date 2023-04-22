#include "shell.h"

/**
 * exec_line - checks if the command is builtin and calls
 * function to execute
 *
 * @datash: data relevant to command arguments
 * Return: 1 on success.
 */
int exec_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->agc[0] == NULL)
		return (1);

	builtin = get_builtIn(datash->agc[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}
