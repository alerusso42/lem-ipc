/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:40:36 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/12 21:18:25 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/**
 * @brief message structure
 * 	|type of event (1 byte)|event info(0-63 bytes)|
 * @example client with id 42 arrives
 * msg type: MSGE_CLIENT_NEW (= ascii 1)
 * msg parsing method: MSG_PARSE_TYPE[MSGE_CLIENT_NEW] = MSGP_ID
 * msg len: event type byte + MSG_PARSE_BYTES[MSGP_ID] = 5
 * msg = {1, 0, 0, 0, 42} = "\1\0\0\0*"
 */
enum e_msg_event
{
	MSGE_INVALID = 0,
	MSGE_CLIENT_NEW,
	MSGE_CLIENT_DEL,
	MSGE_QUIT,
	MSGE_NUM
};

enum e_msg_parse
{
	MSGP_ID,
	MSGP_NONE,
	MSGP_NUM
};

//@var {map<msg_title, msgp_type>}
//get correct parsing type for the message
#define MSG_PARSE_TYPE \
(const char []) \
{\
	[MSGE_INVALID] =	MSGP_NONE,	\
	[MSGE_CLIENT_NEW] =	MSGP_ID,	\
	[MSGE_CLIENT_DEL] =	MSGP_ID,	\
	[MSGE_QUIT] =	MSGP_NONE,	\
	[MSGE_NUM] = MSGP_INVALID	\
}

//@var {map<msgp_type, bytes num>}
//get correct bytes length for the parsing type
#define MSG_PARSE_BYTES \
(const char []) \
{\
	[MSGP_ID] =	4,	\
	[MSGP_NONE] = 0,	\
	[MSGP_NUM] = 0	\
}
