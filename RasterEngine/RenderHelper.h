#pragma once
#include <vector>
struct Color;
struct Vert;
struct Camera;
struct Vec2F;
struct Mat4;
struct Vec3F;

class RenderHelper {
public:
	static class Shader* CurrentShader;

	static void VertexShader(Vert& V, Mat4& T, const Camera& C);

	static void DrawDepth(const std::vector<float>& DepthBuffer);

	static void DrawPixel(const unsigned& Pixel, const unsigned X, const unsigned Y);

	static void DrawLine(const Vec2F& Start, const Vec2F& End);

	static void DrawWireCube(const Camera* C, Mat4& Transform, const float Scale, Shader RenderShader);

	static void DrawWireTriangle(const Camera* C, Mat4& Transform, const std::vector<Vert>& Vertices);

	static void DrawWireMesh(const Camera* C, Mat4& Transform, std::vector<Vert> Vertices, const std::vector<unsigned>
							 & Indices);

	static void DrawGrid(const Camera* Viewer, int WidthDivisions, int HeightDivisions, float GridWidth, float GridHeight,
				  const uint32_t& Color = 0xFFFFFFFF);

	static void FillTriangle(const Camera* C, Mat4& Transform, const std::vector<Vert>& Vertices, const std::vector<Vec2F>& Uv);

	static void FillMesh(const Camera* C, Mat4& Transform, std::vector<Vert> Vertices, const std::vector<unsigned>
						 & Indices, const std::vector<Vec2F>& Uv);

	/** Set all pixels to clear color. */
	static void ClearBuffer();
};
