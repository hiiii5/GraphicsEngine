#include <iostream>

#include "Camera.h"
#include "Matrix4x4.h"
#include "RasterSurface.h"
#include "Renderer.h"
#include "Vector3.h"
#include "MathDefines.h"
#include "MathHelper.h"
#include "XTime.h"
#include "thread"

#include "VertexShader.h"


constexpr uint32_t WIDTH = 500;
constexpr uint32_t HEIGHT = 800;
constexpr uint32_t NUM_PIXEL = WIDTH * HEIGHT;
uint32_t Pixels[NUM_PIXEL] = {0};

int main() {
	RS_Initialize("Dustin Roden", WIDTH, HEIGHT);

	// Initialize the renderer interface.
	Renderer renderer(WIDTH, HEIGHT, 0xFF000000);

	// Create a camera for doing projection.
	auto camera = Camera(0.01f, 10.0f, WIDTH, HEIGHT, MathHelper::Deg2Rad(90.0f));

	// Move the camera into the intended view.
	camera.SetWorldTransform(camera.GetWorldTransform().Translate({0, 0, -1}).Rotate({ -18, 0, 0 }));

	// Start the world timer.
	XTime timer{};
	timer.Restart();

	auto cubeWorldTransform = Matrix4X4{};
	cubeWorldTransform.Translate({ 0, 0.25, 0 });

	do {
		// Update the world timer.
		timer.Signal();
		const auto delta = timer.Delta();

		renderer.ClearBuffer();

		renderer.SetPixelShader(new PixelShader([](Color& C) {
			C.B = 255;
		}));

		renderer.DrawGrid(&camera, 10, 10, 0.5, 0.5, 0xFF888888);

		renderer.DrawUnitAxis(&camera, 0.25);
		
		cubeWorldTransform.Rotate({ 0, -15 * delta, 0 });
		renderer.DrawWireCube(&camera, cubeWorldTransform, 0.5, 0xFF00aa00);

		renderer.UpdateFrame();
	}
	while (RS_Update(renderer.GetFrame(), NUM_PIXEL));

	RS_Shutdown();

	return 1;
}
