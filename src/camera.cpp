#include "Camera.h"

using namespace linalg;

void Camera::MoveTo(const vec3f& position) noexcept
{
	m_position = position;
}

void Camera::Move(const vec3f& direction) noexcept
{
	vec4f dirView = { direction.x, direction.y, direction.z, 0.0f };
	vec4f dirWorld = m_rotation * dirView;
	m_position += dirWorld.xyz();
}

void Camera::Rotate(const long mousedx, const long mousedy, float sensitivity) noexcept 
{
	m_yaw   += -mousedx * sensitivity;
	m_pitch += -mousedy * sensitivity;

	m_pitch = clamp(m_pitch, -maxPitch, maxPitch);

	m_rotation = mat4f::rotation(0, m_yaw, m_pitch);

	ViewToWorld = mat4f::translation(m_position) * m_rotation;
}

mat4f Camera::WorldToViewMatrix() const noexcept
{
	// Assuming a camera's position and rotation is defined by matrices T(p) and R,
	// the View-to-World transform is T(p)*R (for a first-person style camera).
	//
	// World-to-View then is the inverse of T(p)*R;
	//		inverse(T(p)*R) = inverse(R)*inverse(T(p)) = transpose(R)*T(-p)
	// Since now there is no rotation, this matrix is simply T(-p)

	return transpose(m_rotation) * mat4f::translation(-m_position);
}

mat4f Camera::ProjectionMatrix() const noexcept
{
	return mat4f::projection(m_vertical_fov, m_aspect_ratio, m_near_plane, m_far_plane);
}