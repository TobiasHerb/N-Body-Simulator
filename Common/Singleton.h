/*
 * Singleton.h
 *
 *  Created on: May 16, 2012
 *      Author: Tobias Herb
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace Common {

	/*template<typename T> class Singleton {

	private:

		static T* instance;

		Singleton() {
		}

		Singleton( const Singleton<T>& ) {
		}

		virtual ~Singleton() {
		}

	public:
	   static Singleton<T>& getInstance() {
	      if( !instance )
	         instance = new T();
	      return *instance;
	   }

	   static void releaseInstance(){
	      if ( instance )
	         delete instance;
	      instance = 0;
	   }
	};

	template<typename T> Singleton<T>* Singleton::instance = 0;*/
}

#endif /* SINGLETON_H_ */
