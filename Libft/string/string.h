/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:24:29 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:30:01 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H
# include <stdbool.h>
# include <unistd.h>
# include <malloc.h>
# include <limits.h>
# include <stdint.h>
# include "../libft.h"
# include "string_private.h"

//enables/disables garbage collector
# define STRING_GARBAGE_COLLECTOR false
# define STRING_NPOS INT32_MAX

typedef struct s_str			t_str;
typedef struct s_str_iterator	t_str_iterator;
typedef enum e_str_error		t_str_error;
typedef int32_t					err;
typedef struct s_list			t_list;

enum	e_str_error
{
	E_EXIT_SUCCESS = EXIT_SUCCESS,
	E_ALLOC,
	E_PARAM,
	E_NPOS,
	E_ATOI_FAIL,
};

struct s_str
{
//private:
	void			*_garbage_coll_node;
//public:
	char			*buff;
	int32_t			len;
	int32_t			capacity;
	int32_t			i;
	t_str_error		err;
};

struct s_str_iterator
{
	char	*begin;
	char	*half;
	char	*end;
	char	*i;
};

//SECTION - constructor

t_str	_str_constructor(t_str *str, const char *init);
//	the function given to cleanup is called when the variable exits from its
//	scope
# define clean(base) __attribute__((cleanup(_ ## base ## _destructor)))
# define clean_ptr(base) __attribute__((cleanup(_ ## base ## _ptr_destructor)))

/*### CONSTRUCTOR CALL	
	#### OPTION 1: stack
	```c
	STR(variable_name, "initial buffer")
	STR(other_variable, NULL)
	```
	#### OPTION 2: heap
	```c
	t_str	*s;
	str_new(&s, "initial buffer");
	```
	in the first case, the object t_str is allocated on the stack (t_str);
	in the second case, is allocated on the heap (t_str *).

	first should be used as: 	string.print(&string);
	second should be used as: 	string->print(string);
*/
# define STR(name, init) t_str clean(str) name = _str_constructor(&name, init)

//SECTION - functions available

bool			str_new(t_str **str, const char *buff);
t_str			*str_delete(t_str *this);
void			str_terminate(void);
t_str			*str_print(t_str *this);
t_str_iterator	str_get_iterator(t_str *this);

/**### str_addl
 * @brief Appends a character to the start of the string.
 * @attention	IGNORES SET INDEX DURING OPERATION!
 * @param {t_str*}	pointer to string object
 * @param {char} the char to append
 * @return {t_str*} this object
 * ```c
 * STR(s1, "ello");
 * 
 * str_addl(&s1, 'h');
 * str_print(&s1);// => "hello"
 * ```
 */
t_str	*str_addl(t_str *this, char c);

/**### str_addr
 * @brief Appends a character to the end of the string.
 * @attention	IGNORES SET INDEX DURING OPERATION!
 * @param {t_str*} pointer to string object
 * @param {char} the char to append
 * @return {t_str*} this object
 * ```c
 * STR(s1, "hell");
 * 
 * str_addr(&s1, 'o');
 * str_print(&s1);// => "hello"
 * ```
 */
t_str	*str_addr(t_str *this, char c);

/**### str_app
 * @brief Appends the content of another string object or a char pointer
	to the current string object.
 * @attention	IGNORES SET INDEX DURING OPERATION!
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*} pointer to another string object/char ptr
 * @return {t_str*} this object
 * ```c
 * STR(s1, "hello, ");
 * STR(s2, "how are you?");
 * char	s3[] = "\nI am fine!\n";
 * 
 * str_app(&s1, &s2);
 * str_app(&s1, s3);
 * str_print(&s1);// => "hello, how are you?\nI am fine!\n"
 * ```
 */
# define str_app(s, s2) \
	STR_OVERLOAD1(str_app, s2)(s, s2)

/**### str_cmp
 * @brief Compares the string object's buffer
	with another string object or a char pointer.
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*} pointer to another string object/char ptr
 * @return {int32_t} result of comparison
 * ```c
 * if (str_cmp(str, other) == 0)
 * 	ft_printf("equal strings");
 * else
 * 	ft_printf("different strings");
 * ```
 */
