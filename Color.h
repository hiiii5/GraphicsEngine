#pragma once
#include <cstdint>

class Color {
public:
	Color(const uint32_t A, const uint32_t R, const uint32_t G, const uint32_t B)
		: A(A),
		  R(R),
		  G(G),
		  B(B) {}

	explicit Color(uint32_t UnsignedColor);


	uint32_t GetColor() const;

	// Max 255
	uint32_t A, R, G, B;

	static Color AlphaBlend(const Color& Foreground, const Color& Background);
};
