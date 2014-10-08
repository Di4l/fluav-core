/*
 * interface.hpp
 *
 *  Created on: 29/07/2014
 *      Author: rhermoso
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