# define str_cmp(this, other) \
	STR_OVERLOAD1(str_cmp, other)(this, other)

/**### str_count
 * @brief Count how many times c is in buffer.
 * @param {t_str*}	pointer to string object
 * @param {char} ascii character
 * @return {t_str*} this object
 * ```c
 * STR(s1, "Hello, world!\n");
 * 
 * str_count(&s1, 'l');// returns 3
 * ```
 */
int	str_count(t_str *this, char c);

/**### str_cpy
 * @brief Copies the content of another string object or a char pointer
	into the current string object.
 * @attention	IGNORES SET INDEX DURING OPERATION!
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*} pointer to another string object/char ptr
 * @return {t_str*} this object
 * ```c
 * STR(s1, NULL);
 * char	s2[] = "Hello, world!n";
 * 
 * str_cpy(&s1, s2);
 * str_print(&s1);// => "hello, world!\n"
 * ```
 */
# define str_cpy(this, other) \
	STR_OVERLOAD1(str_cpy, other)(this, other)

/**### str_cut
 * @brief Cut a string object from start to end (included).
 * @attention	IGNORES SET INDEX DURING OPERATION!
 * @param {t_str*}	pointer to string object
 * @param {int32_t} start index
 * @param {int32_t} end index
 * @return {t_str*} this object
 * ```c
 * STR(s1, "hello, world!\n");
 * 
 * str_cut(&s1, 0, 1);// => "llo, world!\n"
 * str_cut(&s1, 0, 0);// => "lo, world!\n"
 * str_cut(&s1, 3, 4);// => "lloworld!\n"
 * str_cut(&s1, 3, INT_MAX);// => "llo"
 * ```
 */
t_str	*str_cut(t_str *this, int32_t start, int32_t end);

/**### str_diff
 * @brief Advances the index of the string object while the current character
 *	does not belong to the given string or char pointer.
 * @attention	USES SET INDEX DURING OPERATION!
 * @attention	MODIFY INDEX!
 * @param {t_str*} this
 * @param {t_str*|char*|char} other
 * @return {t_str*} this
 * ```c
 * STR(s1, "hello, world!\n");
 * STR(s2, "hello");
 * STR(s3, "image.png");
 * 
 * str_diff(&s1, 'h');// i = 1 ('e')
 * str_diff(&s1, &s2);// i = 5 (',')
 * str_diff(&s3, ".png");// i = 0 ('i')
 * ```
 */
# define str_diff(this, other) \
	STR_OVERLOAD1_CHR(str_diff, other)(this, other)

/**### str_excpy
 * @brief Copies characters from other
	into this, while characters are EXCLUDED to the given set.
 * @attention	USES SET INDEX DURING OPERATION!
 * @attention	SET INDEX TO END OF COPIED CONTENT!
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*} other
 * @param {t_str*|char*} set
 * @return {t_str*} this object
 * ```c
 * STR(s1, "First line: ");
 * STR(s2, "Hello\nworld!\n");
 * 
 * s1.i = s1.len;
 * str_incpy(&s1, &s2, "\n");
 * str_print(&s1);// =>	"First line: Hello"
 * ```
 */
# define str_excpy(this, other, set) \
	STR_OVERLOAD2(str_excpy, other, set)(this, other, set)

/**### str_find
 * @brief Finds the first occurrence of another string object or a char pointer
	in the current string object.
 * @attention	IGNORES SET INDEX DURING OPERATION!
 * @attention	MODIFY INDEX!
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*|char} other
 * @return {t_str*} this object
 * ```c
 * STR(s1, "hello, world!\n");
 * STR(s2, "world!\n");
 * 
 * str_find(&s1, 'o');// i = 4
 * str_find(&s1, &s2);// i = 7
 * str_find(&s1, "d!\n other data");// i = STRING_NPOS
 * ```
 */
# define str_find(this, other) \
	STR_OVERLOAD1_CHR(str_find, other)(this, other)

