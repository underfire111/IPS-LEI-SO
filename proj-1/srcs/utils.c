#include <stdlib.h>

#include "string.h"

char *	ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	str = NULL;
	if (start >= strlen(s))
	{
		start = 0;
		len = 0;
	}
	if (s && (strlen(s) - 1) >= start)
	{
		if (strlen(s) - start < len)
			len = strlen(s) - start;
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (!str)
			return (0);
		i = -1;
		while (++i < len)
			str[i] = s[start + i];
		str[i] = '\0';
	}
	return (str);
}


static int	ft_countwords(char *s, char c)
{
	int	n_words;
	int	is_word;

	n_words = 0;
	is_word = 0;
	while (*s)
	{
		if (is_word == 0 && *s != c)
		{
			is_word = 1;
			n_words++;
		}
		else if (is_word == 1 && *s == c)
			is_word = 0;
		s++;
	}
	return (n_words);
}

static int	ft_lenght(char *s, char c)
{
	int	lenght;

	lenght = 0;
	while (*s != c && *s != '\0')
	{
		lenght++;
		s++;
	}
	return (lenght);
}

char **	ft_split(char const *s, char c)
{
	char	**ptr;
	int		n_words;
	int		i;

	if (!s)
		return (0);
	n_words = ft_countwords((char *)s, c);
	ptr = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (n_words--)
	{
		while (*s == c && *s)
			s++;
		ptr[i] = ft_substr((char *)s, 0, ft_lenght((char *)s, c));
		if (!ptr[i])
			return (0);
		s += ft_lenght((char *)s, c);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
