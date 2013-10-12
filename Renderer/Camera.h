/*
 * Camera.h
 *
 *  Created on: May 15, 2012
 *      Author: Tobias Herb
 */

#ifndef CAMERA_H_
#define CAMERA_H_

// includes.
#include "../Math/Vector3D.h"

namespace Renderer {

	class Camera {
	public:
		Camera();
		virtual ~Camera();

	private:
		Math::Vector3D<float> viewDirection;
		Math::Vector3D<float> rightVector;
		Math::Vector3D<float> upVector;
		Math::Vector3D<float> position;

		float rotX;
		float rotY;
		float rotZ;

	public:
		void move( const Math::Vector3D<float>& direction );
		void rotateX( const float a );
		void rotateY( const float a );
		void rotateZ( const float a );

		void moveForward( const float distance );
		void moveUpward( const float distance );
		void strafeRight( const float distance );

		void updateCamera();

		Math::Vector3D<float> getViewVector() const;
		Math::Vector3D<float> getRightVector() const;
		Math::Vector3D<float> getUpVector() const;
		Math::Vector3D<float> getPositionVector() const;

		void setCamera( const Math::Vector3D<float>& viewDirection,
				const Math::Vector3D<float>& rightVector,
				const Math::Vector3D<float>& upVector,
				const Math::Vector3D<float>& position );
	};
}

#endif /* CAMERA_H_ */
