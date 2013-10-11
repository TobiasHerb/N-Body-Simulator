/*
 * Dimension3D.h
 *
 *  Created on: May 16, 2012
 *      Author: Tobias Herb
 */

#ifndef DIMENSION3D_H_
#define DIMENSION3D_H_

namespace Math {

	template<typename T> class Dimension3D {
	public:
		Dimension3D() {
			this->w = 0;
			this->h = 0;
			this->d = 0;
		}

		Dimension3D( const T w, const T h, const T d ) {
			this->w = w;
			this->h = h;
			this->d = d;
		}

		Dimension3D( const Dimension3D<T>& q ) {
			this->w = q.w;
			this->h = q.h;
			this->d = q.d;
		}

	private:
		T 	w;
		T	h;
		T	d;

	public:
		Dimension3D<T>& operator=( const Dimension3D<T>& q ) {
			this->w = q.w;
			this->h = q.h;
			this->d = q.d;
			return (*this);
		}

		Dimension2D<T>& set( const T w, const T h, const T d ) {
			this->w = w;
			this->h = h;
			this->d = d;
			return (*this);
		}

		inline T W() const {
			return this->w;
		}

		inline T H() const {
			return this->h;
		}

		inline T D() const {
			return this->d;
		}
	};

}

#endif /* DIMENSION3D_H_ */