/**### str_first
 * @brief Advances the index of the string object until one of the characters 
	from another string object or a char pointer is found.
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*|char} other
 * @return {t_str*} this object
 * ```c
 * STR(s1, "hello, world!\n");
 * STR(s2, "wrl");
 * 
 * str_first(&s1, 'l');// i = 2 ('l')
 * str_first(&s1, &s2);// i = 7 ('w')
 * str_first(&s1, "d!\n other data");// i = 11 ('d')
 * ```
 */
# define str_first(this, other) \
	STR_OVERLOAD1(str_first, other)(this, other)

/**### str_incpy
 * @brief Copies characters from other
	into this, while characters are INCLUDED to the given set.
 * @attention	USES SET INDEX DURING OPERATION!
 * @attention	SET INDEX TO END OF COPIED CONTENT!
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*} other
 * @param {t_str*|char*} set
 * @return {t_str*} this object
 * ```c
 * STR(s1, "Number of words: ");
 * STR(s2, "4221 words");
 * 
 * s1.i = s1.len;
 * str_incpy(&s1, &s2, "0123456789");
 * str_print(&s1);// =>	"Number of words: 4221"
 * ```
 */
# define str_incpy(this, other, set) \
	STR_OVERLOAD2(str_incpy, other, set)(this, other, set)

/**### str_itoa
 * @brief 	push the string conversion of a integer after str->i
 * @attention	USES SET INDEX DURING OPERATION!
 * @attention	DOES NOT MODIFY INDEX!
 * @param {t_str*}	this
 * @param {t_str*|char*} other
 * @return {t_str*} this
 * ```c
 * STR(s1, "Number Of Words: ");
 * int	n = 4222;
 * 
 * s1.i = s1.len;
 * str_itoa(&s1, n);// => "Number Of Words: 4222"
 * str_print(&s1);// => "hello, how are you?\nI am fine!\n"
 * ```
 */
t_str	*str_itoa(t_str *this, int32_t value);
	
/**### str_join
 * @brief 	Appends the content of another string object or a char pointer
	to the current string object.
 * @attention	USES SET INDEX DURING OPERATION!
 * @attention	SET INDEX TO END OF JOINED CONTENT!
 * @param {t_str*}	this
 * @param {t_str*|char*} other
 * @param {int32_t} number of characters to skip from other
 * @return {t_str*} this
 * ```c
 * STR(s1, "hello, you?");
 * STR(s2, "USELESS DATA\nhow are ");
 * char	s3[] = "\nI am fine!\n";
 * 
 * s1.i = 6;// (' ')
 * str_join(&s1, &s2, 13);// => "hello, how are you?"
 * // now s1.i is 19
 * str_join(&s1, s3, 0);
 * str_print(&s1);// => "hello, how are you?\nI am fine!\n"
 * ```
 */
# define str_join(this, other, n) \
	STR_OVERLOAD1(str_join, other)(this, other, n)

/**### str_last
 * @brief 	Reversely advances the index of the string object until one of the 
	characters from another string object or a char pointer is found.
 * @attention	SETS INDEX TO THE END OF THE STRING
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*|char} other
 * @return {t_str*} this object
 * ```c
 * STR(s1, "hello, world!\n");
 * STR(s2, "wrl");
 * 
 * str_last(&s1, 'l');// i = 2 ('l')
 * str_last(&s1, &s2);// i = 7 ('w')
 * str_last(&s1, "d!\n other data");// i = 11 ('d')
 * ```
 */
# define str_last(this, other) \
	STR_OVERLOAD1_CHR(str_last, other)(this, other)

/**### str_lower
 * @brief 	Converts all characters in the string to uppercase.
 * @attention	USES SET INDEX DURING OPERATION!
 * @param {t_str*}	pointer to string object
 * @return {t_str*} this object
 * ```c
 * STR(s1, "Number Of Words: 4222");
 * 
 * str_lower(&s1);// =>	("number of words: 4222")
 * ```
 */
t_str	*str_lower(t_str *str);

