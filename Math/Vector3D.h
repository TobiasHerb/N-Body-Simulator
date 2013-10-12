/*
 * Vector3D.h
 *
 *  Created on: May 15, 2012
 *      Author: Tobias Herb
 */

#ifndef VECTOR3D_H_
#define VECTOR3D_H_

// includes.
#include <string>
#include <sstream>
#include <cmath>

namespace Math {

	template<typename T> class Vector3D {
	public:
		Vector3D() {
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		Vector3D( const T x, const T y, const T z ) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3D( const Vector3D<T>& v ) {
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
		}

	private:
		T x;
		T y;
		T z;

	public:
		Vector3D<T>& operator=( const Vector3D<T>& v ) {
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			return (*this);
		}

		Vector3D<T> operator+( const Vector3D<T>& v ) const {
			Vector3D<T> r( this->x + v.x,
				       this->y + v.y,
				       this->z + v.z );
			return r;
		}

		Vector3D<T> operator-( const Vector3D<T>& v ) const {
			Vector3D<T> r( this->x - v.x,
				       this->y - v.y,
				       this->z - v.z );
			return r;
		}

		Vector3D<T> operator*( const T val ) const {
			Vector3D<T> r( this->x * val,
				       this->y * val,
				       this->z * val );
			return r;
		}

		Vector3D<T> operator/( const T val ) const {
			T reciprocalVal = 1 / val;
			Vector3D<T> r( this->x * reciprocalVal,
				       this->y * reciprocalVal,
				       this->z * reciprocalVal );
			return r;
		}

		Vector3D<T>& operator+=( const Vector3D<T>& v ) {
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;
			return (*this);
		}

		Vector3D<T>& operator-=( const Vector3D<T>& v ) {
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;
			return (*this);
		}

		Vector3D<T>& operator*=( const T val ) {
			this->x *= val;
			this->y *= val;
			this->z *= val;
			return (*this);
		}

		Vector3D<T>& operator/=( const T val ) {
			T reciprocalVal = 1 / val;
			this->x *= reciprocalVal;
			this->y *= reciprocalVal;
			this->z *= reciprocalVal;
			return (*this);
		}

		T length() const {
			return sqrt( ( this->x * this->x ) +
				     ( this->y * this->y ) +
				     ( this->z * this->z ) );
		}

		Vector3D<T> normalize() const {
			return ( (*this) / length() );
		}

		float operator*( const Vector3D<T> v ) const {
			return ( this->x * v.X() +
				 this->y * v.Y() +
				 this->z * v.Z() );
		}

		Vector3D<T> cross( const Vector3D<T>& v ) {
			Vector3D<T> r( this->y * v.Z() - this->z * v.Y(),
				       this->z * v.X() - this->x * v.Z(),
				       this->x * v.Y() - this->y * v.X() );
			return r;
		}

		inline T X() const {
			return this->x;
		}

		inline T Y() const {
			return this->y;
		}

		inline T Z() const {
			return this->z;
		}

		Vector3D<T>& set( const T x, const T y, const T z ) {
			this->x = x;
			this->y = y;
			this->z = z;
			return (*this);
		}

		Vector3D<T>& set( const Vector3D<T>& v ) {
			this->x = v.X();
			this->y = v.Y();
			this->z = v.Z();
			return (*this);
		}

		std::string toString() const {
			std::stringstream ss;
			ss << "[" << this->x << ","
			          << this->y << ","
			          << this->z << "]";
			return ss.str();
		}

		bool operator==( const Vector3D<T>& v ) const {
			if( this == &v )
				return true;
			if( this->x == v.x && this->y == v.y && this->z == v.z ) {
				return true;
			}
			// TODO: fulfills not exact equals contract...
			return false;
		}
	};
}

#endif /* VECTOR3D_H_ */
