/*
 * messages.cpp
 *
 *  Created on: 30/07/2014
 *      Author: rhermoso
 */


#ifndef ARDUINO
//-----------------------------------------------------------------------------
#include "messages.hpp"
#include <cstring>
#include <iostream>
//-----------------------------------------------------------------------------
using namespace nsUav;
//-----------------------------------------------------------------------------

TMessage::TMessage()
{
//	onCreateDevice = NULL;
}
//-----------------------------------------------------------------------------

TMessage::~TMessage()
{
//	onCreateDevice = NULL;
}
//-----------------------------------------------------------------------------

size_t TMessage::serialize_config(TInterface& iface, char*& cBuffer)
{
	size_t        ret = 0x00;
	short         s_val;
	std::string   buff;

	buff.push_back(MSG_CMD_CONFIG);
	buff.push_back(0xff);

	for(size_t i = 0; i < ret; ++i)
	{
		if(iface.devices()[i]->enabled())
		{
			++ret;
			buff.push_back(char(iface.devices()[i]->id()));
			s_val = iface.devices()[i]->minimum();
			buff.push_back(char((s_val >> 8) & 0x0ff));
			buff.push_back(char(s_val & 0x0ff));
			s_val = iface.devices()[i]->maximum();
			buff.push_back(char((s_val >> 8) & 0x0ff));
			buff.push_back(char(s_val & 0x0ff));
			buff.push_back(char(iface.id()));
		}
	}
	buff[1] = char(char(ret & 0x0ff));

	ret = 2 + 6 * ret;
	cBuffer = new char[ret];
	memcpy(cBuffer, buff.data(), ret);

	return ret;
}
//-----------------------------------------------------------------------------

size_t TMessage::serialize_set(TInterface& iface, char*& cBuffer)
{
	size_t         ret = 0;
	std::string    buff;
	unsigned short us_val;

	buff.push_back(MSG_CMD_SET);
	buff.push_back(0xff);

	for(size_t i = 0; i < iface.devices().size(); ++i)
	{
		if(iface.devices()[i]->enabled() && iface.devices()[i]->modified())
		{
			++ret;
			us_val = iface.devices()[i]->value();
			buff.push_back(iface.devices()[i]->id());
			buff.push_back(char((us_val >> 8) & 0x0ff));
			buff.push_back(char(us_val & 0x0ff));
		}
	}
	buff[1] = char(ret & 0x0ff);

	ret = 2 + 3 * ret;
	cBuffer = new char[ret];
	memcpy(cBuffer, buff.data(), ret);

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

		TDevice*       mod = NULL;
		unsigned short val = 0;
//		short          min, max;
		std::string    str_aux;

		for(size_t i = 0; i < ret; ++i)
		{
			size_t idx = 0;

			switch(cBuffer[0])
			{
			case MSG_CMD_SET:
				idx = 2 + 3 * i;
				mod = iface.devices()[uav_id(cBuffer[idx])];
				val = ((unsigned short)cBuffer[idx + 1] << 8)
					| ((unsigned short)cBuffer[idx + 2]);
				mod->value() = val;
				break;

			case MSG_CMD_LOG:
				str_aux = std::string(&cBuffer[2], size_t(cBuffer[1]));
				std::cout << str_aux << std::endl;
				break;

			case MSG_CMD_CONFIG:
/*
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
*/
			default:
				break;
			}
		}
	}

	return ret;
}
//-----------------------------------------------------------------------------
#endif // #ifndef ARDUINO
