/**
 *	UpdateMethodLooped Class Definition
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

#ifndef OVERRATED_UPDATEMETHODLOOPED_H_DEFINED__
#define OVERRATED_UPDATEMETHODLOOPED_H_DEFINED__

#include "OVRUpdateMethod.h"

namespace OverRated
{
	/**
	 *  This method is designed to handle rotations, such as when 0 degrees comes after 360 and
	 *  vice versa. To use this class, you must set a minimum and maximum (like 0 and 360). The
	 *  shortest direction to reach the target is no longer as obvious as in the linear system.
	 */
	template<typename T>
	class UpdateMethodLooped: public OverRated::UpdateMethod<T>
	{
	public:
		/**
		 *  Constructor for a directional target
		 *
		 *  @param rate     The rate of change (magnitude is used)
		 *  @param target   The constant direction to travel in
		 *  @param min		Minimum of the looping range
		 *  @param max		Maximum of the looping range
		 */
		UpdateMethodLooped(const T & rate, OverRated::ConstDirection target,
				const T & min, const T & max)
		: OverRated::UpdateMethod<T>(rate, target), mOverrideEnabled(false), mMin(min), mMax(max)
		{
			assert(min < max);
		}

		/**
		 *  Constructor for a value target
		 *
		 *  @param rate     The rate of change (magnitude is used)
		 *  @param target   The value to try and reach
		 *  @param min      Minimum of the looping range
		 *  @param max      Maximum of the looping range
		 */
		UpdateMethodLooped(const T & rate, const T & target, const T & min,	const T & max)
		: OverRated::UpdateMethod<T>(rate, target), mOverrideEnabled(false), mMin(min), mMax(max)
		{
			assert(min < max);
		}

		/**
		 *  Constructor for a value target with a directional override. This means you want to
		 *  reach a certain value target, but you have a direction you want to rotate with, which
		 *  may or may not be the shortest route.
		 *
		 *  @param rate               The rate of change (magnitude is used)
		 *  @param target             The value to try and reach
		 *  @param directionOverride  The direction you want to force
		 *  @param min                Minimum of the looping range
		 *  @param max                Maximum of the looping range
		 */
		UpdateMethodLooped(const T & rate, const T & target,
				OverRated::ConstDirection directionOverride,
				const T & min,	const T & max)
		: OverRated::UpdateMethod<T>(rate, target), mOverrideEnabled(true),
		  mOverride(directionOverride), mMin(min), mMax(max)
		{
			assert(min < max);
		}

		/**
		 *  @return   Minimum value of the looped range
		 */
		T getMin() const
		{
			return mMin;
		}

		/**
		 *  @return   Maximum value of the looped range
		 */
		T getMax() const
		{
			return mMax;
		}

		/**
		 *  @return   Whether an override direction was supplied
		 */
		bool getIsOverrideEnabled() const
		{
			return mOverrideEnabled;
		}

		/**
		 *  @return   The override direction. Might not be defined ( @see getIsOverrideEnabled() )
		 */
		OverRated::ConstDirection getDirectionOverride() const
		{
			return mOverride;
		}

	private:
		/**
		 *  The best direction for this method requires us to consider how far it would be to the
		 *  target value in each direction and then pick the shortest. If an override was
		 *  supplied at construction, this will always return that instead.
		 *
		 *  @return   The best direction
		 */
		virtual OverRated::ConstDirection _getBestDirection(const T & value)
		{
			if (getIsOverrideEnabled())
				return getDirectionOverride();
			else {
				T target = OverRated::UpdateMethod<T>::getTargetValue();
				T forward_distance = OverRated::UtilDist(value, target);
				T backward_distance = OverRated::UtilDist(OverRated::UtilMin(value,	target),
						getMin()) + OverRated::UtilDist(OverRated::UtilMax(value, target),
						getMax());

				if (forward_distance <= backward_distance)
					return (value <= target) ? OverRated::CD_INCREASING : OverRated::CD_DECREASING;
				else
					return (value <= target) ? OverRated::CD_DECREASING	: OverRated::CD_INCREASING;
			}
		}

		/**
		 *	This is a more complex check which determines if we've passed the target; a check which
		 *	is contingent upon whether or not this update caused a loop (meaning the result passed
		 *  the minimum or max). Refer to function comments for details
		 *
		 *  @param result          The result to check, passed by reference so it can be changed
		 *  @param originalValue   The value prior to the update which created the result
		 *  @param dir             The direction that was used in the update
		 */
		void _processResultForValueTarget(T & result, const T & originalValue,
				const OverRated::ConstDirection & dir)
		{
			T target = OverRated::UpdateMethod<T>::getTargetValue();

			// If the result is still in the range, the only way the target could have been
			// passed is if it is between the original value and the result, much like the
			// linear method.
			if (OverRated::UtilRangeCheck(result, getMin(), getMax())) {
				if (OverRated::UtilRangeCheck(target, originalValue, result))
					result = target;
			}
			// if the result passed either bound of the range, it should loop. After looping,
			// the target is passed if it is between the bound we looped to and the final result.
			else {
				T marker = (result > getMax()) ? getMin() : getMax(); // The bound we looped to

				// Adjust the value
				_checkValue(result);

				if (OverRated::UtilRangeCheck(target, result, marker))
					result = target;
			}
		}

		/**
		 *  In the case of a directional target, this method will simply check the value
		 *
		 *  @param result          The result to check, passed by reference so it can be changed
		 *  @param originalValue   The value prior to the update which created the result
		 *  @param dir             The direction that was used in the update
		 */
		void _processResultForDirectionalTarget( T & result, const T & originalValue,
						const OverRated::ConstDirection & dir )
		{
			_checkValue(result);
		}

		/**
		 *	If the value has passed a bound of the range, it should loop around to the other and
		 *	also surpass it by the same magnitude that it exceeded the other.
		 */
		void _checkValue(T & value)
		{
			if (value > getMax())
				value = getMin() + (value - getMax());
			else if (value < getMin())
				value = getMax() + (value - getMin());

			// If the loop made it still go over a range, push it back to whichever is closest
			OverRated::UtilBindValueToRange(value, getMin(), getMax());
		}

	private:
		bool mOverrideEnabled; // Whether to use an override direction
		OverRated::ConstDirection mOverride; // If override is enabled, will always go this way
		T mMin; // Minimum of the range
		T mMax; // Maximum of the range
	};
}

#endif // OVERRATED_UPDATEMETHODLOOPED_H_DEFINED__
