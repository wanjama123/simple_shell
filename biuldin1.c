#include "shell.h"

/**
 * _myhistory - starting at 0.
 * @info: containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 otherwise 1
 */
int unset_alias(info_t *info, char *str)
{
	char *j, c;
	int ret;

	j = _strchr(str, '=');
	if (!j)
		return (1);
	c = *j;
	*j = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*j = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 otherwise 1
 */
int set_alias(info_t *info, char *str)
{
	char *j;

	j = _strchr(str, '=');
	if (!j)
		return (1);
	if (!*++j)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *j = NULL, *a = NULL;

	if (node)
	{
		j = _strchr(node->str, '=');
		for (a = node->str; a <= j; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(j + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *j = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		j = _strchr(info->argv[i], '=');
		if (j)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