/**### str_ncmp
 * @brief 	Compares up to n characters of the string object's buffer
	with another string object or a char pointer.
 * @attention	IGNORES SET INDEX DURING OPERATION!
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*} other
 * @param {int32_t} n max bytes to compare
 * @return {t_str*} this object
 * ```c
 * if (str_ncmp(str, other, 42) == 0)//	checks 42 bytes or until \0 is found
 * 	ft_printf("equal strings");
 * else
 * 	ft_printf("different strings");
 * ```
 */
# define str_ncmp(this, other, n) \
	STR_OVERLOAD1(str_ncmp, other)(this, other, n)

/**### str_ncpy
 * @brief 		Copies up to n characters from another string object or a char pointer
	into the current string object, starting from a given index.
 * @attention	SET INDEX TO END OF COPIED CONTENT!
 * @attention	DOES NOT REALLOC! IN CASE OF MISSING SPACE, RETURNS ERROR!
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*} other
 * @param {int32_t} start index where to copy other from
 * @param {int32_t} n max bytes to copy
 * @return {t_str*} this object
 * ```c
 * STR(s1, "bar");
 * STR(s2, "hello, world!\n");
 * 
 * str_ncpy(&s1, &s2, 7, 3);// =>	"wor"
 * str_ncpy(&s1, &s2, 7, INT_MAX);// =>	"wor"	ERROR: not enough space in s1
 * ```
 */
# define str_ncpy(this, other, strt, n) \
	STR_OVERLOAD1(str_ncpy, other)(this, other, strt, n)

/**### str_push
 * @brief appends other string. Appends start from s->i
 * @attention	USES SET INDEX DURING OPERATION!
 * @attention	DOES NOT MODIFY INDEX!
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*|char} other
 * @return {t_str*} this object
 * ```c
 * STR(s1, "he, ");
 * STR(s2, "llo");
 * 
 * s1.i = 2;
 * str_push(&s1, &s2);// "hello, "
 * s1.i = s1.len;
 * str_push(&s1, "world!\n");// "hello, world!\n"
 * ```
 */
# define str_push(s, s2) \
	STR_OVERLOAD1_CHR(str_push, s2)(s, s2)

/**### str_reverse
 * @brief Reverses the content of the string object's buffer.
 * @attention	IGNORES SET INDEX DURING OPERATION!
 * @param {t_str*}	pointer to string object
 * @param {int(*)(int-int)|null} optional function, used to compare characters.
 * 									swap is done when a number > 0 is returned
 * @return {t_str*} this object
 * ```c
 * STR(s1, "cab");
 * 
 * str_reverse(&s1);
 * str_print(&s1);// => "bac"
 * ```
 */
t_str	*str_reverse(t_str *str);
	
/**### str_rdiff
 * @brief 	Reversely advances the index of the string object while the current 
	character does not belong to the given string or char pointer.
 * @attention	USES SET INDEX DURING OPERATION!
 * @attention	MODIFY INDEX!
 * @param {t_str*} this
 * @param {t_str*|char*|char} other
 * @return {t_str*} this
 * ```c
 * STR(s1, "hello, world!\n");
 * STR(s2, "hello");
 * STR(s3, "image.png");
 * 
 * str_rdiff(&s1, &s2);// i = 5 (',')
 * str_rdiff(&s1, 'h');// i = 1 ('e')
 * str_rdiff(&s3, ".png");// i = 4 ('e')
 * ```
 */
# define str_rdiff(this, other) \
	STR_OVERLOAD1(str_rdiff, other)(this, other)

/**### str_rfind
 * @brief Reversely finds the first occurrence of other
	in the current string object.
 * @attention	IGNORES SET INDEX DURING OPERATION!
 * @attention	MODIFY INDEX!
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*|char} other
 * @return {t_str*} this object
 * ```c
 * STR(s1, "hello, world!\n");
 * STR(s2, "world!\n");
 * 
 * str_find(&s1, 'o');// i = 8
 * str_find(&s1, &s2);// i = 7
 * str_find(&s1, "d!\n other data");// i = STRING_NPOS
 * ```
 */
# define str_rfind(this, other) \
	STR_OVERLOAD1(str_rfind, other)(this, other)

