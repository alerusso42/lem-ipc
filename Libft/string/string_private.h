/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:50:27 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:43:41 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_PRIVATE_H
# define STRING_PRIVATE_H
# include "string.h"
/** @cond DOXYGEN_SHOULD_SKIP_THIS */

typedef struct s_str			t_str;
typedef enum e_str_error		t_str_error;
typedef int32_t					err;

# define _STR_REALLOC_SIZE 64

# define STR_DEBUG false
# if STR_DEBUG == true
#  define STR_LOG(error, ...) err_printf(error, ##__VA_ARGS__)
# else 
#  define STR_LOG(error, ...) (void)0
# endif
//REVIEW - STR_OVERLOAD
/*
	f:	 	the name of the function
	name:	the name of the string object
	T:		the type of the variable it receives

	example: #define func_name(param)	STR_OVERLOAD(func_name, obj_name, param)
	see it as a switch case:

	switch (T)
	{
		case (char*):
			f ## _char	---> example:	print_char
		case (t_str):
			f ## _str	---> example:	print_str
		case (t_str*):
			f ## _ptr	---> example:	print_ptr
	}
*/

//SECTION - destructor

//	the function given to cleanup is called when the variable exits from its
//	scope
# define clean(base) __attribute__((cleanup(_ ## base ## _destructor)))
# define clean_ptr(base) __attribute__((cleanup(_ ## base ## _ptr_destructor)))

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif

# define STR_OVERLOAD_CHECK(f, name, T) _Generic((T), \
		char*		:	_ ## f ## _char,\
		const char*	:	_ ## f ## _char,\
		void*		:	_ ## f ## _this,\
		t_str*		:	_ ## f ## _str,\
		const t_str*:	_ ## f ## _str)(name, T)

#define _STR_OVERLOAD_SECOND_ARG(f, T1type, T2) _Generic((T2), \
	const t_str*:		_ ## f ## _ ## T1type ## _str,\
	t_str*:				_ ## f ## _ ## T1type ## _str,\
	const char*:		_ ## f ## _ ## T1type ## _char,\
	char*:				_ ## f ## _ ## T1type ## _char)

#define STR_OVERLOAD1(f, T) _Generic((T), \
	const t_str*:		_ ## f ##_str,\
	t_str*:				_ ## f ## _str,\
	const char*:		_ ## f ## _char,\
	char*:				_ ## f ## _char)


#define STR_OVERLOAD1_CHR(f, T) _Generic((T), \
	const t_str*:		_ ## f ##_str,\
	t_str*:				_ ## f ## _str,\
	const char*:		_ ## f ## _char,\
	char*:				_ ## f ## _char,\
	int:				_ ## f ## _chr,\
	char:				_ ## f ## _chr)

#define STR_OVERLOAD2(f, T1, T2) _Generic((T1), \
	const t_str*:		_STR_OVERLOAD_SECOND_ARG(f, str, T2),\
	t_str*:				_STR_OVERLOAD_SECOND_ARG(f, str, T2),\
	const char*:		_STR_OVERLOAD_SECOND_ARG(f, char, T2),\
	char*:				_STR_OVERLOAD_SECOND_ARG(f, char, T2))

//SECTION - private functions

# define str_check(name, other)	STR_OVERLOAD_CHECK(str_check, name, other)
t_str	*_str_scpy(t_str *this, const char *other, const char *set, int m);
bool	_str_check_char(t_str *this, const char *other);
bool	_str_check_str(t_str *this, const t_str *other);
bool	_str_check_this(t_str *this, const void *empty);
void	_str_destructor(void *str);
void	_str_garbage_collector(t_str *p, bool delete);
void	_str_set(t_str *this);
t_str	*_str_reset(t_str *this, int i);
t_str	*_str_set_error(t_str *str, int err, char *func_name);

t_str	*_str_app_str(t_str *s, const t_str *s2);
t_str	*_str_app_char(t_str *s, const char *s2);
int32_t	str_cmp_char(t_str *this, const char *other);
int32_t	str_cmp_str(t_str *this, const t_str *other);
t_str	*_str_cpy_char(t_str *this, const char *other);
t_str	*_str_cpy_str(t_str *this, const t_str *other);
t_str	*_str_diff_chr(t_str *this, char other);
t_str	*_str_diff_char(t_str *this, const char *other);
t_str	*_str_diff_str(t_str *this, const t_str *other);
t_str	*_str_excpy_char_char(t_str *this, const char *other, const char *set);
t_str	*_str_excpy_str_char(t_str *this, const t_str *other, const char *set);
t_str	*_str_excpy_char_str(t_str *this, const char *other, const t_str *set);
t_str	*_str_excpy_str_str(t_str *this, const t_str *other, const t_str *set);
t_str	*_str_find_chr(t_str *this, char other);
t_str	*_str_find_char(t_str *this, const char *other);
t_str	*_str_find_str(t_str *this, const t_str *other);
t_str	*_str_first_chr(t_str *this, char other);
t_str	*_str_first_char(t_str *this, const char *other);
t_str	*_str_first_str(t_str *this, const t_str *other);
t_str	*_str_incpy_char_char(t_str *this, const char *other, const char *set);
t_str	*_str_incpy_str_char(t_str *this, const t_str *other, const char *set);
t_str	*_str_incpy_char_str(t_str *this, const char *other, const t_str *set);
t_str	*_str_incpy_str_str(t_str *this, const t_str *other, const t_str *set);
t_str	*_str_join_str(t_str *s, const t_str *s2, int32_t n);
t_str	*_str_join_char(t_str *s, const char *s2, int32_t n);
t_str	*_str_last_chr(t_str *this, char other);
t_str	*_str_last_char(t_str *this, const char *other);
t_str	*_str_last_str(t_str *this, const t_str *other);
int32_t	_str_ncmp_char(t_str *this, const char *other, int32_t n);
int32_t	_str_ncmp_str(t_str *this, const t_str *other, int32_t n);
t_str	*_str_ncpy_char(t_str *this, const char *other, int32_t strt, int32_t n);
t_str	*_str_ncpy_str(t_str *this, const t_str *other, int32_t strt, int32_t n);
t_str	*_str_push_str(t_str *s, const t_str *s2);
t_str	*_str_push_char(t_str *s, const char *s2);
t_str	*_str_push_chr(t_str *s, char c);
t_str	*_str_rdiff_chr(t_str *this, char other);
t_str	*_str_rdiff_char(t_str *this, const char *other);
t_str	*_str_rdiff_str(t_str *this, const t_str *other);
t_str	*_str_rfind_char(t_str *this, const char *other);
t_str	*_str_rfind_str(t_str *this, const t_str *other);
t_str	*_str_sdup_char(t_str *this, const char *other);
t_str	*_str_sdup_str(t_str *this, const t_str *other);

/** @endcond */
#endif