/*
 * Point2D.h
 *
 *  Created on: May 15, 2012
 *      Author: Tobias Herb
 */

#ifndef POINT2D_H_
#define POINT2D_H_

// includes.
#include "Vector2D.h"
#include <string>
#include <sstream>

namespace Math {

	template<typename T> class Point2D {
	public:
		Point2D() {
			this->x = 0;
			this->y = 0;
		}

		Point2D( const T x, const T y ) {
			this->x = x;
			this->y = y;
		}

		Point2D( const Point2D<T>& p ) {
			this->x = p.x;
			this->y = p.y;
		}

		Point2D( const Vector2D<T>& v ) {
			this->x = v.X();
			this->y = v.Y();
		}

	private:
		T x;
		T y;

	public:
		Point2D<T>& operator=( const Point2D<T>& p ) {
			this->x = p.x;
			this->y = p.y;
			return (*this);
		}

		Point2D<T> operator+( const Vector2D<T>& v ) const {
			Point2D<T> r( this->x + v.X(),
					      this->y + v.Y() );
			return r;
		}

		Point2D<T> operator-( const Vector2D<T>& v ) const {
			Point2D<T> r( this->x - v.X(),
					      this->y - v.Y() );
			return r;
		}

		Point2D<T> operator+=( const Vector2D<T>& v ) {
			this->x += v.X();
			this->y += v.Y();
			return (*this);
		}

		Point2D<T> operator-=( const Vector2D<T>& v ) {
			this->x -= v.X();
			this->y -= v.Y();
			return (*this);
		}

		Vector2D<T> getPositionVector() const {
			Vector2D<T> v( this->x,
					       this->y );
			return v;
		}

		T X() const {
			return this->x;
		}

		T Y() const {
			return this->y;
		}

		std::string toString() const {
			std::stringstream ss;
			ss << "(" << this->x << "," << this->y << ")";
			return ss.str();
		}

		bool operator==( const Point2D<T>& v ) const {
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

#endif /* POINT2D_H_ */
