#pragma once
#include "Vector3.h"

class Vertex {
public:
	Vertex(Vector3 Pos)
		: Pos(std::move(Pos)) {}

	Vector3 Pos; // This includes the w, internally.
};
