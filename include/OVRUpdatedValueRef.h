/**
 *	UpdatedValueRef Class Definition
 *
 *	@author  	Joseph Austin ( joseph.the.austin@gmail.com )
 *
 *	@license	Copyright (c) 2011 Joseph Austin
 *
 *				Permission is hereby granted, free of charge, to any person obtaining a copy
 *				of this software and associated documentation files (the "Software"), to deal
 *				in the Software without restriction, including without limitation the rights
 *				to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *				copies of the Software, and to permit persons to whom the Software is
 *				furnished to do so, subject to the following conditions:
 *
 *				The above copyright notice and this permission notice shall be included in
 *				all copies or substantial portions of the Software.
 *
 *				THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *				IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *				FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *				AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *				LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *				OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *				THE SOFTWARE.
 */

#ifndef OVERRATED_UPDATEDVALUEREF_H_DEFINED__
#define OVERRATED_UPDATEDVALUEREF_H_DEFINED__

#include "OVRUpdatedValue.h"

namespace OverRated
{
	/**
	 *  This is almost the same as the basic updated value, except that instead of storing its
	 *  own variable, it influences an existing one by reference. Note that this isn't the only
	 *  way to directly affect your own value. You can also roll your own and overload the getter
	 *  and setter methods as needed.
	 */
	template <typename T>
	class UpdatedValueRef : public OverRated::UpdatedValue<T>
	{
	public:
		/**
		 *  Constructor
		 *
		 *  @param initValue	Initializes the data value updated by this class
		 */
		UpdatedValueRef( T & value )
		: mVar(value)
		{}

		/**
		 *  Getter for the value; required of the UpdatedValue template.
		 *
		 *  @return   The value being updated at its current state
		 */
		T getValue() const
		{
			return mVar;
		}

		/**
		 *  Setter for the value; required of the UpdatedValue template.
		 *
		 *  @param value   The new value being set
		 */
		void setValue(const T & value)
		{
			mVar = value;
		}

	private:
		T & mVar;	// The referenced, updated value
	};
}

#endif // OVERRATED_UPDATEDVALUEREF_H_DEFINED__
