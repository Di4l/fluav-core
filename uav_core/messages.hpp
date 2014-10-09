/*
 * messages.hpp
 *
 *   Message declaration
 *   Copyright (C) 2014  Raúl Hermoso Sánchez
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License along
 *   with this program; if not, write to the Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Created on: 12/09/2014
 *      Author: Raúl Hermoso Sánchez
 *      e-mail: raul.hermoso@gmail.com
 */

/*
 * Messages Format:
 *
 * All messages consist of a header and a body. The body is divided into
 * frames, each containing an atomic piece of information.
 *
 * The header has two bytes. The first one is the command ID (or message type)
 * and the second the number of frames that contains the body. The size of each
 * frame is determined by the command type. Since the number of frames in the
 * body is stored in a single byte, there is a limit of 256 frames that can fit
 * into a single message. Since, each frame, normally, informs of one device,
 * every message has a limit of 256 devices it can inform about. We think this
 * is more than enough for an RC model.
 *
 * 1. MSG_CMD_SET
 *
 * Used to update devices values. An interface sends this message over its
 * connection to notify the other end of a change in the value in a set of
 * devices.
 *
 *  +-----------+-----------+-----------+-----------+-----------+--
 *  |   BYTE0   |   BYTE1   |   BYTE2   |   BYTE3   |   BYTE4   |
 *  +-----------+-----------+-----------+-----------+-----------+--
 *  |        HEADER         |         DEVICE SET FRAME          |
 *  +-----------+-----------+-----------+-----------+-----------+--
 *  |    CMD    |   # DEV   |    ID1    |        VALUE 1        |
 *  +-----------+-----------+-----------+-----------+-----------+--
 *
 *  Header:
 *    CMD:    Command ID. In this case will always be 0x02 (MSG_CMD_SET)
 *    # DEV:  Number of device frames that follow
 *  Device Set Frame:
 *    IDn:    Device ID
 *    VALUEn: New value for device IDn
 *
 *  The total number of bytes of a MSG_CMD_SET command can be calculated by
 *  the following expression:
 *
 *        mssg_size = 2 + 3 * #_devices
 *
 *  2. MSG_CMD_CONFIG
 *
 *  Used to configure the different devices, their ids (pin #), which
 *  interfaces each uses, and that sort of information. This message is though
 *  specifically for configuring the Arduino from the RPi. The idea is that the
 *  RPi read the device layout and configuration for the different sensors from
 *  a file, and sends this message to the Arduino, which then knows what kind
 *  of device is attached to what pins and what type of interface each uses.
 *
 *  +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 *  |   BYTE0   |   BYTE1   |   BYTE2   |   BYTE3   |   BYTE4   |   BYTE5   |   BYTE6   |   BYTE7   |
 *  +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 *  |        HEADER         |                          DEVICE CONFIG FRAME                          |
 *  +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 *  |    CMD    |   # DEV   |    ID1    |       MIN_VALUE       |       MAX_VALUE       |    IFC1   |
 *  +-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
 *
 *  Header:
 *    CMD:    Command ID. In this case will always be 0x01 (MSG_CMD_CONFIG)
 *    # DEV:  Number of configuration frames that follow
 *  Device Set Frame:
 *    IDn:      Device ID
 *    MIN_VALUE Absolute minimum value the device can take
 *    MAX_VALUE Absolute maximum value the device can take
 *    IFCn:     Interface Code to attach to. This is a predefined code that
 *              every module should know about.
 *
 *  The total number of bytes of a MSG_CMD_CONFIG command can be calculated by
 *  the following expression:
 *
 *        mssg_size = 2 + 6 * #_devices
 *
 *  3. MSG_CMD_LOG
 *
 *  Used to send text messages.
 *
 *  +-----------+-----------+-----------+-----------+---
 *  |   BYTE0   |   BYTE1   |   BYTE2   |   BYTE3   |
 *  +-----------+-----------+-----------+-----------+---
 *  |        HEADER         |      TEXT STRING
 *  +-----------+-----------+-----------+-----------+---
 *  |    CMD    |    LEN    |   CHAR1   |   CHAR2   |
 *  +-----------+-----------+-----------+-----------+---
 *
 */

//-----------------------------------------------------------------------------
#ifndef MESSAGES_HPP_
#define MESSAGES_HPP_
//-----------------------------------------------------------------------------
#include "interface.hpp"
//-----------------------------------------------------------------------------

namespace nsUav
{
	//-------------------------------------------------------------------------

//	typedef TDevice* (*fncOnConfigure)(uav_id, short, short, uav_id);
	//-------------------------------------------------------------------------

	class TMessage
	{
	private:
		size_t serialize_config(TInterface& iface, char*& cBuffer);
		size_t serialize_set(TInterface& iface, char*& cBuffer);
		size_t serialize_log(char* cTxt, char*& cBuffer);

	protected:
	public:
		TMessage();
		virtual ~TMessage();

		size_t serialize(uav_msg ucCommand, TInterface& iface, char*& cBuffer);
		size_t serialize(uav_msg ucCommand, char* cTxt, char*& cBuffer);
		size_t unserialize(TInterface& iface, char*& cBuffer);

//		fncOnConfigure onCreateDevice;
	};
	//-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
#endif /* MESSAGES_HPP_ */
//-----------------------------------------------------------------------------
