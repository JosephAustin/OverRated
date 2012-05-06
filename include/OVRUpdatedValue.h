/**
 *	UpdatedValue Class Definition
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

#ifndef OVERRATED_UPDATEDVALUE_H_DEFINED__
#define OVERRATED_UPDATEDVALUE_H_DEFINED__

#include "OVRUpdatedObject.h"
#include "OVRUpdateMethod.h"

namespace OverRated
{
	/**
	 *  UpdatedObject which changes a single value over time. You must specify an UpdateMethod
	 *  before this can do anything meaningful ( @see setMethod() )
	 */
	template <typename T>
	class UpdatedValue : public OverRated::UpdatedObject
	{
	public:
		UpdatedValue() : mUpdateMethod(0) {}

		virtual ~UpdatedValue() {}

		/**
		 *  An updated value must overload this accessor for the changing value
		 *
		 *  @return   The value being updated, at its current state
		 */
		virtual T getValue() const = 0;

		/**
		 *  An updated value must overload this setter for the changing value
		 *
		 *  @param value   The value to apply
		 */
		virtual void setValue( const T & value ) = 0;

		/**
		 *  Set an UpdateMethod, which handles the way the value gets updated on each iteration.
		 *  NULL is a valid setting if you would like to detach the current method, rendering this
		 *  class useless until a new one is applied.
		 *
		 *  @param method   The UpdateMethod to use (must have the same template arguments as this)
		 */
		void setMethod( OverRated::UpdateMethod<T> * method )
		{
			mUpdateMethod = method;

			// Adjust any invalid initial setting
			_addTime(0.0);
		}

		/**
		 *  Simple accessor for the update method.
		 *
		 *  @return   The UpdateMethod assigned (warning: can be NULL!)
		 */
		OverRated::UpdateMethod<T> * getMethod() const
		{
			return mUpdateMethod;
		}

		/**
		 *  @returns   Whether or not this class is currently updating a value
		 */
		bool getIsUpdating() const
		{
			if( mUpdateMethod )
				return !mUpdateMethod->getIsFinished(getValue());

			return false;
		}

	private:
		/**
		 *  Add time in seconds to this object to update the value using the installed
		 *  UpdateMethod (if any)
		 *
   		 *  @param timeElapsed   The amount of time that has passed in seconds (1.0 = 1 sec)
		 */
		void _addTime( const double & timeElapsed )
		{
			if( getIsUpdating() )
				setValue( mUpdateMethod->updateValue( getValue(), timeElapsed ) );
		}

	private:
		OverRated::UpdateMethod<T> * mUpdateMethod;	// The method of updating the managed value
	};
}

#endif // OVERRATED_UPDATEDVALUE_H_DEFINED__
