#include "shell.h"

/**
 * is_cdir - checks if the current directory is in the PATH
 * @path: the PATH environment variable
 * @i: pointer to the current index in the PATH string
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - locates a command system PATH directory
 *
 * @cmd: command name
 * @_environ: array of environment variables
 * Return: location of the command if found else, NULL
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *path_ptr, *token_path, *dir;
	int dir_len, cmd_len, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		path_ptr = _strdup(path);
		cmd_len = _strlen(cmd);
		token_path = _strtok(path_ptr, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			dir_len = _strlen(token_path);
			dir = malloc(dir_len + cmd_len + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(path_ptr);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(path_ptr);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if is an executable
 *
 * @datash: data structure containing the shell's inputs
 * Return: 0 if not an executable, a positive integer if it is.
 * -1 on error
 */
int is_executable(data_shell *datash)
{
	struct stat st;
	int index;
	char *input;

	input = datash->agc[0];
	for (index = 0; input[index]; index++)
	{
		if (input[index] == '.')
		{
			if (input[index + 1] == '.')
				return (0);
			if (input[index + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[index] == '/' && index != 0)
		{
			if (input[index + 1] == '.')
				continue;
			index++;
			break;
		}
		else
			break;
	}
	if (index == 0)
		return (0);

	if (stat(input + index, &st) == 0)
	{
		return (index);
	}
	get_err(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if user has permissions to access
 *
 * @dir: The directory path to be checked.
 * @datash: data dtructure containing shell inpts
 * Return: 0 on success, 1 if an error is encountered
 */
int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_err(datash, 127);
		return (1);
	}

	if (_strcmp(datash->agc[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_err(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->agc[0], X_OK) == -1)
		{
			get_err(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * exec_cmd - executes command lines
 *
 * @datash: relevant agc and input data
 * Return: 1 on success.
 */
int exec_cmd(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_executable(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(datash->agc[0], datash->_environ);
		if (check_error_cmd(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(datash->agc[0], datash->_environ);
		else
			dir = datash->agc[0];
		execve(dir + exec, datash->agc, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->agv[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
