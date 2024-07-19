
#include "../cub.h"

int	ft_strlcpy(char	*dst, char *src, int dstsize)
{
	int	i;
	int	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

static int	check_set(char s, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*r;
	int		len;

	if (!s1 || !set)
		return (NULL);
	while (s1)
	{
		if (check_set(*s1, set) == 1)
			s1++;
		else
			break ;
	}
	len = ft_strlen(s1);
	while (len)
	{
		if (check_set(s1[len - 1], set) == 1)
			len--;
		else
			break ;
	}
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (0);
	ft_strlcpy(r, s1, len + 1);
	return (r);
}

void	*ft_calloc(int num, int size)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(num * size);
	if (!res)
		return (NULL);
	while (i < (num * size))
	{
		res[i] = 0;
		i++;
	}
	return ((void *)res);
}