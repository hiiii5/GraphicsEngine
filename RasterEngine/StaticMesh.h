#pragma once
#include <vector>
struct Vert;
struct Vec2F;

class StaticMesh
{
public:
	StaticMesh(std::vector<Vert> Vertices, std::vector<unsigned> Indices, std::vector<Vec2F> Uv);

	std::vector<Vert> Vertices;
	std::vector<unsigned> Indices;
	std::vector<Vec2F> Uv;
};

