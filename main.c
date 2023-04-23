#include "shell.h"

/**
 * free_data - frees the data structure
 * @datash: data structure
 * Return: no return
 */
void free_data(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Initialize data structure
 * @datash: data structure
 * @agv: argument vector
 * Return: no return
 */
void set_data(data_shell *datash, char **agv)
{
	unsigned int i;

	datash->agv = agv;
	datash->input = NULL;
	datash->agc = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	datash->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _strdup(environ[i]);
	}

	datash->_environ[i] = NULL;
	datash->pid = _itoa(getpid());
}

/**
 * main - Entry point
 * @agc: argument count
 * @agv: argument vector
 * Return: 0 on success.
 */
int main(int agc, char **agv)
{
	data_shell datash;
	(void) agc;

	signal(SIGINT, get_sigint);
	set_data(&datash, agv);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
