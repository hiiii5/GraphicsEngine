#include "VertexShader.h"

void VertexShader::Execute(const std::function<Vertex(Vertex&)> Function, Vertex& V) {
	Function(V); // Call the execution object and return the result.
}
