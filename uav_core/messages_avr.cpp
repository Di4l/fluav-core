/*
 * messages_avr.cpp
 *
 *  Created on: 12/09/2014
 *      Author: rhermoso
 */

#ifdef ARDUINO
//-----------------------------------------------------------------------------
#include "messages.hpp"
//-----------------------------------------------------------------------------
using namespace nsUav;
//-----------------------------------------------------------------------------

TMessage::TMessage()
{
	onCreateDevice = NULL;
}
//-----------------------------------------------------------------------------

TMessage::~TMessage()
{
	onCreateDevice = NULL;
}
//-----------------------------------------------------------------------------

size_t TMessage::serialize_config(TInterface& iface, char*& cBuffer)
{
	size_t        ret = 0x00;
	short         s_val;
	char          buff[2 + 6 * iface.size()];

	memset(buff, 0, 2 + 6 * iface.size());

	buff[0] = MSG_CMD_CONFIG;

	for(size_t i = 0; i < ret; ++i)
	{
		if(iface[i]->enabled())
		{
			++ret;
			buff[2 + 6 * i] = iface[i]->id();
			s_val = iface[i]->minimum();
			buff[3 + 6 * i] = (s_val >> 8) & 0x0ff;
			buff[4 + 6 * i] = s_val & 0x0ff;
			s_val = iface[i]->maximum();
			buff[5 + 6 * i] = (s_val >> 8) & 0x0ff;
			buff[6 + 6 * i] = s_val & 0x0ff;
			buff[7 + 6 * i] = iface.id();
		}
	}
	buff[1] = char(ret & 0x0ff);

	ret = 2 + 6 * ret;
	cBuffer = new char[ret];
	memcpy(cBuffer, buff, ret);

	return ret;
}
//-----------------------------------------------------------------------------

size_t TMessage::serialize_set(TInterface& iface, char*& cBuffer)
{
	size_t         ret = 0;
	char           buff[2 + 3 * iface.size()];
	unsigned short us_val;

	buff[0] = MSG_CMD_SET;

	for(size_t i = 0; i < iface.size(); ++i)
	{
		if(iface[i]->enabled() && iface[i]->modified())
		{
			++ret;
			us_val = iface[i]->value();
			buff[2 + 3 * i] = iface[i]->id();
			buff[3 + 3 * i] = (us_val >> 8) & 0x0ff;
			buff[4 + 3 * i] = us_val & 0x0ff;
		}
	}
	buff[1] = char(ret & 0x0ff);

	ret = 2 + 3 * ret;
	cBuffer = new char[ret];
	memcpy(cBuffer, buff, ret);

	return ret;
}
//-----------------------------------------------------------------------------

size_t TMessage::serialize_log(char* cTxt, char*& cBuffer)
{
	size_t ret = strlen(cTxt);

	cBuffer = new char[2 + ret];

	cBuffer[0] = MSG_CMD_LOG;
	cBuffer[1] = ret;

	memcpy(&cBuffer[2], cTxt, ret);

	return ret;
}
//-----------------------------------------------------------------------------

size_t TMessage::serialize(uav_msg ucCommand, TInterface& iface, char*& cBuffer)
{
	size_t ret = 0;

	if(cBuffer)
	{
		delete[] cBuffer;
		cBuffer = NULL;
	}

	switch(ucCommand)
	{
	case MSG_CMD_CONFIG:
		ret = serialize_config(iface, cBuffer);
		break;

	case MSG_CMD_SET:
		ret = serialize_set(iface, cBuffer);
		break;

	default:
		break;
	}

	return ret;
}
//-----------------------------------------------------------------------------

size_t TMessage::serialize(uav_msg ucCommand, char* cTxt, char*& cBuffer)
{
	size_t ret = 0;

	if(cBuffer)
	{
		delete[] cBuffer;
		cBuffer = NULL;
	}

	switch(ucCommand)
	{
	case MSG_CMD_LOG:
		ret = serialize_log(cTxt, cBuffer);
		break;

	default:
		break;
	}

	return ret;
}
//-----------------------------------------------------------------------------

size_t TMessage::unserialize(TInterface& iface, char*& cBuffer)
{
	size_t ret = 0;

	if(cBuffer)
	{
		ret = cBuffer[1];

		TDevice*       dev = NULL;
		unsigned short val = 0;
		short          min, max;
		for(size_t i = 0; i < ret; ++i)
		{
			size_t idx = 0;

			switch(cBuffer[0])
			{
			case MSG_CMD_CONFIG:
				idx = 2 + 6 * i;
				if(onCreateDevice)
				{
					min = ((short)cBuffer[idx + 1] << 8)
						| ((short)cBuffer[idx + 2]);
					max = ((short)cBuffer[idx + 3] << 8)
						| ((short)cBuffer[idx + 4]);

					onCreateDevice(uav_id(cBuffer[idx]), min, max, iface.id());
				}
				break;

			case MSG_CMD_SET:
				idx = 2 + 3 * i;
				dev = iface[uav_id(cBuffer[idx])];
				val = ((unsigned short)cBuffer[idx + 1] << 8)
					| ((unsigned short)cBuffer[idx + 2]);
				dev->value() = val;
				break;

			default:
				break;
			}
		}
	}

	return ret;
}
//-----------------------------------------------------------------------------
#endif /* ARDUINO */



