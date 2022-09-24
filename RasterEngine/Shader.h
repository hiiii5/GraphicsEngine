#pragma once
#include <ctime>
#include <functional>

#include "EngineDefines.h"
#include "GEngine.h"
#include "celestial.h"
#include "StoneHenge_Texture.h"

class Shader
{
public:
	Shader(std::function<void(Color&, Vec2F&)> PixelShader, const std::function<void(Vert&, Mat4&, const Camera&)>&
		   VertexShader);

	// Shaders are bound by lambda functions and must match the arguments of this function pointer.
	std::function<void(Color&, Vec2F&)> PixelShader;
	std::function<void(Vert&, Mat4&, const Camera&)> VertexShader;
};

const Shader DEFAULT_SHADER{[](Color& C, Vec2F& Uv){ C = Color(Color::Green); }, [](Vert& V, Mat4& T, const Camera& C) {}};

const Shader INVISIBLE_SHADER{ [](Color& C, Vec2F& Uv) { C = Color(0, 0, 0, 0); }, [](Vert& V, Mat4& T, const Camera& C) {} };


const Shader MASTER_SHADER{[](Color& C, Vec2F& Uv) {
	// Get engine access for the shader.
	const auto delta = GEngine::Get()->DeltaTime;
	const auto elapsed = GEngine::Get()->ElapsedTime;
},
[](Vert& V, Mat4& T, const Camera& C) {
	// Get engine access for the shader.
	const auto delta = GEngine::Get()->DeltaTime;
	const auto elapsed = GEngine::Get()->ElapsedTime;
}};

const Shader CUBE_SHADER{ [](Color& C, Vec2F& Uv) {
	// Get the color at the intended pixel of the texture.
	const Vec2F pixel = { Uv.X * celestial_width, Uv.Y * celestial_height };

	C = Color(BGRA_TO_ARGB(celestial_pixels[TwoD2OneD(pixel.X, pixel.Y, celestial_width)]));

	/*srand(time(NULL));
	C.R *= Clamp((std::rand() % 255 + 1) / 255.0f, 0.5f, 1.0f);
	C.G *= Clamp((std::rand() % 255 + 1) / 255.0f, 0.5f, 1.0f);
	C.B *= Clamp((std::rand() % 255 + 1) / 255.0f, 0.5f, 1.0f);*/

}, [](Vert& V, Mat4& T, const Camera& C) {
	const auto delta = GEngine::Get()->DeltaTime;
	const auto elapsed = GEngine::Get()->ElapsedTime;



	//Camera::Perspective(V, T, C);

	Mat4 rot {};
	rot.Rotate({0.0f, -0.5f * delta, 0.0f});

	T = rot * T;

	//Mat4 rot = {};
	//rot.Rotate({-18.0f, 15.0f, 0.0f});
	//rot.Translate({ 0.5f, 0.25f, 0.0f });
	

	//T = rot;
} };


const Shader STONEHENGE_SHADER { [](Color& C, Vec2F& Uv) {
		MASTER_SHADER.PixelShader(C, Uv);

		const Vec2F pixel = { Uv.X * StoneHenge_width, Uv.Y * StoneHenge_height };
		const Color t = Color(BGRA_TO_ARGB(StoneHenge_pixels[TwoD2OneD(pixel.X, pixel.Y, StoneHenge_width)]));

		C = t;
	},
	[](Vert& V, Mat4& T, const Camera& C) {
		MASTER_SHADER.VertexShader(V, T, C);

		const auto delta = GEngine::Get()->DeltaTime;

		/*Mat4 rot {};
		rot.Rotate({0.0f, -0.001f * delta, 0.0f});

		T = rot * T;*/

		// Calculate directional lighting.
		auto dot = Vec3F::DotProduct(V.Norm, { -0.577f, -0.577f, 0.577f });
		dot = Clamp(dot, 0.0f, 1.0f);

		//const auto black = Color(Color::Black);
		auto lightColor = Color(0xFFC0C0F0);

		auto r = LerpF(lightColor.R, 0.0f, dot + 0.1f);
		auto g = LerpF(lightColor.G, 0.0f, dot + 0.1f);
		auto b = LerpF(lightColor.B, 0.0f, dot + 0.1f);

		r = Clamp(r, 0.0f, 255.0f);
		g = Clamp(g, 0.0f, 255.0f);
		b = Clamp(b, 0.0f, 255.0f);

		auto finalDirectionalLight = Vec3F(r, g, b) / 255.0f;

		// TODO: Fix me
		dot = Vec3F::DotProduct(V.Norm, V.Pos - Vec3F(-1, 0.5f, 1));

		lightColor = Color(Color::Red);
		r = LerpF(lightColor.R, 0.0f, dot + 0.1f);
		g = LerpF(lightColor.G, 0.0f, dot + 0.1f);
		b = LerpF(lightColor.B, 0.0f, dot + 0.1f);

		r = Clamp(r, 0.0f, 255.0f);
		g = Clamp(g, 0.0f, 255.0f);
		b = Clamp(b, 0.0f, 255.0f);

		auto finalPointLight = Vec3F(r, g, b) / 255.0f;


		V.Light = finalDirectionalLight/* + finalPointLight*/;
	}
};
