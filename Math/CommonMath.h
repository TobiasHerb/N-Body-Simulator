/*
 * CommonMath.h
 *
 *  Created on: May 15, 2012
 *      Author: Tobias Herb
 */

#ifndef COMMONMATH_H_
#define COMMONMATH_H_

// includes.
#include <math.h>

namespace Math {

	class CommonMath {
	public:
		static const double PI;

		static double deg2rad( double a );

		static float deg2rad( float a );

		static double rad2deg( double a );

		static float rad2deg( float a );

		static double dmod( double x, double z );
	};
}

#endif /* COMMONMATH_H_ */
