#include <iostream>

#include "Camera.h"
#include "Matrix4x4.h"
#include "RasterSurface.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Vector3.h"
#include "MathDefines.h"
#include "XTime.h"


constexpr uint32_t WIDTH = 500;
constexpr uint32_t HEIGHT = 500;
constexpr uint32_t NUM_PIXEL = WIDTH * HEIGHT;
uint32_t Pixels[NUM_PIXEL] = {0};

int main() {
	RS_Initialize("Dustin Roden", WIDTH, HEIGHT);

	// Initialize the renderer interface.
	const Renderer r(WIDTH, HEIGHT, 0xFF000000);

	// Create a camera for doing projection.
	const auto c = new Camera(0.01, 10.0, WIDTH, HEIGHT, DEG2_RAD(90.0));

	// Move the camera into the intended view.
	c->SetWorldTransform(c->GetWorldTransform().Translate({0, 0, -1}).Rotate({ -18, 0, 0 }));

	//printf("%s", c->GetWorldTransform().ToString().c_str());

	XTime timer{};
	timer.Restart();
	auto cubeWorldTransform = Matrix4X4{}; cubeWorldTransform.Translate({ 0, 0.25, 0 });
	do {
		timer.Signal();
		const auto delta = timer.Delta();
		r.ClearBuffer();

		r.DrawGrid(c, 10, 10, 0.5, 0.5, 0xFF888888);

		//r.DrawUnitAxis(c, 0.25);

		
		cubeWorldTransform.Rotate({ 0, -15 * delta, 0 });
		

		r.DrawWireCube(c, cubeWorldTransform, 0.5, 0xFF00aa00);
		r.UpdateFrame();
	}
	while (RS_Update(r.GetFrame(), NUM_PIXEL));

	RS_Shutdown();
}
