#include "StaticMesh.h"

#include <utility>
#include "EngineDefines.h"

StaticMesh::StaticMesh(std::vector<Vert> Vertices, std::vector<unsigned> Indices, std::vector<Vec2F> Uv):
	Vertices(std::move(Vertices)),
	Indices(std::move(Indices)),
	Uv(std::move(Uv)) {}
