#include "shell.h"

/**
 * cd_shell - changes to current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int cd_shell(data_shell *datash)
{
	char *dir;
	int isshome, isshome2, issddash;

	dir = datash->agc[1];

	if (dir != NULL)
	{
		isshome = _strcmp("$HOME", dir);
		isshome2 = _strcmp("~", dir);
		issddash = _strcmp("--", dir);
	}

	if (dir == NULL || !isshome || !isshome2 || !issddash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
