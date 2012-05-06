/**
 *	Utility Functions
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

#ifndef OVERRATED_UTILS_H_DEFINED__
#define OVERRATED_UTILS_H_DEFINED__

// This header defines some utility functions meant to make life a little easier for the OverRated
// classes. I wanted to reduce dependency on even STD since the UpdatedValue class operates on a
// template and therefore nothing can be assumed about the manipulated value except that certain
// operators are valid.

namespace OverRated
{
	/**
	 *  Utility function to determine the maximum of two values
	 *
	 *  @param first    First value, order is unimportant
	 *  @param second   Second value, order is unimportant
	 *  @return         Maximum of the values
	 */
	template <typename T>
	T UtilMax( const T & first, const T & second )
	{
		if( first > second )
			return first;
		else
			return second;
	}

	/**
	 *  Utility function to determine the minimum of two values
	 *
	 *  @param first    First value, order is unimportant
	 *  @param second   Second value, order is unimportant
	 *  @return         Minimum of the values
	 */
	template <typename T>
	T UtilMin( const T & first, const T & second )
	{
		if( first <= second )
			return first;
		else
			return second;
	}

	/**
	 *  Utility function to determine both the minimum and maximum from two of values
	 *
	 *  @param first	First value, order is unimportant
	 *  @param second	Second value, order is unimportant
	 *  @param min		Holds the minimum value, passed back by reference
	 *  @param max		Holds the maximum value, passed back by reference
	 */
	template <typename T>
	void UtilMinMax( const T & first, const T & second, T & min, T & max )
	{
		if( first <= second )
		{
			min = first;
			max = second;
		}
		else
		{
			min = second;
			max = first;
		}
	}

	/**
	 *  Utility function to determine the linear distance between two values
	 *
	 *  @param first    First value, order is unimportant
	 *  @param second   Second value, order is unimportant
	 *  @return         Distance between first and second
	 */
	template <typename T>
	T UtilDist( const T & first, const T & second )
	{
		return OverRated::UtilMax(first,second) - OverRated::UtilMin(first, second);
	}

	/**
	 *  Utility function to determine if a value is between two other values
	 *
	 *  @param value    The value to check
	 *  @param first    First range value, order is unimportant
	 *  @param second   Second range value, order is unimportant
	 *
	 *  @return         Whether value is between first and second
	 */
	template <typename T>
	bool UtilRangeCheck( const T & value, const T & first, const T & second )
	{
		return (value <= OverRated::UtilMax(first,second)) &&
			   (value >= OverRated::UtilMin(first,second));
	}

	/**
	 *  Utility function which binds a value within a range. So if the value is outside the range,
	 *  it will be pushed back in to the nearest boundary
	 *
	 *  @param value    The value to check
	 *  @param first    First range value, order is unimportant
	 *  @param second   Second range value, order is unimportant
	 */
	template <typename T>
	void UtilBindValueToRange( T & value, const T & first, const T & second )
	{
		T min, max;

		OverRated::UtilMinMax( first, second, min, max );

		if( value > max )
			value = max;
		else if( value < min )
			value = min;
	}

	/**
	 *  Utility function which returns an absolute value without using std::abs
	 *
	 *  @param value   Value to get the absolute for
	 *
	 *  @return        Absolute value of 'value'
	 */
	template <typename T>
	T UtilAbs( const T & value )
	{
		if( value < 0 )
			return value * (-1);
		else
			return value;
	}
}

#endif // OVERRATED_UTILS_H_DEFINED__
