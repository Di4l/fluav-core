/*
 * devices.hpp
 *
 *   Device (sensors, actuators...) declaration
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
 *  Created on: 29/07/2014
 *      Author: Raúl Hermoso Sánchez
 *      e-mail: raul.hermoso@gmail.com
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
