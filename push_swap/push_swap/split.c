#include "../push_swap.h"

static int	count_words(char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_next_word(char *s, char c)
{
	static int	cursor;
	char		*word;
	int			len;
	int			i;

	len = 0;
	while (s[cursor] == c)
		cursor++;
	while (s[cursor + len] != c && s[cursor + len])
		len++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (s[cursor] != c && s[cursor])
		word[i++] = s[cursor++];
	word[i] = '\0';
	return (word);
}

char	**split(char *s, char c)
{
	char	**result;
	int		words;
	int		i;

	words = count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < words)
	{
		result[i] = get_next_word(s, c);
		if (!result[i])
			return (NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}