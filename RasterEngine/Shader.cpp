#include "Shader.h"
Shader::Shader(std::function<void(Color& V, Color& C, Vec2F& Uv)> PixelShader,
			   std::function<void(Vert&, Mat4& T, const Camera& C)> VertexShader): PixelShader(std::move(PixelShader)), VertexShader(
																					   std::move(VertexShader)) {}
