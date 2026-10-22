/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_murmur_hash.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 07:33:30 by codespace         #+#    #+#             */
/*   Updated: 2025/09/21 10:01:13 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

/*
uint32_t	mur_switch(uint32_t h, unsigned char *data, int len, uint32_t m)
{
	if (len == 3)
		h ^= data[2] << 16;
	if (len >= 2)
		h ^= data[1] << 8;
	if (len >= 1)
	{
		h ^= data[0];
		h *= m;
	}
	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;
	return (h);
}

//	https://en.wikipedia.org/wiki/MurmurHash
uint32_t	murmurhash2(const void *key, int len, uint32_t seed)
{
	uint32_t		m;
	uint32_t		h;
	uint32_t		k;
	unsigned char	*data;

	m = 0x5bd1e995;
	h = seed ^ len;
	data = (unsigned char *)key;
	while (len >= 4)
	{
		k = *(uint32_t *)data;
		k *= m;
		k ^= k >> 24;
		k *= m;
		h *= m;
		h ^= k;
		data += 4;
		len -= 4;
	}
	return (mur_switch(h, data, len, m));
}*/

//	file->size + 1 is the size of the lists, and the hash limit.
int	_daft_hash(t_daft_list *file, const char *key)
{
	int	len;

	len = 0;
	while (key[len] && key[len] != file->field_sep[0])
		++len;
	return (murmurhash2(key, len, SEED) % (file->size + 1));
}
