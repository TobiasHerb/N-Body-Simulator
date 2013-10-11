/*
 * Camera.cpp
 *
 *  Created on: May 15, 2012
 *      Author: Tobias Herb
 */

// includes.
#include "Camera.h"
#include "../Math/CommonMath.h"

//opengl.
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

namespace Renderer {

	Camera::Camera() {
		position.set( 0.0f, 0.0f, 0.0f );
		viewDirection.set( 0.0f, 0.0f, -1.0f );
		rightVector.set( 1.0f, 0.0f, 0.0f );
		upVector.set( 0.0f, 1.0f, 0.0f );
		rotX = rotY = rotZ = 0.0;
	}

	Camera::~Camera() {
	}

	void Camera::move( const Math::Vector3D<float>& direction ) {
		position += direction;
	}

	void Camera::rotateX( float a ) {
		rotX += a;
		rotX = fmodf( rotX, 360.0f );
		// rotate viewDirection around the right vector.
		viewDirection.set( ( viewDirection * cos( Math::CommonMath::deg2rad( a ) ) ) +
						   ( upVector * sin( Math::CommonMath::deg2rad( a ) ) ) ).normalize();
		// now compute the new upVector (by cross product).
		upVector = ( viewDirection.cross( rightVector ) * (-1) );
	}

	void Camera::rotateY( float a ) {
		rotY += a;
		rotY = fmodf( rotY, 360.0f );
		// rotate viewDirection around the up vector.
		viewDirection.set( ( viewDirection * cos( Math::CommonMath::deg2rad( a ) ) ) -
						   ( rightVector * sin( Math::CommonMath::deg2rad( a ) ) ) ).normalize();
		// now compute the new rightVector (by cross product).
		rightVector = ( viewDirection.cross( upVector ) );
	}

	void Camera::rotateZ( float a ) {
		rotZ += a;
		rotZ = fmodf( rotZ, 360.0f );
		// rotate viewDirection around the right vector.
		rightVector.set( ( rightVector * cos( Math::CommonMath::deg2rad( a ) ) ) +
						 ( upVector * sin( Math::CommonMath::deg2rad( a ) ) ) );
		// now compute the new upVector (by cross product).
		upVector = ( viewDirection.cross( rightVector ) * (-1) );
	}

	void Camera::updateCamera() {
		// the point at which the camera looks.
		Math::Vector3D<float> viewPoint = position + viewDirection;
		//as we know the up vector, we can easily use gluLookAt:
		gluLookAt( position.X(), position.Y(), position.Z(),
				   viewPoint.X(), viewPoint.Y(), viewPoint.Z(),
				   upVector.X(), upVector.Y(), upVector.Z() );
	}

	void Camera::moveForward( float distance ) {
		position = position + ( viewDirection * -distance );
	}

	void Camera::strafeRight ( float distance ) {
		position = position + ( rightVector * distance );
	}

	void Camera::moveUpward( float distance ) {
		position = position + ( upVector * distance );
	}

	Math::Vector3D<float> Camera::getViewVector() const {
		return this->viewDirection;
	}

	Math::Vector3D<float> Camera::getRightVector() const {
		return this->rightVector;
	}

	Math::Vector3D<float> Camera::getUpVector() const {
		return this->upVector;
	}

	Math::Vector3D<float> Camera::getPositionVector() const {
		return this->position;
	}

	void Camera::setCamera( const Math::Vector3D<float>& viewDirection,
							const Math::Vector3D<float>& rightVector,
							const Math::Vector3D<float>& upVector,
							const Math::Vector3D<float>& position ) {
		this->viewDirection = viewDirection;
		this->rightVector = rightVector;
		this->upVector = upVector;
		this->position = position;
	}
}
