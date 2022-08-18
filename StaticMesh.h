#pragma once
#include <vector>

#include "VertexShader.h"

class Vector3;

class StaticMesh {
public:
	StaticMesh() = default;
	StaticMesh(std::vector<Vector3> Vertices, std::vector<uint32_t> Indices);

	uint32_t GetVertexCount() const;
	uint32_t GetIndicesCount() const;

	std::vector<Vector3> GetVertices();
	std::vector<uint32_t> GetIndices();

	Vector3 GetVertexAt(uint32_t Index);
	uint32_t GetIndexAt(uint32_t Index) const;

	VertexShader GetVertexShader() const;

private:
	std::vector<Vector3> Vertices;
	std::vector<uint32_t> Indices;

	VertexShader Vs;
};
