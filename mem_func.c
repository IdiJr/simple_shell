#include "shell.h"

/**
 * _memcpy - copies info between the void pointers.
 * @newptr: destination pointer variable.
 * @ptr: source pointer variable.
 * @size: size of the new pointer.
 * Return: no return.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int id;

	for (id = 0; id < size; id++)
		char_newptr[id] = char_ptr[id];
}

/**
 * _realloc - re-allocates a memory block.
 * @ptr: pointer to the memory previously allocated block.
 * @old_size: size in bytes of the allocated space of ptr.
 * @new_size: new size in bytes of the new memory block.
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp - re-allocates a memory block of  double pointers.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size in bytes of the allocated space of ptr.
 * @new_size: new size in bytes of the new memory block.
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int id;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (id = 0; id < old_size; id++)
		newptr[id] = ptr[id];

	free(ptr);

	return (newptr);
}
