#include "shell.h"

/**
 * cmp_env_name - compares the name of an environment
 * variable with the given name.
 * @nenv: name of the environment variable to compare
 * @name: name to compare with/against
 *
 * Return: 0 if are not equal. Another value if they are. Otherwise,
 * the number of characters in nenv including the equals sign.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the environment variable to get
 * @_environ: array environment variables to search
 *
 * Return: value of the environment variable if found. Otherwise, NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value to NULL and mov to 0 */
	ptr_env = NULL;
	mov = 0;

	/* Loops through _environ until we reach the end of the array */
	for (i = 0; _environ[i]; i++)
	{
	/* compare the name of the current environment variable with the given name */
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints all environment variables to standard output
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{

		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
