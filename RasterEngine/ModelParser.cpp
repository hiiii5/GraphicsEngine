#include "ModelParser.h"

#include "EngineDefines.h"

StaticMesh ModelParser::LoadMesh(const _OBJ_VERT_* MeshData, const unsigned VertexCount, const unsigned* IndicesData, unsigned IndexCount) {
	// For every vertex entry add it to the mesh vertices and uv lists
	std::vector<Vert> meshVertices{};
	std::vector<Vec2F> meshUvs{};
	for (unsigned i = 0; i < VertexCount; i++) {
		meshVertices.emplace_back(Vert({ MeshData[i].pos[0], MeshData[i].pos[1], MeshData[i].pos[2] }, Color(0xFFFFFFFF), {MeshData[i].nrm[0], MeshData[i].nrm[1], MeshData[i].nrm[2]}));
	}

	// Copy the indices from the mesh data into the vector.
	std::vector<unsigned> indices{};
	indices.reserve(IndexCount);
	for (unsigned i = 0; i < IndexCount; i++) {
		indices.emplace_back(IndicesData[i]);

		auto uv = Vec2F(MeshData[IndicesData[i]].uvw[0], MeshData[IndicesData[i]].uvw[1]);
		uv.Z = MeshData[IndicesData[i]].uvw[2];
		meshUvs.emplace_back(uv);
	}

	// Construct a static mesh from the mesh data.
	return {meshVertices, indices, meshUvs};
}
