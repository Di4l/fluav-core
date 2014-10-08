/*
 * devices.hpp
 *
 *  Created on: 29/07/2014
 *      Author: rhermoso
 */

//-----------------------------------------------------------------------------
#ifndef DEVICES_HPP_
#define DEVICES_HPP_
//-----------------------------------------------------------------------------
#include "uav_defs.hpp"
//-----------------------------------------------------------------------------
#define DEV_FAMILY_SENSOR		0x00
#define DEV_FAMILY_ACTUATOR		0x80

#define DEV_KIND_SERVO			0x01
#define DEV_KIND_DISCRETE		0x02
#define DEV_KIND_ANALOG			0x03

#define DEV_FAMILY_MASK			0x80
#define DEV_KIND_MASK			0x7f
//-----------------------------------------------------------------------------

namespace nsUav
{
	//-------------------------------------------------------------------------

	class TDevice : public TObject
	{
	private:
		uav_id     m_uiKind;
		uav_value  m_sMin;
		uav_value  m_sMax;
		uav_uvalue m_usLast;
		uav_uvalue m_usValue;

	protected:
	public:
		TDevice(uav_id uiId);
		virtual ~TDevice() {}

		inline uav_id&     kind()    { return m_uiKind;  }
		inline uav_value&  minimum() { return m_sMin;    }
		inline uav_value&  maximum() { return m_sMax;    }
		inline uav_uvalue& value()   { return m_usValue; }

		bool modified();
	};
	//-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
extern nsUav::TContainer<nsUav::TDevice> Devices;
//-----------------------------------------------------------------------------
#endif /* DEVICES_HPP_ */
//-----------------------------------------------------------------------------
