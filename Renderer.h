#pragma once
#include <cstdint>

#include "PixelShader.h"
#include "VertexShader.h"

class Matrix4X4;
class Vector3;
class Camera;
class Vector2;

class Renderer {
public:
	Renderer(uint32_t Width, uint32_t Height, uint32_t ClearColor);
	~Renderer();

	const uint32_t Width;
	const uint32_t Height;

	void ClearBuffer() const;

	void DrawPixel(const uint32_t& Pixel, uint32_t X, uint32_t Y) const;

	void DrawLine(const Vector2& Start, const Vector2& End, uint32_t Color = 0xFFFFFFFF) const;

	void DrawGrid(const Camera* Viewer, int WidthDivisions, int HeightDivisions, float GridWidth, float GridHeight, const uint32_t& Color = 0xFFFFFFFF) const;

	void DrawUnitAxis(const Camera* C, float AxisLength = 2.5) const;

	void DrawWireCube(const Camera* C, const Matrix4X4& Transform, float Scale, const uint32_t& Color) const;

	void UpdateFrame() const;

	void SetVertexShader(VertexShader* NewVertexShader);
	void SetPixelShader(PixelShader* Shader);

	uint32_t* GetFrame() const;

	uint32_t GetScreenSize() const { return Width * Height; }

private:
	uint32_t* Pixels;
	uint32_t* OldPixels;
	const uint32_t ClearColor;

	VertexShader* CurrentVertexProgram;
	PixelShader* CurrentPixelShaderProgram;
};
