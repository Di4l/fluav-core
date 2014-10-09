/*
 * interface.hpp
 *
 *   Interface declaration
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
#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_
//-----------------------------------------------------------------------------
#include "devices.hpp"
//-----------------------------------------------------------------------------

namespace nsUav
{
	//-------------------------------------------------------------------------

	class TInterface : public TObject
	{
	private:
		uav_id m_uiKind;

	protected:
		TContainer<TDevice> m_mDevices;

	public:
		TInterface(uav_id uiId, uav_id uiKnd) : TObject(uiId), m_uiKind(uiKnd) {}
		virtual ~TInterface() {}

		inline uav_id kind() { return m_uiKind; }

		inline TContainer<TDevice>& devices() { return m_mDevices; }

		virtual bool connect(void* cParam) = 0;
		virtual void disconnect() = 0;

		virtual void read()  = 0;
		virtual void write() = 0;
	};
	//-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
extern  nsUav::TContainer<nsUav::TInterface> Interfaces;
//-----------------------------------------------------------------------------
#endif /* INTERFACE_HPP_ */
//-----------------------------------------------------------------------------
