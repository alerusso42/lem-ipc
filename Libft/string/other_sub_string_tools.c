/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_sub_string_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:24:24 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/05 22:42:04 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
    RULES:

    1)  MAKE SURE YOUR DEST STRING IS BIG ENOUGH!
	2)	IF YOU WANT OTHER ASCII TYPE, YOU CAN:
		THIS FUNCTION GOES ON UNTIL IT FINDS A '\0'.
    3)  GIVE ONE OF THE FOLLOWING VALUES:

    -  	 ALPHA,	(53 bytes needed)
	-    UPPER_ALPHA, (27 bytes needed)
	-    LOWER_ALPHA, (27 bytes needed)
	-    DIGIT, (11 bytes needed)
	-    ALPHANUM (63 bytes needed)
*/
void	copy_stringset(char *dest, int charset_type)
{
	if (!dest)
		return ;
	while (*dest != 0)
		++dest;
	if (charset_type == ALPHA)
		ft_strlcpy(dest, "abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ", 53);
	else if (charset_type == LOWER_ALPHA)
		ft_strlcpy(dest, "abcdefghijklmnopqrstuvwxyz", 27);
	else if (charset_type == UPPER_ALPHA)
		ft_strlcpy(dest, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 27);
	else if (charset_type == DIGIT)
		ft_strlcpy(dest, "0123456789", 11);
	else if (charset_type == ALPHANUM)
		ft_strlcpy(dest, "abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ\
0123456789", 63);
}

/*
    RULES:

    1)  MAKE SURE YOUR DEST STRING IS BIG ENOUGH!
	2)	IF YOU WANT OTHER ASCII TYPE, YOU CAN:
		THIS FUNCTION GOES ON UNTIL IT FINDS A '\0'.
    3)  This function will copy charset in dest,
		starting from the first '\0' it finds.
*/
void	copy_customset(char *dest, char *charset)
{
	if ((!dest) || (!charset))
		return ;
	while (*dest != 0)
		++dest;
	ft_strlcpy(dest, charset, ft_strlen(charset) + 1);
}

/*
	Count until the char is in the charset.
	TWO MODES:

	INCLUDE: Count until the char is in the charset.
	EXCLUDE: Count until the char is NOT in the charset.
*/
int	sub_strlen(const char *s, const char *charset, int mode)
{
	int	i;

	if (!s || !charset)
		return (0);
	i = 0;
	if (mode == INCLUDE)
	{
		while (((s[i] != '\0')) && \
		(ft_strchr(charset, s[i])))
		{
			++i;
		}
	}
	else if (mode == EXCLUDE)
	{
		while (((s[i] != '\0')) && \
		!(ft_strchr(charset, s[i])))
		{
			++i;
		}
	}
	return (i);
}

/*
	Copy until the char is in the charset.
	TWO MODES:

	INCLUDE: Copy until the char is in the charset.
	EXCLUDE: Copy until the char is NOT in the charset.
*/
int	sub_strcpy(char *dest, const char *src, const char *charset, int mode)
{
	int	i;

	if (!dest || !src || !charset)
		return (0);
	i = 0;
	if (mode == INCLUDE)
	{
		while (((src[i] != '\0')) && \
		(ft_strchr(charset, src[i])))
		{
			dest[i] = src[i];
			++i;
		}
	}
	else if (mode == EXCLUDE)
	{
		while (((src[i] != '\0')) && \
		!(ft_strchr(charset, src[i])))
		{
			dest[i] = src[i];
			++i;
		}
	}
	dest[i] = 0;
	return (i);
}

/*
int	main()
{
	char	charset[70];
	char	charset1[70];
	char	test[70] = "Ciao42 _42";
	char	test1[70] = "Stringa con spazi e 42";
	char	test2[70];

	//	Test 1: lunghezza con solo caratteri alfabetici
	copy_stringset(charset, ALPHA);
	printf("\nLen Ciao42: %d\n", sub_strlen(test, charset, INCLUDE));
	printf("\nLen Ciao42: %d\n", sub_strlen(test, "0123456789", EXCLUDE));
	//	Test 2: lunghezza con caratteri alfanumerici
	copy_stringset(charset, DIGIT);
	printf("\nLen Ciao42: %d\n", sub_strlen(test, charset, INCLUDE));
	printf("\nLen Ciao42: %d\n", sub_strlen(test, " ", EXCLUDE));
	//	Test 3: copia generica fino a numeri
	copy_customset(charset1, "0123456789");
	sub_strcpy(test2, test1, charset1, EXCLUDE);
	printf("\n%s\n", test2);
	printf("END\n");
}*/
