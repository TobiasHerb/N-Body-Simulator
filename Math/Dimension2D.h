/*
 * Dimension2D.h
 *
 *  Created on: May 16, 2012
 *      Author: Tobias Herb
 */

#ifndef DIMENSION2D_H_
#define DIMENSION2D_H_

namespace Math {

	template<typename T> class Dimension2D {
	public:
		Dimension2D() {
			this->w = 0;
			this->h = 0;
		}

		Dimension2D( const T w, const T h ) {
			this->w = w;
			this->h = h;
		}

		Dimension2D( const Dimension2D<T>& d ) {
			this->w = d.w;
			this->h = d.h;
		}

	private:
		T 	w;
		T	h;

	public:
		Dimension2D<T>& operator=( const Dimension2D<T>& d ) {
			this->w = d.w;
			this->h = d.h;
			return (*this);
		}

		Dimension2D<T>& set( const T w, const T h ) {
			this->w = w;
			this->h = h;
			return (*this);
		}

		inline T W() const {
			return this->w;
		}

		inline T H() const {
			return this->h;
		}
	};

}

#endif /* DIMENSION2D_H_ */
