#include "gbcpch.h"
#include "Math.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

namespace gbc::math
{
	bool decomposeTransform(const glm::mat4& transform, glm::vec3& outTranslation, glm::vec3& outRotation, glm::vec3& outScale)
	{
		// From glm::decompose in matrix_decompose.inl

		glm::mat4 LocalMatrix(transform);

		// Normalize the matrix.
		if (glm::epsilonEqual(LocalMatrix[3][3], 0.0f, glm::epsilon<float>()))
			return false;

		// First, isolate perspective. This is the messiest.
		if (glm::epsilonNotEqual(LocalMatrix[0][3], 0.0f, glm::epsilon<float>()) ||
			glm::epsilonNotEqual(LocalMatrix[1][3], 0.0f, glm::epsilon<float>()) ||
			glm::epsilonNotEqual(LocalMatrix[2][3], 0.0f, glm::epsilon<float>()))
		{
			// Clear the perspective partition
			LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = 0.0f;
			LocalMatrix[3][3] = 0.0f;
		}

		// Next take care of translation (easy).
		outTranslation = glm::vec3(LocalMatrix[3]);
		LocalMatrix[3] = glm::vec4(0.0f, 0.0f, 0.0f, LocalMatrix[3].w);

		glm::vec3 Row[3], Pdum3;

		// Now get scale and shear.
		for (glm::length_t i = 0; i < 3; i++)
			for (glm::length_t j = 0; j < 3; j++)
				Row[i][j] = LocalMatrix[i][j];

		// Compute X scale factor and normalize first row.
		outScale.x = glm::length(Row[0]);
		Row[0] = glm::detail::scale(Row[0], 1.0f);
		outScale.y = glm::length(Row[1]);
		Row[1] = glm::detail::scale(Row[1], 1.0f);
		outScale.z = glm::length(Row[2]);
		Row[2] = glm::detail::scale(Row[2], 1.0f);

		// Now, get the rotations out
		outRotation.y = asin(-Row[0][2]);
		if (cos(outRotation.y) != 0.0f)
		{
			outRotation.x = atan2(Row[1][2], Row[2][2]);
			outRotation.z = atan2(Row[0][1], Row[0][0]);
		}
		else
		{
			outRotation.x = atan2(-Row[2][0], Row[1][1]);
			outRotation.z = 0.0f;
		}

		return true;
	}
}
