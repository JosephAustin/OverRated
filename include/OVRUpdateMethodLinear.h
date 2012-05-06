/**
 *	UpdateMethodLinear Class Definition
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

#ifndef OVERRATED_UPDATEMETHODLINEAR_H_DEFINED__
#define OVERRATED_UPDATEMETHODLINEAR_H_DEFINED__

#include "OVRUpdateMethod.h"

namespace OverRated
{
	/**
	 *	This is the most commonplace update method. It works on a linear number model where values
	 *	can go infinitely in both positive and negative directions. This contrasts with the looped
	 *  method, in which there is a range where one end leads to the other and vice versa.
	 */
	template <typename T>
	class UpdateMethodLinear : public OverRated::UpdateMethod<T>
	{
	public:
		/*
		 *  Constructor for a directional target
		 *
		 *  @param rate     The rate of change (magnitude is used)
		 *  @param target   The constant direction to travel in
		 */
		UpdateMethodLinear( const T & rate, OverRated::ConstDirection target )
		: OverRated::UpdateMethod<T>(rate, target)
		{}

		/**
		 *  Constructor for a value target
		 *
		 *  @param rate     The rate of change (magnitude is used)
		 *  @param target   The value to try and reach
		 */
		UpdateMethodLinear( const T & rate, const T & target )
		: OverRated::UpdateMethod<T>(rate, target)
		{}

	private:
		/**
		 *  The best direction for this method is easy; increase if the target's greater,
		 *  decrease if it's less. There is only one right direction.
		 *
		 *  @return   The best direction
		 */
		OverRated::ConstDirection _getBestDirection( const T & value )
		{
			if( OverRated::UpdateMethod<T>::getTargetValue() > value )
				return OverRated::CD_INCREASING;
			else
				return OverRated::CD_DECREASING;
		}

		/**
		 *  If there is a targeted value, we must check that we didn't pass over it. If we did, the
		 *  result needs to be reverted to the target instead.
		 *
		 *  @param result          The result to check, passed by reference so it can be changed
		 *  @param originalValue   The value prior to the update which created the result
		 *  @param dir             The direction that was used in the update
		 */
		void _processResultForValueTarget( T & result, const T & originalValue,
				const OverRated::ConstDirection & )
		{
			T target = OverRated::UpdateMethod<T>::getTargetValue();

			if( OverRated::UtilRangeCheck(target, originalValue, result) )
				result = target;
		}
	};
}

#endif // OVERRATED_UPDATEMETHODLINEAR_H_DEFINED__
