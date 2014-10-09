/*
 * devices.cpp
 *
 *   Definition of a device (sensor,a ctuator) in fluav
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
#include "devices.hpp"
//-----------------------------------------------------------------------------
using namespace nsUav;
//-----------------------------------------------------------------------------
TContainer<TDevice> Devices;
//-----------------------------------------------------------------------------

TDevice::TDevice(uav_id uiId) : TObject(uiId)
{
	m_uiKind  = UI_INVALID_ID;
	m_sMin    = 0;
	m_sMax    = 0;
	m_usLast  = 0;
	m_usValue = 0;
}
//-----------------------------------------------------------------------------

bool TDevice::modified()
{
	bool b_ret = m_usLast != m_usValue;
	m_usLast = m_usValue;
	return b_ret;
}
//-----------------------------------------------------------------------------

