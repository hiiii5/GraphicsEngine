#pragma once
#include <functional>

#include "Color.h"

class PixelShader {
public:
	explicit PixelShader(std::function<void(Color&)> ShaderFunction);

	/**
	 * \brief To allow for a managed system of shaders, a lambda function was chosen to contain the vertex manipulation logic.
	 * \param Function Lambda function or functor to bind and execute.
	 * \param C The ARGB color of the pixel to modify.
	 */
	static void Execute(const std::function<void(Color&)>& Function, Color& C);

	// Shaders are bound by lambda functions and must match the arguments of this function pointer.
	std::function<void(Color&)> ShaderFunction;
};
