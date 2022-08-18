#include "PixelShader.h"

PixelShader::PixelShader(std::function<void(Color&)> ShaderFunction): ShaderFunction(std::move(ShaderFunction)) {}

void PixelShader::Execute(const std::function<void(Color&)>& Function, Color& C) {
	Function(C);
}
