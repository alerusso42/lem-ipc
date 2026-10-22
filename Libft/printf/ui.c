/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:38:26 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/02 13:55:49 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	_ft_printf(int fd, const char *str, t_str *buff, va_list *ptr);

int	fd_printf(int fd, const char *str, ...)
{
	int		n;
	va_list	p;

	va_start(p, str);
	n = _ft_printf(fd, str, NULL, &p);
	va_end(p);
	return (n);
}

int	tfd_printf(t_fd fd, const char *str, ...)
{
	int		n;
	va_list	p;

	va_start(p, str);
	n = _ft_printf(fd.p, str, NULL, &p);
	va_end(p);
	return (n);
}

int	err_printf(const char *str, ...)
{
	int		n;
	va_list	p;
	
	va_start(p, str);
	n = _ft_printf(2, str, NULL, &p);
	va_end(p);
	return (n);
}

int	str_printf(t_str *buff, const char *str, ...)
{
	int		n;
	va_list	p;

	va_start(p, str);
	n = _ft_printf(-1, str, buff, &p);
	va_end(p);
	return (n);
}

/*
Interpreta:
	-	% = specificatori di formato
	-	$ = ansi code
	-	? = funzioni
//ANCHOR -  % = specificatori di formato
%c = char
%d = long long signed int
%u = long long unsigned int
%p = puntatori

//ANCHOR -  $ = ansi code
esempio: "$R ciao!"	->	setta come colore font red, scrive ciao
esempio: "$\\5"		->	scende 5 colonne in basso
esempio: "$#2"		->	pulisce lo schermo
cmd||effect								|ansi code
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//SECTION NO ARGS						
0	|Home (cursore in alto a sinistra)	|	\033[H
1	|save_position						|	\033[s
2	|restore_position					|	\033[u
//SECTION ARGS
!	|clear (pulisce schermo)			|	\033[0J | OPPURE 1J 2J 3J
|#|	|clearLine (pulisce linea corrente)	|	\033[0K | OPPURE 1K 2K
/	|Up									|	\033[A
\\	|Down								|	\033[B
>	|right								|	\033[C
<	|left								|	\033[D
//SECTION m separator
lowercase: printa il background
A	|grAy (grigio)						|	\033[90m
B	|Bold								|	\033[1m
C	|Cyan (ciano)						|	\033[36m
D	|Dim (sbiadito)						|	\033[2m
E										|	
F	|Flash								|	\033[5m
G	|Green (verde)						|	\033[32m
H										|
I	|Italic (corsivo)					|	\033[3m
J										|	
K										|	
L	|bLu								|	\033[34m
M	|Magenta							|	\033[35m
N	|black (Nero)						|	\033[30m
O										|	
P	|Pink (magenta chiaro)				|	\033[95m
Q										|	
R	|Red (rosso)						|	\033[31m
S										|	
T	|strikeThrough (barrato)			|	\033[9m
U	|Urderline (sottolineato)			|	\033[4m
V	|reverse							|	\033[7m
W	|white (bianco)						|	\033[37m
X	|hidden (testo invisibile)			|	\033[8m
Y	|yellow (giallo)					|	\033[33m
Z	|reset								|	\033[0m

//ANCHOR -  ? = Function

-	Può ricevere puntatori a funzioni ed eseguirle
-	Può prendere da 0 a massimo 3 argomenti
-	Gli argomenti possono essere puntatori (%p) o variabili senza puntatore (%d)
-	Le variabili senza puntatore non devono avere size > 8 bytes

Sintassi: 	
			ft_printf("?%p?", function)
			ft_printf("?%p-%d-%p", function, 42, "ciao!")
			ft_printf("?%p-42-ciao!", function")
Esempio: ft_printf("aspetto %d secondi... ?%p-%d?fine attesa!\n", time, sleep, time);
Esempio: ft_printf("?%p-%d-%p?", main, ac, av);
*/
int	ft_printf(const char *str, ...)
{
	int		n;
	va_list	p;

	va_start(p, str);
	n = _ft_printf(1, str, NULL, &p);
	va_end(p);
	return (n);
}
