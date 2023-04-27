#include "shell.h"

/**
 * copy_info - copies the name given to create
 * a new env or alias
 * @name: name of env or alias
 * @value: value of env or alias
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure for environ
 * Return: void
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int i = 0;
	char *var_env, *name_env;

	while (datash->_environ[i] != NULL)
	{
		var_env = _strdup(datash->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
		i++;
	}

	datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = copy_info(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the given name.
 * @datash: data relevant to env name and env value
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->agc[1] == NULL || datash->agc[2] == NULL)
	{
		get_err(datash, -1);
		return (1);
	}

	set_env(datash->agc[1], datash->agc[2], datash);

	return (1);
}

/**
 * _unsetenv - deletes a set environment variable
 *
 * @datash: data relevant to env name
 *
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i = 0, j = 0, k = -1;

	if (datash->agc[1] == NULL)
	{
		get_err(datash, -1);
		return (1);
	}
	while (datash->_environ[i] != NULL)
	{
		var_env = _strdup(datash->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->agc[1]) == 0)
		{
			k = i;
		}
		free(var_env);
		i++;
	}
	if (k == -1)
	{
		get_err(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
