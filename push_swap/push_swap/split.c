#include "push_swap.h"

static int count_words(char *s, char c)
{
    int count;
    int in;

    count = 0;
    while (*s)
    {
        in = 0;
        while (*s == c)
            s++;
        while (*s && *s != c)
        {
            if (!in)
            {
                count++;
                in = 1;
            }
            s++;
        }
    }
    return (count);
}

static char *get_next_word(char *s, char c)
{
    static int  cur;
    char        *word;
    int         len;
    int         i;

    len = 0;
    i = 0;
    while (s[cur] == c)
        cur++;
    while (s[cur + len] && s[cur + len] != c)
        len++;
    word = malloc(len + 1);
    if (!word)
        return (NULL);
    while (s[cur] && s[cur] != c)
        word[i++] = s[cur++];
    word[i] = '\0';
    return (word);
}

char **split(char *s, char c)
{
    char    **res;
    int     wc;
    int     i;

    wc = count_words(s, c);
    if (wc == 0)
        exit(1);
    res = malloc(sizeof(char *) * (wc + 2));
    if (!res)
        return (NULL);
    i = 0;
    while (wc-- >= 0)
    {
        if (i == 0)
        {
            res[i] = malloc(1);
            if (!res[i])
                return (NULL);
            res[i++][0] = '\0';
            continue;
        }
        res[i++] = get_next_word(s, c);
    }
    res[i] = NULL;
    return (res);
}