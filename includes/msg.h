/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:40:36 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/14 12:43:08 by alerusso42       ###   ########.fr       */
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
