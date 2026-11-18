/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:40:36 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/18 17:18:02 by alerusso42       ###   ########.fr       */
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
enum e_msg
{//						PURPOSE			|	PARSING
	MSGE_INVALID = 0,//	invalid message	|	{1TYPE}
	MSGE_CLIENT_NEW,//	new client		| 	{1TYPE, 4_ID, 2_t_info}
	MSGE_CLIENT_DEL,//  client deleted	|	{1TYPE, 4_ID}
	MSGE_QUIT,//		quit everything	|	{1TYPE}
	MSGE_START,//		matchmaking end	|	{1TYPE, 4_ID}
	MSGE_ERROR,//		general error	|	{1TYPE, n_string, \0}
	MSGE_ID_ASK,//		client asks id	|	{1TYPE, 4_tmpID}
	MSGE_ID_RECEIVE,//	give client id	|	{1TYPE, 4_ID}
	MSGE_NUM,							
	MSGID_FRONT = 1,
	MSGID_MASTER
};
