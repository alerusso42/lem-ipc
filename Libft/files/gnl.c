/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:38:47 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/02 10:56:26 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfile.h"

char		*get_static_buffer(int fd, bool reset, bool reset_all);
static void	read_from_file(char *buffer, t_fd fd, char **new_line);
static int	read_from_buff(char *buffer, char **old_content);
/*
//TODO - 
			1)	strlen fatto bene;
			2)	strstr fatto bene;
			3)	strstr che calcoli lunghezza (sub_strlen);
			4)	strstr che copi (sub_strcpy);
			5)	una funzione che legga e che aggiorni l'fd;
			6)	una integrazione di queste funzioni con gli fd;
			7)	read_line riceverà l'offset di dove trovare le info nel buffer;
			8)	Algoritmo di hashing e ricerca.
*/

//ANCHOR - gnl
/*
//	gnl read a file line by line, reading for BUFFER_SIZE defined in mfile.h.
//	exceedes lines are saved in a stack matrix of [MAX_FILES][BUFFER_SIZE]
//	file must be opened using openfd() function.
//	file taken is last file opened with openfd().
	You can use switch_filedata() function to change file.

	@input:		none
	@return:	string allocated with malloc, that ends with \0 (NOT \n),
				or NULL if file is finished or error occurs.
	@variables:	[char *buffer]------>	chars got by old read calls
				[t_fd fd]----------->	data of file data stream and its id
				[char *old_content]->	chars from buffer
				[new_line]---------->	final str, a union of old/new content
	@usage:	*-------------------------------*	
			|	t_fd = openfd("file", "r");	|
			|	char *line = gnl();			|
			|	//code ...					|
			|	free(line);					|
			|	del_filedata();				|
			*-------------------------------*
//REVIEW
//	1)	get data from the current fd. It there is none, returns NULL. 
		fd id is used to get buffer[fd.n], in get_static_buffer;
	2)	read_from_buffer saves and trim buffer chars until \n.
		If detects a \n, returns 1, and skip read_from_file;
	3)	read_from_file reads until it finds a \n or EOF;
	4)	old content is fused with new_content, using ft_strjoin_which.
*/
char	*gnl(void)
{
	char	*buffer;
	t_fd	fd;
	char	*old_content;
	char	*new_line;

	old_content = NULL;
	if (!get_filedata(&fd, NULL))
		return (NULL);
	buffer = get_static_buffer(fd.n, 0, 0);
	if (read_from_buff(buffer, &old_content) == 1)
		return (old_content);
	read_from_file(buffer, fd, &new_line);
	new_line = ft_strjoin_free(old_content, new_line, 3);
	return (new_line);
}

//ANCHOR - get_static_buffer
/*
//	get data of fd id buffer. Reset buffer data.

	@input:		[int fd]------>		id of the fd of the file
				[bool reset]-->		if true, deletes all buffer content
				[bool reset_all]->	if true, deletes all buffers content
	@return:	the buffer of buffer[fd]
	@variables:	[t_manage_fds *data]------>	store data of all fds
				[int i]
//REVIEW
//	data->last is last fd id saved using openfd.
	When reset_all is called, get_static_buffer calls itself recursively
	iterating for every fd.
*/
char	*get_static_buffer(int fd, bool reset, bool reset_all)
{
	t_manage_fds	*data;
	int				i;

	data = fd_static_storage(0);
	if (reset_all)
	{
		i = 1;
		while (i != data->last + 1)
		{
			get_static_buffer(i, 1, 0);
			++i;
		}
	}
	else if (reset)
	{
		i = 0;
		while (i != BUFFER_SIZE + 1)
		{
			data->buffer[fd][i] = 0;
			i++;
		}
	}
	return (data->buffer[fd]);
}

//ANCHOR - read_from_buffer
/*
//	get chars already in buffer.

	@input:		[char *buffer]
				[char **old_content]
	@return:	[0] if new content from read is needed;
				[1] if a \n is found, and read must not be called.
	@variables:	[int i]
				[char *s]
//REVIEW
//	1)	If buffer is empty, [0] is returned;
	2)	A new string is allocated, using size of buffer until \n;
	3)	String is populated using chars from buffer until \n;
	4)	If old_content already exists (see read_from_file), 
		old_content joins s, otherwise old_content becomes s;
	5)	Cuts all chars from buffer until \n.
*/
static int	read_from_buff(char *buffer, char **old_content)
{
	int		i;
	char	*s;

	if (buffer[0] == '\0')
		return (0);
	i = sub_strlen(buffer, "\n", EXCLUDE);
	s = ft_calloc(i + 1, sizeof(char));
	if (!s)
		return (1);
	sub_strcpy(s, buffer, "\n", EXCLUDE);
	if (*old_content)
		*old_content = ft_strjoin_free(*old_content, s, 3);
	else
		*old_content = s;
	if (buffer[i] == '\n')
		return (cut_string(buffer, 0, i + 1), 1);
	cut_string(buffer, 0, i + 1);
	return (0);
}

//ANCHOR - read_from_file
/*
//	get chars from file.

	@input:		[char *buffer]
				[t_fd fd]
				[char **new_line]
	@return:	none
	@variables:	[int bytes_read]-->	total number of bytes read in the loop
				[int diff]-------->	used to check if new read given BUFFER_SIZE
//REVIEW
//	1)	While there's no \n in buffer:
	2)	If buffer is not empty, add the buffer to the head of *new_line.
		Then, if malloc does not fail, a \0 is put to last element.
		This is useful when BUFFER_SIZE < line_size;
	3)	diff starts from 0. Becomes equal to bytes_read at the end of a 
		cycle. If (bytes_read - diff) != BUFFER_SIZE, EOF is reached,
		or file is not readable: so loop is ended;
	4)	The new chars put in the buffer are extracted using read_from_buff.  
*/
static void	read_from_file(char *buffer, t_fd fd, char **new_line)
{
	int		bytes_read;
	int		diff;

	bytes_read = 0;
	diff = 0;
	*new_line = NULL;
	while (ft_strchr(buffer, '\n') == NULL)
	{
		if (*buffer)
			*new_line = ft_strjoin_free(*new_line, buffer, 1);
		if (*buffer && *new_line)
			(*new_line)[bytes_read] = 0;
		bytes_read += readfd(fd, buffer, BUFFER_SIZE);
		diff = bytes_read - diff;
		if (diff != BUFFER_SIZE)
		{
			cut_string(buffer, diff, BUFFER_SIZE + 1);
			break ;
		}
		diff = bytes_read;
		//buffer[bytes_read] = 0;
	}
	read_from_buff(buffer, new_line);
}

/*NOTE - test main
#define POKEDEX "../tests/pokedex.txt"

int	main(void)
{
	char	*line;
	t_fd	fd;

	fd = openfd(POKEDEX, "r");
	if (fd.n == 0)
	{
		perror("Error opening file");
		return (1);
	}
	line = gnl();
	int c = 1;
	while (line != NULL)
	{
		printf("%s\n", line);
		FREE(line);
		line = gnl();
		c++;
	}
	(void)c;
	del_filedata();
	return (0);
}
*/
