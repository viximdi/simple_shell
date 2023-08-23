#include "shell.h"

/**
 * get_custom_strlen - returns the length of a custom string.
 * @str: pointer to custom string.
 * Return: length of custom string.
 */
int get_custom_strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);

	while (str[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * duplicate_custom_str - duplicates a custom string
 * @str: Custom string to be copied
 * Return: pointer to the array
 */
char *duplicate_custom_str(char *str)
{
	char *result;
	int len, i;

	if (str == NULL)
		return (NULL);

	len = get_custom_strlen(str) + 1;

	result = malloc(sizeof(char) * len);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len ; i++)
	{
		result[i] = str[i];
	}

	return (result);
}

/**
 * compare_custom_str - Compare two custom strings
 * @str1: Custom string one, or the shorter
 * @str2: Custom string two, or the longer
 * @num: number of characters to be compared, 0 if infinite
 * Return: 1 if the custom strings are equal, 0 if they are different
 */
int compare_custom_str(char *str1, char *str2, int num)
{
	int iter;

	if (str1 == NULL && str2 == NULL)
		return (1);

	if (str1 == NULL || str2 == NULL)
		return (0);

	if (num == 0) /* Infinite length */
	{
		if (get_custom_strlen(str1) != get_custom_strlen(str2))
			return (0);
		for (iter = 0; str1[iter]; iter++)
		{
			if (str1[iter] != str2[iter])
				return (0);
		}
		return (1);
	}
	else /* If there is a number of chars to be compared */
	{
		for (iter = 0; iter < num ; iter++)
		{
			if (str1[iter] != str2[iter])
				return (0);
		}
		return (1);
	}
}

/**
 * concat_custom_str - concatenates two custom strings.
 * @str1: Custom string to be concatenated
 * @str2: Custom string to be concatenated
 * Return: pointer to the array
 */
char *concat_custom_str(char *str1, char *str2)
{
	char *result;
	int len1 = 0, len2 = 0;

	if (str1 == NULL)
		str1 = "";
	len1 = get_custom_strlen(str1);

	if (str2 == NULL)
		str2 = "";
	len2 = get_custom_strlen(str2);

	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* Copy of str1 */
	for (len1 = 0; str1[len1] != '\0'; len1++)
		result[len1] = str1[len1];
	free(str1);

	/* Copy of str2 */
	for (len2 = 0; str2[len2] != '\0'; len2++)
	{
		result[len1] = str2[len2];
		len1++;
	}

	result[len1] = '\0';
	return (result);
}

/**
 * reverse_custom_str - reverses a custom string.
 * @str: pointer to custom string.
 * Return: void.
 */
void reverse_custom_str(char *str)
{
	int i = 0, length = get_custom_strlen(str) - 1;
	char hold;

	while (i < length)
	{
		hold = str[i];
		str[i++] = str[length];
		str[length--] = hold;
	}
}
