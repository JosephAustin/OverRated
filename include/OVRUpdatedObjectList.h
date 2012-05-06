/**
 *	UpdatedObjectList Class Definition
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

#ifndef OVERRATED_UPDATEDOBJECTLIST_H_DEFINED__
#define OVERRATED_UPDATEDOBJECTLIST_H_DEFINED__

#include <vector>

#include "OVRUpdatedObject.h"

namespace OverRated
{
	/**
	 *  A container which allows you to update a list of UpdatedObject's in one shot. Caller must
	 *  supply the full type of the UpdatedObject via a template argument, as with most standard
	 *  lists. The argument should always be an UpdatedObject or a subclass of it.
	 *
	 *  Example: UpdatedObjectList< UpdatedValue<double> >
	 */
	template <typename T>
	class UpdatedObjectList : public OverRated::UpdatedObject
	{
	public:
		/**
		 *  Adds a new item to the list
		 *
		 *  @param newItem  The item to add
		 */
		void add( T * newItem )
		{
			if( !contains(newItem) )
				mList.push_back(newItem);
		}

		/**
		 *  Removes an existing item from the list (if it is actually there)
		 *
		 *  @param item   The item to remove
		 */
		void remove( T * item )
		{
			for( unsigned i = 0; i < mList.size(); i++ ) {
				if( mList[i] == item ) {
					mList.erase( mList.begin() + i);
					return;
				}
			}
		}

		/**
		 *  Clears the list without deleting anything
		 */
		void clear()
		{
			mList.clear();
		}

		/**
		 *  Accessor
		 *
		 *  @param index   Index of the desired item to access
		 *  @return        The desired item
		 */
		T * getItem( unsigned index ) const
		{
			return mList[index];
		}

		/**
		 *  Returns the size of the list
		 *
		 *  @return   Unsigned integer stating number of items in the container
		 */
		unsigned getSize() const
		{
			return mList.size();
		}

		/**
		 *  Returns whether or not the list currently contains an item
		 *
		 *  @param item   The item to query the list for
		 *  @return       Whether the item currently exists in this container
		 */
		bool contains( const T * item )
		{
			for( unsigned i = 0; i < mList.size(); i++ ) {
				if( mList[i] == item )
					return true;
			}
			return false;
		}

	private:
		/**
		 *  When time is added, update every item in the list.
		 *
		 *  @param timeElapsed   The time elapsed since last time; normally, in seconds
		 */
		void _addTime( const double & timeElapsed )
		{
			for( unsigned i = 0; i < mList.size(); i++ )
				mList[i]->addTime(timeElapsed);
		}

	private:
		std::vector<T*> mList;	// The updated items
	};
}

#endif // OVERRATED_UPDATEDOBJECTLIST_H_DEFINED__
