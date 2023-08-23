#include "shell.h"

/**
 * convert_long_to_string - converts a long number to a string.
 * @num: long number to be converted to string.
 * @str: buffer to save the number as a string.
 * @base: base to convert the number.
 */
void convert_long_to_string(long num, char *str, int base)
{
	int index = 0, isNegative = 0;
	long quotient = num;
	char digit_chars[] = "0123456789abcdef";

	if (quotient == 0)
		str[index++] = '0';

	if (str[0] == '-')
		isNegative = 1;

	while (quotient)
	{
		if (quotient < 0)
			str[index++] = digit_chars[-(quotient % base)];
		else
			str[index++] = digit_chars[quotient % base];
		quotient /= base;
	}
	if (isNegative)
		str[index++] = '-';

	str[index] = '\0';
	reverse_string(str);
}

/**
 * custom_atoi - convert a string to an integer.
 *
 * @s: pointer to the input string.
 * Return: integer representation of the string or 0.
 */
int custom_atoi(char *s)
{
	int sign = 1;
	unsigned int num = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{
		num = (num * 10) + (*s - '0');
		s++;
	}
	return (num * sign);
}

/**
 * count_chars - count the occurrences of a character in a string.
 *
 * @string: pointer to the input string.
 * @character: character to be counted.
 * Return: number of occurrences.
 */
int count_chars(char *string, char character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character)
			counter++;
	}
	return (counter);
}
