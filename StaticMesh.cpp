#include "StaticMesh.h"
#include "Vector3.h"

StaticMesh::StaticMesh(std::vector<Vector3> Vertices, std::vector<uint32_t> Indices): Vertices(std::move(Vertices)),
																					  Indices(std::move(Indices)) {}

uint32_t StaticMesh::GetVertexCount() const { return Vertices.size(); }

uint32_t StaticMesh::GetIndicesCount() const { return Indices.size(); }

std::vector<Vector3> StaticMesh::GetVertices() { return Vertices; }

std::vector<uint32_t> StaticMesh::GetIndices() { return Indices; }

Vector3 StaticMesh::GetVertexAt(const uint32_t Index) { return Vertices.at(Index); }

uint32_t StaticMesh::GetIndexAt(const uint32_t Index) const { return Indices.at(Index); }

VertexShader StaticMesh::GetVertexShader() const {
	return Vs;
}

