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
	int i = 0;

	while (nenv[i] != '=')
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
		i++;
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
	int i = 0, j;

	ptr_env = NULL;
	j = 0;

	while (_environ[i])
	{
		j = cmp_env_name(_environ[i], name);
		if (j)
		{
			ptr_env = _environ[i];
			break;
		}
		i++;
	}

	return (ptr_env + j);
}

/**
 * _env - prints all environment variables to standard output
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int i = 0, j;

	while (datash->_environ[i])
	{
		j = 0;
		while (datash->_environ[i][j])
		{
			j++;
		}
		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	datash->status = 0;

	return (1);
}
