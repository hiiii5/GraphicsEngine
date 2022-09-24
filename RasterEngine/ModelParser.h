#pragma once
#include "StaticMesh.h"
#include "StoneHenge.h"

class ModelParser
{
public:
	static StaticMesh LoadMesh(const _OBJ_VERT_* MeshData, unsigned VertexCount, const unsigned* IndicesData, unsigned IndexCount);
};