/**### str_sdup
 * @brief Free current buffer, copy other buffer (like strdup)
 * @attention	IGNORES SET INDEX DURING OPERATION!
 * @attention	SET INDEX TO ZERO
 * @param {t_str*}	pointer to string object
 * @param {t_str*|char*|char} other
 * @return {t_str*} this object
 * ```c
 * STR(s1, NULL);
 * STR(s1, "hello, world!\n");
 * 
 * str_sdup(&s1, &s2);// =>	"hello, world!\n"
 * ```
 */
# define str_sdup(this, other) \
	STR_OVERLOAD1(str_sdup, other)(this, other)

/**### str_satoi
 * @brief Converts the string object's buffer to an integer.
 * 			contrary to ft_atoi, uses a int * to save the result
 * @attention	USES SET INDEX DURING OPERATION!
 * @attention	DOES NOT MODIFY INDEX
 * @
 * @param {t_str*}	pointer to string object
 * @param {int*} ptr to an integer to save the result
 * @return {t_str*} 0 if success, else a non-zero integer with overflow
 * ```c
 * STR(s1, "42");
 * STR(s2, "42424242424242424242424242");
 * int	*n;
 * 
 * if (str_satoi(&s1, n) == 0)
 * 	ft_printf("%d\n", *n);// prints 42
 * else
 * 	ft_printf("overflow");
 * if (str_satoi(&s2, n) == 0)
 * 	ft_printf("%d\n", *n);
 * else
 * 	ft_printf("overflow");// prints error
 * ```
 */
err	str_satoi(t_str *this, int *n);

/**### str_sort
 * @brief Sort the content of the string object's buffer.
 * 			if a cmp function is not given, sorts by ascii order.
 * @attention	IGNORES SET INDEX DURING OPERATION!
 * @param {t_str*}	pointer to string object
 * @param {int(*)(int-int)|null} optional function, used to compare characters.
 * 									swap is done when a number > 0 is returned
 * @return {t_str*} this object
 * ```c
 * int	cmp(int x, int y){return y > x};
 * STR(s1, "cab");
 * 
 * str_sort(&s1, NULL);
 * str_print(&s1);// => "abc"
 * str_sort(&s1, cmp);
 * str_print(&s1);// => "cba"
 * ```
 */
t_str	*str_sort(t_str *str, int(*cmp)(int, int));

/**### str_srealloc
 * @brief Reallocates the internal buffer of the string object to a new size.
 * 			always assures the \0
 * @attention	IGNORES SET INDEX DURING OPERATION!
 * @attention	SET INDEX MAY CHANGE IF n < this->i
 * @param {t_str*}	pointer to string object
 * @param {int32_t} n bytes to allocate
 * @return {t_str*} this object
 * ```c
 * STR(s1, NULL);
 * 
 * str_srealloc(&s1, 42);
 * str_cpy(&s1, "Hello, world!\n");
 * ```
 */
t_str	*str_srealloc(t_str *this, int32_t n);

/**### str_trim
 * @brief Trims n characters, starting from this->i.
 * @attention	USES SET INDEX DURING OPERATION!
 * @attention	DOES NOT MODIFY INDEX
 * @param {t_str*}	pointer to string object
 * @param {int32_t} start index
 * @param {int32_t} end index
 * @return {t_str*} this object
 * ```c
 * STR(s1, "hello, world!\n");
 * 
 * str_cut(&s1, 0, 1);// => "llo, world!\n"
 * str_cut(&s1, 0, 0);// => "lo, world!\n"
 * str_cut(&s1, 3, 4);// => "lloworld!\n"
 * str_cut(&s1, 3, INT_MAX);// => "llo"
 * ```
 */
t_str	*str_trim(t_str *this, int32_t n);

/**### str_upper
 * @brief 	Converts all characters in the string to uppercase.
 * @attention	USES SET INDEX DURING OPERATION!
 * @param {t_str*}	pointer to string object
 * @return {t_str*} this object
 * ```c
 * STR(s1, "Number Of Words: 4222");
 * 
 * str_lower(&s1);// =>	("NUMBER OF WORDS: 4222")
 * ```
 */
t_str	*str_upper(t_str *str);

#endif