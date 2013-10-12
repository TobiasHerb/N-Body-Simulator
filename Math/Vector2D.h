/*
 * Vector
 *
 *  Created on: May 15, 2012
 *      Author: Tobias Herb
 */

#ifndef VECTOR2D_
#define VECTOR2D_

// includes.
#include "Vector3D.h"
#include <string>
#include <sstream>

namespace Math {

	template<typename T> class Vector2D {
	public:
		Vector2D() {
			this->x = 0;
			this->y = 0;
		}

		Vector2D( const T x, const T y ) {
			this->x = x;
			this->y = y;
		}

		Vector2D( const Vector2D<T>& v ) {
			this->x = v.x;
			this->y = v.y;
		}

	private:
		T 	x;
		T 	y;

	public:
		Vector2D<T>& operator=( const Vector2D<T>& v ) {
			this->x = v.x;
			this->y = v.y;
			return (*this);
		}

		Vector2D<T> operator+( const Vector2D<T>& v ) const {
			Vector2D<T> r( this->x + v.x,
				       this->y + v.y );
			return r;
		}

		Vector2D<T> operator-( const Vector2D<T>& v ) const {
			Vector2D<T> r( this->x - v.x,
				       this->y - v.y );
			return r;
		}

		Vector2D<T> operator*( const T val ) const {
			Vector2D<T> r( this->x * val,
				       this->y * val );
			return r;
		}

		Vector2D<T> operator/( const T val ) const {
			T reciprocalVal = 1 / val;
			Vector2D<T> r( this->x * reciprocalVal,
				       this->y * reciprocalVal );
			return r;
		}

		Vector2D<T>& operator+=( const Vector2D<T>& v ) {
			this->x += v.x;
			this->y += v.y;
			return (*this);
		}

		Vector2D<T>& operator-=( const Vector2D<T>& v ) {
			this->x -= v.x;
			this->y -= v.y;
			return (*this);
		}

		Vector2D<T>& operator*=( const T val ) {
			this->x *= val;
			this->y *= val;
			return (*this);
		}

		Vector2D<T>& operator/=( const T val ) {
			T reciprocalVal = 1 / val;
			this->x *= reciprocalVal;
			this->y *= reciprocalVal;
			return (*this);
		}

		T length() const {
			return sqrt( ( this->x * this->x ) +
				     ( this->y * this->y ) );
		}

		Vector2D<T> normalize() const {
			return ( (*this) / length() );
		}

		float operator*( const Vector3D<T> v ) const {
			return ( this->x * v.X() +
				 this->y * v.Y() );
		}

		Vector3D<T> cross( const Vector2D<T>& v ) {
			Vector3D<T> r( 0, 0, this->x * v.Y() - this->y * v.X() );
			return r;
		}

		inline T X() const {
			return this->x;
		}

		inline T Y() const {
			return this->y;
		}

		Vector2D<T>& set( const T x, const T y ) {
			this->x = x;
			this->y = y;
			return (*this);
		}

		Vector2D<T>& set( const Vector2D<T>& v ) {
			this->x = v.X();
			this->y = v.Y();
			return (*this);
		}

		std::string toString() const {
			std::stringstream ss;
			ss << "[" << this->x << ","
			          << this->y << "]";
			return ss.str();
		}

		bool operator==( const Vector2D<T>& v ) const {
			if( this == &v )
				return true;
			if( this->x == v.x &&
				this->y == v.y ) {
				return true;
			}
			// TODO: fulfills not exact equals contract...
			return false;
		}

	};
}

#endif /* VECTOR2D_ */
