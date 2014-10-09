/*
 * system.hpp
 *
 *   System declaration
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
 *  Created on: 04/09/2014
 *      Author: Raúl Hermoso Sánchez
 *      e-mail: raul.hermoso@gmail.com
 */

//-----------------------------------------------------------------------------
#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_
//-----------------------------------------------------------------------------
#include "uav_defs.hpp"
//-----------------------------------------------------------------------------

namespace nsUav
{
	//-------------------------------------------------------------------------

	class TSystem
	{
	private:
	protected:
	public:
		TSystem() {}
		virtual ~TSystem() {}

		virtual void configure(char* cParam) = 0;
	};
	//-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
#endif /* SYSTEM_HPP_ */
//-----------------------------------------------------------------------------
