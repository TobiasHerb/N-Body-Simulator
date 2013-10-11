/*
 * Point3D.h
 *
 *  Created on: May 16, 2012
 *      Author: Tobias Herb
 */

#ifndef POINT3D_H_
#define POINT3D_H_

// includes.
#include "Vector3D.h"
#include <string>
#include <sstream>

namespace Math {

	template<typename T> class Point3D {
	public:
		Point3D() {
			this->x = 0;
			this->y = 0;
		}

		Point3D( const T x, const T y ) {
			this->x = x;
			this->y = y;
		}

		Point3D( const Point3D<T>& p ) {
			this->x = p.x;
			this->y = p.y;
		}

		Point3D( const Vector3D<T>& v ) {
			this->x = v.X();
			this->y = v.Y();
		}

	private:
		T x;
		T y;
		T z;

	public:
		Point3D<T>& operator=( const Point3D<T>& p ) {
			this->x = p.x;
			this->y = p.y;
			this->z = p.z;
			return (*this);
		}

		Point3D<T> operator+( const Vector3D<T>& v ) const {
			Point3D<T> r( this->x + v.X(),
					 	  this->y + v.Y(),
					 	  this->z + v.Z() );
			return r;
		}

		Point3D<T> operator-( const Vector3D<T>& v ) const {
			Point3D<T> r( this->x - v.X(),
						  this->y - v.Y(),
						  this->z - v.Z() );
			return r;
		}

		Point3D<T> operator+=( const Vector3D<T>& v ) {
			this->x += v.X();
			this->y += v.Y();
			this->z += v.Z();
			return (*this);
		}

		Point3D<T> operator-=( const Vector3D<T>& v ) {
			this->x -= v.X();
			this->y -= v.Y();
			this->z -= v.Z();
			return (*this);
		}

		Vector3D<T> getPositionVector() const {
			Vector3D<T> v( this->x, this->y, this->z );
			return v;
		}

		T X() const {
			return this->x;
		}

		T Y() const {
			return this->y;
		}

		T Z() const {
			return this->z;
		}

		std::string toString() const {
			std::stringstream ss;
			ss << "(" << this->x << ","
					  << this->y << ","
					  << this->z << ")";
			return ss.str();
		}

		bool operator==( const Point3D<T>& v ) const {
			if( this == &v )
				return true;
			if( this->x == v.x &&
				this->y == v.y &&
				this->z == v.z ) {
				return true;
			}
			// TODO: fulfills not exact equals contract...
			return false;
		}
	};
}

#endif /* POINT3D_H_ */
