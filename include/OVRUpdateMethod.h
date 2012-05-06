/**
 *	UpdateMethod Class Definition
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

#ifndef OVERRATED_UPDATEMETHOD_H_DEFINED__
#define OVERRATED_UPDATEMETHOD_H_DEFINED__

#include "OVRUtils.h"
#include "assert.h"

namespace OverRated
{
	// Used to specify the two possible directions of change for a value
	enum ConstDirection
	{
		CD_INCREASING,
		CD_DECREASING
	};

	/**
	 *  Used by UpdatedValue's to decide how a value should respond to each update. Based on a
	 *  given rate, they move the value gradually on each update in the direction (+ or -) of a
	 *  given target, which is either a specific value or an infinite constant direction.
	 */
	template <typename T>
	class UpdateMethod
	{
	private:
		// The type of "target" this method has.
		enum TargetType
		{
			T_DIRECTION,	// Infinitely move in a constant direction
			T_VALUE			// Move towards a specific value
		};

	public:
		/**
		 *  Constructor for a directional target
		 *
		 *  @param rate     The rate of change (magnitude is used)
		 *  @param target   The constant direction to travel in
		 */
		UpdateMethod( const T & rate, OverRated::ConstDirection target )
		: mTargetType(T_DIRECTION), mTargetValue(0), mTargetDir(target), mRate(rate)
		{}

		/**
		 *  Constructor for a value target
		 *
		 *  @param rate     The rate of change (magnitude is used)
		 *  @param target   The value to try and reach
		 */
		UpdateMethod( const T & rate, const T & target )
		: mTargetType(T_VALUE), mTargetValue(target), mRate(rate)
		{}

		virtual ~UpdateMethod() {}

		/**
		 *  The rate may be changed at any time using this setter
		 *
		 *  @param rate  The new rate
		 */
		void setRate( const T & rate ) { mRate = OverRated::UtilAbs(rate); }

		/**
		 *  @return   The set rate
		 */
		T getRate() const { return mRate; }

		/**
		 *  @return   Whether the target of this method is a value
		 */
		bool getHasTargetValue() const
		{
			return mTargetType == T_VALUE;
		}

		/**
		 *  @return   Whether the target of this method is a direction
		 */
		bool getHasTargetDirection() const
		{
			return mTargetType == T_DIRECTION;
		}

		/**
		 *  @return   The value target. This is undefined if the target is directional.
		 */
		const T getTargetValue() const
		{
			return mTargetValue;
		}

		/**
		 *  @return   The directional target. This is undefined if the target is value-based.
		 */
		OverRated::ConstDirection getTargetDirection() const
		{
			return mTargetDir;
		}

		/**
		 *  Call with regular updates with a value to find out what it should be for the time
		 *  elapsed.
		 *
		 *  @param value        The value to update
		 *  @param timeElapsed  How much time has elapsed since last time, in seconds (1.0 = 1 sec)
		 *  @return             The value after updating
		 */
		T updateValue( const T & value, const double & timeElapsed )
		{
			T original( value );					// Copy of the original value
			OverRated::ConstDirection dir;			// Direction we'll change the value this time
			T result( 0.0 );						// The result to return
			T magnitude(getRate() * timeElapsed);	// The amount of change to apply (pos only)

			assert( getHasTargetDirection() || getHasTargetValue() );

			// Make the value legal
			_checkValue( original );

			result = original;

			// Get the target direction
			if( getHasTargetValue() )
				dir = _getBestDirection(value);
			else
				dir = getTargetDirection();

			// Apply the target direction
			if( dir == OverRated::CD_INCREASING )
				result += magnitude;
			else
				result -= magnitude;

			// Process the result
			if( getHasTargetValue() )
				_processResultForValueTarget(result, original, dir);
			else
				_processResultForDirectionalTarget( result, original, dir );

			return result;
		}

		/**
		 *  @return  Whether this is method has a target value AND has reached it.
		 */
		bool getIsFinished( const T & value ) const
		{
			assert( getHasTargetDirection() || getHasTargetValue() );

			if( getHasTargetDirection() )
				return false;
			else
				return value == getTargetValue();
		}

	protected:
		/**
		 *  Overload this if special checks are needed to see that the value is legal, and make
		 *  it legal directly if it isn't.
		 *
		 *  @param value   The value to check, passed by reference if in case it needs to change
		 */
		virtual void _checkValue( T & value ) {}

		/**
		 *  This must be overloaded to determine the best direction to go for target-based values.
		 *  Normally it will be the direction which most quickly brings the value to the target.
		 *
		 *  @return   The best direction
		 */
		virtual OverRated::ConstDirection _getBestDirection( const T & value ) = 0;

		/**
		 *  Overload this if special checks are needed to see that the result is legal, and make
		 *  it legal directly if it isn't. This one is called in the case of a value target.
		 *
		 *  @param result          The result to check, passed by reference so it can be changed
		 *  @param originalValue   The value prior to the update which created the result
		 *  @param dir             The direction that was used in the update
		 */
		virtual void _processResultForValueTarget( T & result, const T & originalValue,
				const OverRated::ConstDirection & dir ) {}

		/**
		 *  Overload this if special checks are needed to see that the result is legal, and make
		 *  it legal directly if it isn't. This one is called in the case of a directional target.
		 *
		 *  @param result          The result to check, passed by reference so it can be changed
		 *  @param originalValue   The value prior to the update which created the result
		 *  @param dir             The direction that was used in the update
		 */
		virtual void _processResultForDirectionalTarget( T & result, const T & originalValue,
				const OverRated::ConstDirection & dir ) {}

	private:
		const TargetType mTargetType;	// The type of target to use
		T mTargetValue;  				// If the target is a value, this is it
		ConstDirection mTargetDir;		// If the target is a direction, this is it
		T mRate;						// The rate of change
	};
}

#endif // OVERRATED_UPDATEMETHOD_H_DEFINED__
