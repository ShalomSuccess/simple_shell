#include <stdio.h>

/**
 * is_interactive - returns true if running in interactive mode
 * @fd: the file descriptor for stdin
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int is_interactive(int fd)
{
    return (isatty(fd));
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to check
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_delimiter(char c)
{
    char *delimiters = " \t\n";
    while (*delimiters != '\0') {
        if (*delimiters == c) {
            return 1;
        }
        delimiters++;
    }
    return 0;
}

/**
 * str_to_int - converts a string to an integer
 * @str: the string to convert
 *
 * Return: the converted integer, or 0 if the string does not contain a number
 */
int str_to_int(const char *str)
{
    int sign = 1, result = 0, i = 0;
    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
        result = result * 10 + (str[i] - '0');
    }
    return sign * result;
}

int main(void)
{
    printf("Is interactive: %d\n", is_interactive(STDIN_FILENO));
    printf("Is delimiter: %d\n", is_delimiter(' '));
    printf("String to integer: %d\n", str_to_int("-12345"));
    return 0;
}
