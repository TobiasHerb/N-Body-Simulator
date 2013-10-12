/*
 * Thread.h
 *
 *  Created on: Jun 1, 2012
 *      Author: Tobias Herb
 */

#ifndef THREAD_H_
#define THREAD_H_

#include "../GlobalDefs.h"

// includes.
#include <pthread.h>
#include <cassert>

namespace Application {

	template<class T> class Thread {
	public:
		Thread() {
		}

		virtual ~Thread() {
		}

	private:
		pthread_t	thread;

		static T*	self;

		pthread_mutex_t	mutex;

	public:
		static T* getInstance() {
			if( self == 0L ) {
				self = new T();
			}
			return self;
		}
		static void releaseInstance() {
			if( self != 0L ) {
				delete self;
			}
		}

	public:
		void execute( void* args ) {
		    int rc = pthread_create( &thread, 0L, static_runThread, args );
		    assert( 0 == rc );
		}

		void join() {
		    int rc = pthread_join( thread, 0L );
		    assert( 0 == rc );
		}

		inline void lock() {
			pthread_mutex_lock( &mutex );
		}

		inline void unlock() {
			pthread_mutex_unlock( &mutex );
		}

	public:
		virtual void* runThread( void* args ) = 0;

	private:
		static void* static_runThread( void* args ) {
			if( self != 0L ) {
				return self->runThread( args );
			}
			return 0L;
		}
	};

	template<class T> T* Thread<T>::self = 0L;
}

#endif /* THREAD_H_ */
