#include "include/pipex.h"

int	test (int len, char **args)
{
	printf("%d\n", len);
	printf("%s\n", args[0]);
	return (0);
}