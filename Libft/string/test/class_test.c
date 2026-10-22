/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:15:28 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:48:58 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../string.h"

void	psection(char *s)
{
	static int	n = 1;

	printf("\033[34m----------------------------\033[35m\n");
	printf("SECTION %d:\n", n);
	printf("%s\n", s);
	printf("\033[34m----------------------------\033[0m\n");
	++n;
}

void	ptest(char *s)
{
	static int	n = 1;

	printf("\033[33m----------------------------\033[32m\n");
	printf("TEST %d:\n", n);
	printf("%s\n", s);
	printf("\033[33m----------------------------\033[0m\n");
	++n;
}

int	test1()
{
	ptest("find substr ROCKY and deletes it");

	STR(s, "ROCKI ROCK ROOCKY CKY OCKY ROCK YROCKY ROCCKY AAA");
	STR(s2, "ROCKY");
	STR(s3, "");

	str_sdup(&s3, &s2);
	str_find(&s, &s2);
	// str_cut(&s, s.i, s.i + s2.len);
	str_trim(&s, s2.len);
	str_print(&s);
	return (0);
}

int	test2(void)
{
	ptest("Prints string begin, half, end. Overrides char from begin to half");

	STR(trim_s, "str ");
	STR(s1, "str Bosio");
	STR(s2, "str Rayquaza");
	char	*trim_c = "str ";

	str_find(&s1, &trim_s);
	str_cut(&s1, s1.i, trim_s.len);
	str_find(&s2, trim_c);
	str_cut(&s2, s2.i, ft_strlen(trim_c));
	str_print(&s1);
	return (0);
}

int	test3()
{
	ptest("Prints string begin, half, end. Overrides char from begin to half");

	STR(s, "MEGA_RAYQUAZA");
	t_str_iterator	it;

	it = str_get_iterator(&s);
	ft_printf("BEGIN[%s][%d]\n", it.begin, it.begin);
	ft_printf("HALF[%s][%d]\n", it.half, it.half);
	ft_printf("END[%s][%d]\n", it.end, it.end);

	for (;it.i < it.half; it.i++)
		*it.i = 'A';
	str_print(&s);
	return (0);
}

int	test4(char **av)
{
	ptest("Append argv to front and back of an empty string");

	STR(s, "");

	for (int i = 0; av[i]; i++)
	{
		for (int j = 0; av[i][j]; j++)
		{
			str_addr(&s, av[i][j]);
			str_addl(&s, av[i][j]);
		}
		str_addr(&s, '\n');
		str_addl(&s, '\n');
	}
	str_print(&s);
	return (0);
}

int	test5()
{
	ptest("Copy matrix until \\n");

	STR(s, NULL);
	char	matr[5][8] = {"ciao,\n", " come\n", " stai?\n", ""};

	for (int i = 0; matr[i][0]; i++)
	{
		str_excpy(&s, matr[i], "\n");
	}
	str_print(&s);
	return (0);
}

int	test6()
{
	ptest("Sort");

	STR(s, "38573847183471834701401840912841822110002321");

	str_sort(&s, NULL);
	str_print(&s);
	return (0);
}

int	test7()
{
	ptest("Reverse");

	STR(s, "Ale Alle Allllle   -><-");

	str_reverse(&s);
	str_print(&s);
	return (0);
}

int	test8()
{
	ptest("Heap and garbage collector");

	t_str	*s1;
	t_str	*s2;
	t_str	*s3;

	if (!STRING_GARBAGE_COLLECTOR)
		return (0);
	if (str_new(&s1, "s1") || str_new(&s2, "s2") || str_new(&s3, "s3"))
		return (str_terminate(), 1);
	str_delete(s1);
	str_delete(s2);
	str_delete(s3);
	str_terminate();
	return (0);
}

int	test_join(char *n1, char *n2)
{
	ptest("Join");

	STR(s, n1);
	str_join(&s, "    Sum of ", 4);
	str_push(&s, " with ");
	str_push(&s, n2);
	STR(s2, "//TERRA_DI_MEZZO");
	s.i = s.len / 2;
	str_join(&s, &s2, 0);
	str_find(&s, "");
	str_trim(&s, s2.len);
	str_print(&s);
	return (0);
}

int	test_sum(char *n1, char *n2)
{
	ptest("Sum of argv[1] with argv[2]");

	STR(s, n1);
	STR(s2, n2);
	STR(final, "the number is ");
	int	temp1;
	int	temp2;

	if (!n1 || !n2)
		return (1);
	if (str_satoi(&s, &temp1) != 0 || str_satoi(&s2, &temp2) != 0)
		return (1);
	temp1 = temp1 + temp2;
	final.i = final.len;
	str_itoa(&final, temp1);
	ft_printf("Result:\t%s\n", final.buff);
	return (0);
}

//FIXME - 
/*
*/
int	main(int ac, char **av)
{
	test1();
	test2();
	test3();
	test4(av);
	test5();
	test6();
	test7();
	test8();
	if (ac < 3)
		return (0);
	test_sum(av[1], av[2]);
	test_join(av[1], av[2]);
	return (0);
}
