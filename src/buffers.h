/**
 * @file buffers.h
 * @brief Contains constant buffers
*/

#pragma once

#include "vec/mat.h"

/**
 * @brief Contains transformation matrices.
*/
struct TransformationBuffer
{
	linalg::mat4f ModelToWorldMatrix; //!< Matrix for converting from object space to world space.
	linalg::mat4f WorldToViewMatrix; //!< Matrix for converting from world space to view space.
	linalg::mat4f ProjectionMatrix; //!< Matrix for converting from view space to clip cpace.
};

struct LightCamBuffer
{
	linalg::vec4f CameraPosition;
	linalg::vec4f LightPosition;
};

struct alignas(16) MaterialBuffer
{
	alignas(16) linalg::vec3f AmbientColor;
	alignas(16) linalg::vec3f DiffuseColor;
	alignas(16) linalg::vec3f SpecularColor;
	float Shininess;
};