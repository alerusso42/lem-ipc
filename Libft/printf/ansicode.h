/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ansicode.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:58:50 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/05 23:40:39 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANSICODE_H
# define ANSICODE_H

# include <stdint.h>
enum e_ansi_flags
{
	ANSI_ARGS = 		(1 << 0),
	ANSI_M_SEPARATOR = 	(1 << 1),
};

/*
cmd||effect								|ansi code
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//SECTION NO ARGS						
0	|Home (cursore in alto a sinistra)	|	\033[H
1	|save_position						|	\033[s
2	|restore_position					|	\033[u
//SECTION ARGS
!	|clear (pulisce schermo)			|	\033[0J | OPPURE 1J 2J 3J
?	|sleep								|	-
#	|clearLine (pulisce linea corrente)	|	\033[0K | OPPURE 1K 2K
/	|Up									|	\033[A
\	|Down								|	\033[B
>	|right								|	\033[C
<	|left								|	\033[D
//SECTION m separator
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
*/
enum e_ansi_codes
{
	CLEAR_SCREEN = 'J',
	CLEAR_LINE = 'K',
	CMD_SLEEP = '?',
	MV_UP = 'A',
	MV_DOWN = 'B',
	MV_RIGHT = 'C',
	MV_LEFT = 'D',
	MV_HOME = 'H',
	MV_SAVE = 's',
	MV_RESTORE = 'u',
	S_RESET = '0',//style codes must be set to ascii digit to work
	S_BOLD = '1',
	S_DIM = '2',
	S_ITALIC = '3',
	S_UNDERLINE = '4',
	S_FLASH = '5',
	S_REVERSE = '7',
	S_HIDDEN = '8',
	S_STRIKE = '9',
	C_BLACK = 30,
	B_BLACK = 40,
	C_RED = 31,
	B_RED = 41,
	C_GREEN = 32,
	B_GREEN = 42,
	C_YELLOW = 33,
	B_YELLOW = 43,
	C_BLUE = 34,
	B_BLUE = 44,
	C_MAGENTA = 35,
	B_MAGENTA = 45,
	C_CYAN = 36,
	B_CYAN = 46,
	C_WHITE = 37,
	B_WHITE = 47,
	C_GRAY = 90,
	B_GRAY = 100,
	C_PINK = 95,
	B_PINK = 105,
};

# define 	FT_PRINTF_ANSI_TABLE \
(const uint8_t['~' - ' ']){ \
	[' ' - 32] = 255, \
	['!' - 32] = (uint8_t)CLEAR_SCREEN, \
	['"' - 32] = 255, \
	['#' - 32] = (uint8_t)CLEAR_LINE, \
	['$' - 32] = 255, \
	['%' - 32] = 255, \
	['&' - 32] = 255, \
	['\'' - 32] = 255, \
	['(' - 32] = 255, \
	[')' - 32] = 255, \
	['*' - 32] = 255, \
	['+' - 32] = 255, \
	[',' - 32] = 255, \
	['-' - 32] = 255, \
	['.' - 32] = 255, \
	['/' - 32] = (uint8_t)MV_UP, \
	['0' - 32] = (uint8_t)MV_HOME, \
	['1' - 32] = (uint8_t)MV_SAVE, \
	['2' - 32] = (uint8_t)MV_RESTORE, \
	['3' - 32] = 255, \
	['4' - 32] = 255, \
	['5' - 32] = 255, \
	['6' - 32] = 255, \
	['7' - 32] = 255, \
	['8' - 32] = 255, \
	['9' - 32] = 255, \
	[':' - 32] = 255, \
	[';' - 32] = 255, \
	['<' - 32] = (uint8_t)MV_LEFT, \
	['=' - 32] = 255, \
	['>' - 32] = (uint8_t)MV_RIGHT, \
	['?' - 32] = (uint8_t)CMD_SLEEP, \
	['@' - 32] = 255, \
	['A' - 32] = (uint8_t)C_GRAY, \
	['a' - 32] = (uint8_t)B_GRAY, \
	['B' - 32] = (uint8_t)S_BOLD, \
	['b' - 32] = (uint8_t)S_BOLD, \
	['C' - 32] = (uint8_t)C_CYAN, \
	['c' - 32] = (uint8_t)B_CYAN, \
	['D' - 32] = (uint8_t)S_DIM, \
	['d' - 32] = (uint8_t)S_DIM, \
	['E' - 32] = 255, \
	['e' - 32] = 255, \
	['F' - 32] = (uint8_t)S_FLASH, \
	['f' - 32] = (uint8_t)S_FLASH, \
	['G' - 32] = (uint8_t)C_GREEN, \
	['g' - 32] = (uint8_t)B_GREEN, \
	['H' - 32] = 255, \
	['h' - 32] = 255, \
	['I' - 32] = (uint8_t)S_ITALIC, \
	['i' - 32] = (uint8_t)S_ITALIC, \
	['J' - 32] = 255, \
	['j' - 32] = 255, \
	['K' - 32] = 255, \
	['k' - 32] = 255, \
	['L' - 32] = (uint8_t)C_BLUE, \
	['l' - 32] = (uint8_t)B_BLUE, \
	['M' - 32] = (uint8_t)C_MAGENTA, \
	['m' - 32] = (uint8_t)B_MAGENTA, \
	['N' - 32] = (uint8_t)C_BLACK, \
	['n' - 32] = (uint8_t)B_BLACK, \
	['O' - 32] = 255, \
	['o' - 32] = 255, \
	['P' - 32] = (uint8_t)C_PINK, \
	['p' - 32] = (uint8_t)B_PINK, \
	['Q' - 32] = 255, \
	['q' - 32] = 255, \
	['R' - 32] = (uint8_t)C_RED, \
	['r' - 32] = (uint8_t)B_RED, \
	['S' - 32] = 255, \
	['s' - 32] = 255, \
	['T' - 32] = (uint8_t)S_STRIKE, \
	['t' - 32] = (uint8_t)S_STRIKE, \
	['U' - 32] = (uint8_t)S_UNDERLINE, \
	['u' - 32] = (uint8_t)S_UNDERLINE, \
	['V' - 32] = (uint8_t)S_REVERSE, \
	['v' - 32] = (uint8_t)S_REVERSE, \
	['W' - 32] = (uint8_t)C_WHITE, \
	['w' - 32] = (uint8_t)B_WHITE, \
	['X' - 32] = (uint8_t)S_HIDDEN, \
	['x' - 32] = (uint8_t)S_HIDDEN, \
	['Y' - 32] = (uint8_t)C_YELLOW, \
	['y' - 32] = (uint8_t)B_YELLOW, \
	['Z' - 32] = (uint8_t)S_RESET, \
	['z' - 32] = (uint8_t)S_RESET, \
	['[' - 32] = 255, \
	['\\' - 32] = (uint8_t)MV_DOWN, \
	[93 - 32] = 255, \
	['^' - 32] = 255, \
	['_' - 32] = 255, \
	['`' - 32] = 255, \
	['{' - 32] = 255, \
	['|' - 32] = 255, \
	['}' - 32] = 255, \
}
			

#endif