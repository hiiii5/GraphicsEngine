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
	Shader(std::function<void(Color&, Color&, Vec2F&)> PixelShader, std::function<void(Vert&, Mat4&, const Camera&)>
		   VertexShader);

	// Shaders are bound by lambda functions and must match the arguments of this function pointer.
	std::function<void(Color&, Color&, Vec2F&)> PixelShader;
	std::function<void(Vert&, Mat4&, const Camera&)> VertexShader;

	static float GetLightRatio(const Vec3F& LightDirection, const Vec3F& SurfaceNormal) {
		return Clamp(Vec3F::DotProduct(LightDirection, SurfaceNormal), 0.0f, 1.0f);
	}
};

const Shader DEFAULT_SHADER{[](Color& V, Color& C, Vec2F& Uv){ C = Color(Color::Green); }, [](Vert& V, Mat4& T, const Camera& C) {}};

const Shader INVISIBLE_SHADER{ [](Color& V, Color& C, Vec2F& Uv) { C = Color(0, 0, 0, 0); }, [](Vert& V, Mat4& T, const Camera& C) {} };


const Shader MASTER_SHADER{[](Color& V, Color& C, Vec2F& Uv) {
	// Get engine access for the shader.
	const auto delta = GEngine::Get()->DeltaTime;
	const auto elapsed = GEngine::Get()->ElapsedTime;
},
[](Vert& V, Mat4& T, const Camera& C) {
	// Get engine access for the shader.
	const auto delta = GEngine::Get()->DeltaTime;
	const auto elapsed = GEngine::Get()->ElapsedTime;
}};


const Shader CUBE_SHADER{ [](Color& V, Color& C, Vec2F& Uv) {
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


const Shader STONEHENGE_SHADER { [](Color& V, Color& C, Vec2F& Uv) {
	MASTER_SHADER.PixelShader(V, C, Uv);

	unsigned texWidth = StoneHenge_width;
	unsigned texHeight = StoneHenge_height;
	unsigned texSize = StoneHenge_width*StoneHenge_height;

	const Vec2F pixel = { Uv.X * texWidth, Uv.Y * texHeight };

	auto t = Color(BGRA_TO_ARGB(StoneHenge_pixels[TwoD2OneD(pixel.X, pixel.Y, StoneHenge_width)]));

	/*double u = Uv.X * texSize - 0.5f;
	double v = Uv.Y * texSize - 0.5f;
	int x = floor(u);
	int y = floor(v);

	double uRatio = u-x;
	double vRatio = v-y;
	double uOpposite = 1 - uRatio;
	double vOpposite = 1 - vRatio;*/

	// Calculate the 4 indices to sample
	/*auto i1 = TwoD2OneD(x, y, StoneHenge_width);
	auto i2 = TwoD2OneD(x+1, y, StoneHenge_width);
	auto i3 = TwoD2OneD(x, y+1, StoneHenge_width);
	auto i4 = TwoD2OneD(x+1, y+1, StoneHenge_width);

	auto sample1 = (i1 <= texSize) ? BGRA_TO_ARGB(StoneHenge_pixels[i1]) : 0xFF000000;
	auto sample2 = (i2 <= texSize) ? BGRA_TO_ARGB(StoneHenge_pixels[i2]) : 0xFF000000;
	auto sample3 = (i3 <= texSize) ? BGRA_TO_ARGB(StoneHenge_pixels[i3]) : 0xFF000000;
	auto sample4 = (i4 <= texSize) ? BGRA_TO_ARGB(StoneHenge_pixels[i4]) : 0xFF000000;

	auto final = (unsigned)((sample1 * uOpposite + sample2 * uRatio) * vOpposite +
		(sample3 * uOpposite + sample4 * uRatio) * vRatio);

	Color t = Color(final);*/

	// Apply lighting to final color of surface.
	t *= V + 0.1f;

	C = t;

	}, [](Vert& V, Mat4& T, const Camera& C) {
	MASTER_SHADER.VertexShader(V, T, C);

	const auto time = GEngine::Get()->ElapsedTime;
	const auto delta = GEngine::Get()->DeltaTime;

	const auto sinTime = sin(time);


	// Calculate directional lighting.
	const auto directionalLightVec = Vec3F(-0.577f, -0.577f, 0.577f);
	const auto directionalLightColor = Color(0xFFC0C0F0);
	constexpr auto directionalLightIntensity = 0.25f;

	const auto directionalLightRatio = Shader::GetLightRatio(directionalLightVec * -1.0f, V.Norm);

	const auto directionalResult = directionalLightColor * directionalLightIntensity * V.C * directionalLightRatio;


	// Calculate a single point light with a point in space.
	const auto pointLightPos = Vec3F(5.0f, 3.0f, 0.5f);
	const auto pointLightColor = Color(0xFFFF0000);
	constexpr auto pointLightIntensity = 150.0f;
	constexpr auto pointLightRadius = 150.0f;

	
	auto pointLightDir = pointLightPos - V.Pos;
	auto pointLightAttenuation = 1.0f - Clamp(Vec3F::Magnitude(pointLightDir) / pointLightRadius);
	Vec3F::Normalize(pointLightDir);

	const auto pointLightRatio = Clamp(Vec3F::DotProduct(pointLightDir, V.Norm));
	auto pointLightResult = pointLightColor * pointLightIntensity * V.C * pointLightRatio;
	pointLightResult *= pointLightAttenuation*pointLightAttenuation;
	pointLightResult *= sinTime;


	// Calculate the surfaces lighting color.
	auto result = directionalResult + pointLightResult;


	// Apply ambient lighting
	const auto ambientLight = Color(0xaaaaaaaa);
	constexpr auto ambientLightIntensity = 0.05f;

	result += ambientLight * ambientLightIntensity;


	// Clamp the final light color.
	result.R = result.R / 255.0f;
	result.G = result.G / 255.0f;
	result.B = result.B / 255.0f;

	V.Light = {result.R, result.G, result.B};

	}
};
