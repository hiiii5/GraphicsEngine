#pragma once
#include <functional>

#include "Vertex.h"

class VertexShader {
public:
	/**
	 * \brief To allow for a managed system of shaders, a lambda function was chosen to contain the vertex manipulation logic.
	 * \param Function Lambda function or functor to bind and execute.
	 * \param V The reference of the vertex to manipulate.
	 */
	static void Execute(std::function<Vertex(Vertex&)> Function, Vertex& V);

	// Shaders are bound by lambda functions and must match the arguments of this function pointer.
	std::function<Vertex(Vertex&)> ShaderFunction;
};
