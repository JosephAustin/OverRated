/**
 *	OverRated Example
 *
 *	@author  	Joseph Austin ( joseph.the.austin@gmail.com )
 *
 *	@license	This example is released in the public domain, which shall not extend to the actual
 *				OverRated library. OverRated is released under the liberal but more specific MIT
 *				license, as is detailed in each of its headers.
 */

#include <stdio.h>
#include <iostream>
#include <OverRated.h>

// -----------------------------------------------------------------------------------------------
// WARNING: if you change anything, expect inconsistency. This isn't beautiful flexible code, it's
// a tutorial :)
// -----------------------------------------------------------------------------------------------


// Welcome to an OverRated tutorial program (see what I did there?) We're going to use this library
// to do some stuff to numbers. Fun times.

using namespace OverRated;

int main()
{
	// OverRated is meant to abstract value changes across regular time updates. Normally,
	// updates will come in from some sort of loop, potentially running in a thread. However,
	// for the purposes of our tutorial we're going to apply fake updates manually so that the
	// results will be good and predictable.

	double local_number = 1.0;
	UpdatedValueBasic<double> basic_updater(1.0);
	UpdatedValueRef<double> ref_updater(local_number);

	// Both Updaters above are legal. The only difference is that we can access local_number
	// in this scope while for basic_updater, we have to use a getter function. They can both be
	// updated at once using a list:

	UpdatedObjectList< UpdatedValue<double> > update_list;
	update_list.add(&basic_updater);
	update_list.add(&ref_updater);

	// Update the list, you update everything at once. Well, actually, nothing will update at
	// all yet because there are no UpdateMethods installed. I'll even prove it...

	update_list.addTime(50.0);
	assert( local_number == 1.0 );
	assert( basic_updater.getValue() == 1.0 );

	// So, updateMethods are the way this library really does the job. We'll use the linear method,
	// as that is the most typical. You might want to view the looped method's header for info on
	// how to use that as well. And of course, you can always create your own.

	// First, an increasing method for both updaters

	UpdateMethodLinear<double> increaser(0.5, CD_INCREASING);
	basic_updater.setMethod(&increaser);
	ref_updater.setMethod(&increaser);

	printf( ">> TEST 1: Increasing method with a rate of 0.5 <<\n" );
	printf( "Accessed value:\t %f\n", basic_updater.getValue() );
	printf( "Local value:\t %f\n", local_number );
	printf( "... Updating by 5 seconds ...\n");
	update_list.addTime(5.0);
	printf( "Accessed value:\t %f\n", basic_updater.getValue() );
	printf( "Local value:\t %f\n", local_number );
	printf( ">> Expected: 3.5 for each <<\n\n");

	// Next, we'll change just one of the two updaters to use a decreasing method.
	UpdateMethodLinear<double> decreaser(0.5, CD_DECREASING);
	ref_updater.setMethod(&decreaser);

	printf( ">> TEST 2: Local (referenced) value will be decreased this time  <<\n" );
	printf( "Accessed value:\t %f\n", basic_updater.getValue() );
	printf( "Local value:\t %f\n", local_number );
	printf( "... Updating by 5 seconds ...\n");
	update_list.addTime(5.0);
	printf( "Accessed value:\t %f\n", basic_updater.getValue() );
	printf( "Local value:\t %f\n", local_number );
	printf( ">> Expected: 6.0 and 1.0 <<\n\n");

	// Increasing and Decreasing linear updates will move infinitely in the expected direction.
	// If you use the other constructor for your UpdateMethod, however, you can set a specific
	// numerical goal.

	// Update towards 10... with a faster rate, too
	UpdateMethodLinear<double> changer(1.0, 10.0);

	basic_updater.setMethod(&changer);
	ref_updater.setMethod(&changer);

	printf( ">> TEST 3: Using targets. Both values updated toward 10.0 by 1.0 rate <<\n" );
	printf( "Accessed value:\t %f\n", basic_updater.getValue() );
	printf( "Local value:\t %f\n", local_number );
	for( int i = 0; i < 3; i++ )
	{
		printf( "... Updating by 3 seconds ...\n");
		update_list.addTime(3.0);
		printf( "Accessed value:\t %f\n", basic_updater.getValue() );
		printf( "Local value:\t %f\n", local_number );
	}
	printf( ">> Expected: Both moved towards 10.0 and never passed it <<\n\n");

	// Neither value went beyond the number targeted. They both stop neatly at 10, as ordered.
	// In a linear system, the value will always INCREASE by the rate if the target is higher, and
	// DECREASE by the rate if it is lower. Again, you may want to look at how the looped method
	// works if you're, say, dealing with rotations.

	// This concludes the OverRated tutorial. I hope you found it useful. Good luck and thanks for
	// checking out the library!

	std::cin.ignore();
}

