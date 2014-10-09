/*
 * ard_defs.hpp
 *
 *   Common definitions for the Arduino
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
 *  Created on: 09/09/2014
 *      Author: Raúl Hermoso Sánchez
 *      e-mail: raul.hermoso@gmail.com
 */

//-----------------------------------------------------------------------------
#ifndef ARD_DEFS_HPP_
#define ARD_DEFS_HPP_
//-----------------------------------------------------------------------------
#ifdef ARDUINO
//-----------------------------------------------------------------------------
#include "Arduino.h"
//-----------------------------------------------------------------------------
#define ARD_MAX_ELEMENT_COUNT	24
#define INVALID_INDEX			ARD_MAX_ELEMENT_COUNT

#define _map	ard::map
//-----------------------------------------------------------------------------

/* Lets fake the stl map class so that the it can be used in AVR. We shall do
 * it in a very different way and will try NOT to mimic the stl map class. It
 * will only provide the methods we will be using and its internal
 * implementation be simpler.
 */
namespace ard
{
	//-------------------------------------------------------------------------

	template <class T1, class T2>
	struct pair
	{
		typedef pair<T1, T2>& reference;

		T1 first;
		T2 second;

		pair() : first(0), second(0) { }
		pair(const T1& fst, const T2& scnd) : first(fst), second(scnd) {}

		inline bool operator ==(reference ref) { return first == ref.first; }
		inline bool operator !=(reference ref) { return first != ref.first; }
		inline bool operator <(reference ref)  { return first < ref.first;  }
		inline bool operator >(reference ref)  { return first > ref.first;  }
		inline bool operator <=(reference ref) { return first <= ref.first; }
		inline bool operator >=(reference ref) { return first >= ref.first; }
	};
	//-------------------------------------------------------------------------

	template <class T1, class T2>
	inline pair<T1, T2> make_pair(const T1& x, const T2& y)
	{
		return pair<T1, T2>(x, y);
	}
	//-------------------------------------------------------------------------






	typedef unsigned char at_index;
	struct _iterator_base
	{
		at_index index;

		_iterator_base() : index(0) {}

		inline void next() { ++index; }
		inline void prev() { --index; }
	};
	//-------------------------------------------------------------------------

	template <class T>
	struct _iterator : public _iterator_base
	{
		typedef _iterator<T> _self;

		T* addr;

		_iterator() : addr(0) {}
		_iterator(T& x) : addr(0) { addr = &x; }
		_iterator(T* x) : addr(0) { addr = x; }
		_iterator(const _self& it) : addr(0) { addr = it.addr; index = it.index; }

		T& operator *()  { return addr[index]; }
		T* operator ->() { return &addr[index]; }

		_self& operator ++()    { next(); return *this; }
		_self  operator ++(int) { _self tmp = *this; next(); return tmp; }

		_self& operator --()    { prev(); return *this; }
		_self  operator --(int) { _self tmp = *this; prev(); return tmp; }
	};
	//-------------------------------------------------------------------------

	template <class T>
	inline bool operator ==(const T& x, const T& y)
	{
		return x == y;
	}
	//-------------------------------------------------------------------------

	template <class T>
	inline bool operator !=(const T& x, const T& y)
	{
		return x != y;
	}
	//-------------------------------------------------------------------------






	template <class TKey, class TDat>
	class map
	{
	private:
		size_t m_size;
		pair<TKey, TDat>* m_begin;
		pair<TKey, TDat>* m_end;
		pair<TKey, TDat>  m_array[ARD_MAX_ELEMENT_COUNT];

	protected:
	public:
		map() : m_size(0), m_begin(m_array), m_end(&m_array[ARD_MAX_ELEMENT_COUNT]) {}

		typedef _iterator<pair<TKey, TDat> > iterator;

		inline size_t size() { return m_size; }

		iterator begin() { return iterator(m_begin); }
		iterator end()   { return iterator(m_end); }

		iterator find(TKey key);
		void erase(iterator it);

		TDat& operator [](TKey key);
	};
	//-------------------------------------------------------------------------

	template <class TKey, class TDat>
	typename map<TKey, TDat>::iterator map<TKey, TDat>::find(TKey key)
	{
		typename map<TKey, TDat>::iterator found = begin();

		for(size_t i = 0; i < m_size; ++i)
		{
			if(m_array[i].first == key)
			{
				found.index = i;
				return found;
			}
		}

		return end();
	}
	//-------------------------------------------------------------------------

	template <class TKey, class TDat>
	void map<TKey, TDat>::erase(map<TKey, TDat>::iterator it)
	{
		if(it != end())
		{
			it->first  = 0;
			it->second = 0;

			--m_size;
		}
	}
	//-------------------------------------------------------------------------

	template <class TKey, class TDat>
	TDat& map<TKey, TDat>::operator [](TKey key)
	{
		at_index i;
		for(i = 0; m_array[i].first != 0 && i < ARD_MAX_ELEMENT_COUNT; ++i)
		{
			if(m_array[i].first == key)
			{
				if(m_array[i].second == 0)
					m_array[i].second = TDat();

				return m_array[i].second;
			}
		}

		//-- If we reach this point, there is no element in the map that
		//   has the desired key, we must initialize it and return it

		if(i == INVALID_INDEX)
		{
			//-- we've reached the maximum number of elements that can be
			//   allocated in the map... we should throw an error of some sort
		}

		m_array[i].first  = key;
		m_array[i].second = TDat();

		return m_array[i].second;
	}
	//-------------------------------------------------------------------------




	template <class T>
	class vector
	{
		size_t m_size;
		T* m_begin;
		T* m_end;
		T  m_array[ARD_MAX_ELEMENT_COUNT];

	protected:
	public:
		vector() : m_size(0), m_begin(m_array), m_end(&m_array[ARD_MAX_ELEMENT_COUNT]) {}

		typedef _iterator<T> iterator;

		inline size_t size() { return m_size; }

		iterator begin() { return iterator(m_begin); }
		iterator end()   { return iterator(m_end); }

		iterator find(T value);
		void erase(iterator it);

		inline T&   operator [](at_index indx) { return m_array[indx];      }
		inline void push_back(T Value)         { m_array[m_size++] = Value; }
		inline T    pop_back()                 { return m_array[--m_size];  }
	};
	//-------------------------------------------------------------------------

	template <class T>
	typename vector<T>::iterator vector<T>::find(T value)
	{
		typename vector<T>::iterator found = begin();

		for(size_t i = 0; i < m_size; ++i)
		{
			if(m_array[i] == value)
			{
				found.index = i;
				return found;
			}
		}

		return end();
	}
	//-------------------------------------------------------------------------

	template <class T>
	void vector<T>::erase(vector<T>::iterator it)
	{
		if(it != end())
		{
			if(it.index < m_size)
				m_array[it.indx] = 0;

			for(at_index i = it.indx; i < m_size; ++i)
				m_array[i] = ((i + 1) == INVALID_INDEX) ? 0 :m_array[i + 1];

			--m_size;
		}
	}
	//-------------------------------------------------------------------------
} // namespace std
//-----------------------------------------------------------------------------

#endif /* ARDUINO */
#endif /* ARD_DEFS_HPP_ */
//-----------------------------------------------------------------------------
