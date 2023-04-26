#include "shell.h"

/**
 * get_helper - calls help messages from builtin
 * @datash: data structure for agc and input
 * Return: 0 on success
*/
int get_helper(data_shell *datash)
{

	if (datash->agc[1] == 0)
		help_general();
	else if (_strcmp(datash->agc[1], "setenv") == 0)
		help_setenv();
	else if (_strcmp(datash->agc[1], "env") == 0)
		help_env();
	else if (_strcmp(datash->agc[1], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(datash->agc[1], "help") == 0)
		_help();
	else if (_strcmp(datash->agc[1], "exit") == 0)
		help_exit();
	else if (_strcmp(datash->agc[1], "cd") == 0)
		help_cd();
	else if (_strcmp(datash->agc[1], "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, datash->agc[0],
		      _strlen(datash->agc[0]));

	datash->status = 0;
	return (1);
}
