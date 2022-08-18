#include "Color.h"

#include "MathHelper.h"

Color::Color(const uint32_t UnsignedColor) : A(((UnsignedColor & 0xFF000000) >> 24) / 255),
											 R((UnsignedColor & 0x00FF0000) >> 16),
											 G((UnsignedColor & 0x0000FF00) >> 8),
											 B(UnsignedColor & 0x000000FF) {}

uint32_t Color::GetColor() const { return (A << 24) * 255 | R << 16 | G << 8 | B; }

Color Color::AlphaBlend(const Color& Foreground, const Color& Background) {
	const auto red = Foreground.R * Foreground.A + Background.R * (1.0f - Foreground.A);
	const auto green = Foreground.G * Foreground.A + Background.G * (1.0f - Foreground.A);
	const auto blue = Foreground.B * Foreground.A + Background.B * (1.0f - Foreground.A);

	const auto color = Foreground.A << 24 | MathHelper::Floor(red) << 16 | MathHelper::Floor(green) << 8 | MathHelper::Floor(blue);

	return Color{color};
}
