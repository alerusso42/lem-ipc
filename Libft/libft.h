/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:30:58 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/02 13:53:45 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef FUN_MACROS
#  define FUN_MACROS
#  define MALLOC malloc
#  define CALLOC ft_calloc
#  define FREE free
#  define WRITE write
#  define READ readfd
#  define SEEK lseek
#  define OPEN ft_open
#  define CLOSE close
#  define SDL_RWops int
# endif
# include <stdint.h>
# include <stdlib.h>
// # include "files/mfile.h"
// # include "daft/daft.h"
# include "data/list/list.h"
# include "data/map/map.h"
# include "printf/ft_printf.h"
# include "string/string.h"

// used for malloc test
# define TEST_DATA_DIR "../Libft/daft/DATA_DIR"

typedef struct s_list	t_list;
typedef struct s_list2	t_list2;
typedef struct s_manage_fds	t_manage_fds;
typedef struct s_matr2	t_matr2;
typedef struct s_matr3	t_matr3;

typedef struct s_fd
{
	int			p;
	int			n;
}	t_fd;

enum e_charsets
{
	ALPHA,
	UPPER_ALPHA,
	LOWER_ALPHA,
	DIGIT,
	ALPHANUM,
	EXCLUDE,
	INCLUDE,
};

int64_t		ft_atoi(const char *nptr);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
char		*ft_itoa(int num);
int			ft_strcount(const char *s, char c);
void		ft_itoa_stack(char *str, int64_t num);
void		ft_uitoa_stack(char *str, uint64_t num);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_free(char *s1, char *s2, int mode);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);

int			sub_strlen(const char *s, const char *charset, int mode);
int			sub_strcpy(char *dest, const char *src, const char *charset, int mode);

//		LIST

t_list		*lst_new(void *content);
void		lst_front(t_list **lst, t_list *new);
int			lst_size(t_list *lst);
t_list		*lst_last(t_list *lst);
void		lst_back(t_list **lst, t_list *new);
void		lst_delone(t_list *lst, void (*del)(void *));
void		lst_clear(t_list **lst, void (*del)(void *));
void		lst_iter(t_list *lst, void (*f)(void *));

t_list2		*lst2_new(void *content1, void *content2);
void		lst2_front(t_list2 **lst, t_list2 *new);
int			lst2_size(t_list2 *lst);
t_list2		*lst2_last(t_list2 *lst);
void		lst2_back(t_list2 **lst, t_list2 *new);
void		lst2_delone(t_list2 *lst, void (*del)(void *));
void		lst2_clear(t_list2 **lst, void (*del)(void *));
void		lst2_iter(t_list2 *lst, void (*f)(void *));

//		MATRIX

// int		matrix2_len(char **matr);
// int		matrix3_len(char ***matr);
// void	*_matrix2_del(t_matr2 *matr2);
// void	*_matrix3_del(t_matr3 *matr3);
// char	***ft_multi_split(char *s, char matr_c, char str_c);
// void	*matrix_convert(void *matr, int matr_type);

//		PRINTF

/*void	ft_putchar_fd(char c, t_fd fd);
void	ft_putendl_fd(char *s, t_fd fd);
void	ft_putnbr_fd(int n, t_fd fd);
void	ft_putstr_fd(char *s, t_fd fd);
int		fd_printf(t_fd fd, const char *str, ...);
int	    ft_printf(int fd, const char *str, ...);*/

int			cut_string(char *string, size_t start, size_t end);

//	MATH

int	int_size(int64_t n);
int	uint_size(uint64_t n);

//	FILE

// t_fd			openfd(const char *filename, const char *permissions);
// int				ft_open(const char *filename, const char *perm);
// t_manage_fds	*fd_static_storage(bool);
// int				get_filedata(t_fd *fd, char **filename);
// void			del_filedata(void);
// int				switch_filedata(t_fd fd);
// int				fd_indexation(void);
// void			closefd(t_fd fd);
// int				read_curr(t_manage_fds *data, int count);
// int				readfd(t_fd	fd, char *buff, int count);
// char			*get_static_buffer(int fd, bool reset, bool reset_all);
// char			*gnl();
// int				writefd(t_fd fd, const char *s, size_t len);
// int				reset_fd(t_fd fd);

// DAFT

int 	daft_init(const char *path, const char *settings_filename);
void	daft_quit(void);
void	daft_swap(int enum_id);
void	daft_free(void *mem);
void	*daft_get(const char *search);
int		daft_load(void);
void	*daft_edit(const char *search, int size, int mtr_number);
void	*daft_append(const char *key, int size, int mtr_number);

#endif
