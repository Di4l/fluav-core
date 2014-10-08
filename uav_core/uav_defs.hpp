/*
 * uav_defs.hpp
 *
 *  Created on: 29/08/2014
 *      Author: rhermoso
 */

//-----------------------------------------------------------------------------
#ifndef UAV_DEFS_HPP_
#define UAV_DEFS_HPP_
//-----------------------------------------------------------------------------
#ifdef ARDUINO
	#define ARDUINO_AVR_LEONARDO

	#include "ard_defs.hpp"

#else
	#include <string>
	#include <map>

	#define _map	std::map
#endif
//-----------------------------------------------------------------------------

typedef short          uav_value;
typedef unsigned short uav_uvalue;
typedef unsigned char  uav_id;

#define UI_INVALID_ID	0xff
#define UII_MASK_READ	0x10

//-- INTERFACE IDs
#define UII_SERIAL		0x01	//-- Serial for interface communication
#define UII_TCP			0x02	//-- TCP/IP for interface communication
#define UII_PWM_RD		0x10	//-- Pulse Width Modulated (read only)
#define UII_PWM			0x20	//-- Pulse Width Modulated (read and write)
#define UII_I2C_RD		0x30	//-- I2C (read only)
#define UII_I2C			0x40	//-- I2C (read and write)
#define UII_DIGITAL_RD	0x50	//-- Digital (read only)
#define UII_DIGITAL		0x60	//-- Digital (read and write)
#define UII_ANALOG_RD   0x70	//-- Analog  (read only)
#define UII_ANALOG      0x80	//-- Analog  (read and write)
//-----------------------------------------------------------------------------

namespace nsUav
{
	//-------------------------------------------------------------------------

	class TObject
	{
	private:
		uav_id m_uiId;
		bool   m_bEnabled;

	protected:
	public:
		TObject(uav_id uiId) : m_uiId(uiId), m_bEnabled(true) {}
		virtual ~TObject() {}

		inline uav_id id()      { return m_uiId;     }
		inline bool&  enabled() { return m_bEnabled; }
	};
	//-------------------------------------------------------------------------

	template <class T>
	class TContainer
	{
	private:
	protected:
		_map<uav_id, T*> m_mItems;

	public:
		TContainer() {}
		virtual ~TContainer() { clear(); }

		inline size_t size() { return m_mItems.size(); }

		virtual uav_id insert(T* tItm);
		virtual void   erase(uav_id uiId);
		virtual void   clear();

		virtual T* operator [](uav_id uiId);
		virtual T* operator [](size_t sIdx);

		inline typename _map<uav_id, T*>::iterator begin() { return m_mItems.begin(); }
		inline typename _map<uav_id, T*>::iterator end()   { return m_mItems.end();   }
	};
	//-------------------------------------------------------------------------

	template <class T>
	uav_id TContainer<T>::insert(T* tItm)
	{
		uav_id ui_ret = UI_INVALID_ID;

		if(tItm)
		{
			ui_ret = tItm->id();
			m_mItems[ui_ret] = tItm;
		}

		return ui_ret;
	}
	//-------------------------------------------------------------------------

	template <class T>
	void TContainer<T>::erase(uav_id uiId)
	{
		typename _map<uav_id, T*>::iterator found = m_mItems.find(uiId);

		if(found != m_mItems.end())
			m_mItems.erase(found);
	}
	//-------------------------------------------------------------------------

	template <class T>
	void TContainer<T>::clear()
	{
		while(m_mItems.size())
			m_mItems.erase(m_mItems.begin());
	}
	//-------------------------------------------------------------------------

	template <class T>
	T* TContainer<T>::operator [](uav_id uiId)
	{
		typename _map<uav_id, T*>::iterator found = m_mItems.find(uiId);

		return found == m_mItems.end() ? NULL : found->second;
	}
	//-------------------------------------------------------------------------

	template <class T>
	T* TContainer<T>::operator [](size_t sIdx)
	{
		size_t ndx = 0;
		typename _map<uav_id, T*>::iterator iter = m_mItems.begin();

		while(iter != m_mItems.end() && ndx++ < sIdx)
			++iter;

		return iter == m_mItems.end() ? NULL : iter->second;
	}
	//-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------

typedef unsigned char uav_msg;

#define MSG_CMD_CONFIG		0x01
#define MSG_CMD_SET			0x02
#define MSG_CMD_LOG			0x03
//-----------------------------------------------------------------------------

#define DEV_BMP085			0x77	//-- Barometric pressure sensor (altimeter)
//-----------------------------------------------------------------------------
#endif /* UAV_DEFS_HPP_ */
//-----------------------------------------------------------------------------
