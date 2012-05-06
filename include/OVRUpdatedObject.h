/**
 *	UpdatedObject Class Definition
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

#ifndef OVERRATED_UPDATEDOBJECT_H_DEFINED__
#define OVERRATED_UPDATEDOBJECT_H_DEFINED__

namespace OverRated
{
	/**
	 *  Any class that needs to receive regular time updates. Updates are ignored if the instance
	 *  is 'paused'. That is the only thing abstracted at this level. For now at least, this
	 *  exists so that UpdatedValue can subclass it.
	 */
	class UpdatedObject
	{
	public:
		UpdatedObject()
		: mIsPaused( false )
		{}

		virtual ~UpdatedObject()
		{}

		/**
		 *  If unpaused, add the elapsed time in seconds
		 *
		 *  @param timeElapsed   Amount of time that has passed in seconds (1.0 = 1 sec)
		 */
		void addTime( double timeElapsed )
		{
			if( !getIsPaused() )
				_addTime( timeElapsed );
		}

		/**
		 *  Getter for the paused state
		 *
		 *  @return   The pause state
		 */
		bool getIsPaused() const
		{
			return mIsPaused;
		}

		/**
		 *  Setter for the paused state
		 *
		 *  @param paused   Whether to pause(true) or unpause(false)
		 */
		void setIsPaused( bool paused )
		{
			mIsPaused = paused;
		}

	protected:
		/**
		 *  This function determines how we want to respond to time updates
		 *
  		 *  @param timeElapsed   Amount of time that has passed in seconds (1.0 = 1 sec)
		 */
		virtual void _addTime( const double & timeElapsed ) = 0;

	private:
		bool mIsPaused;	// Whether this object is paused
	};
}

#endif // OVERRATED_UPDATEDOBJECT_H_DEFINED__
