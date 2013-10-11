/*
 * CommonMath.cpp
 *
 *  Created on: May 16, 2012
 *      Author: Tobias Herb
 */

// includes.
#include "CommonMath.h"

namespace Math {

	const double CommonMath::PI = 3.14159265;

	double CommonMath::deg2rad( double a ) {
		return ( a * ( PI / 180.0 ) );
	}

	float CommonMath::deg2rad( float a ) {
		return ( a * ( PI / 180.0 ) );
	}

	double CommonMath::rad2deg( double a ) {
		return a * ( 180 / PI );
	}

	float CommonMath::rad2deg( float a ) {
		return a * ( 180 / PI );
	}

	double CommonMath::dmod( double x, double z ) {
		return ( ( x / z ) - ( (int)( x / z ) ) ) * z;
	}
}
