/**
 *	UpdatedValueBasic Class Definition
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

#ifndef OVERRATED_UPDATEDVALUEBASIC_H_DEFINED__
#define OVERRATED_UPDATEDVALUEBASIC_H_DEFINED__

#include "OVRUpdatedValue.h"

namespace OverRated
{
	/**
	 *  This type of updated value stores its own copy of the value type and updates it directly.
	 */
	template <typename T>
	class UpdatedValueBasic : public OverRated::UpdatedValue<T>
	{
	public:
		/**
		 *  Constructor
		 *
		 *  @param initValue   Initializes the data value updated by this class
		 */
		UpdatedValueBasic( const T & initValue )
		{
			mVar = initValue;
		}

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
		T mVar;	// The contained, updated value
	};
}

#endif // OVERRATED_UPDATEDVALUEBASIC_H_DEFINED__
