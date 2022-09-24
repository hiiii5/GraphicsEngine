#include "GEngine.h"

#include <iostream>
#include <random>

#include "Actor.h"
#include "EngineDefines.h"
#include "RasterSurface.h"
#include "BaseObject.h"
#include "RenderHelper.h"
#include "StaticMeshComponent.h"
#include "Shader.h"
#include "ModelParser.h"
#include "StoneHenge.h"

GEngine* GEngine::Instance = nullptr;
Shader* RenderHelper::CurrentShader = nullptr;

void GEngine::Start(const unsigned NewWidth, const unsigned NewHeight) {
	IsInitialized =  RS_Initialize("Dustin Roden", NewWidth, NewHeight);

	if(!IsInitialized) {
		Destroy();
		return;
	}

	IsRunning = false;

	this->Width = NewWidth;
	this->Height = NewHeight;

	Pixels.assign(this->Width * this->Height, 0xFF000000);
	OldPixels = Pixels;
	Depth.assign(this->Width * this->Height, 1000000.0f);
	Stars.assign(3000, {});

	DeltaTimer.Restart();
	DeltaTime = 0.0f;
	ElapsedTime += DeltaTime;

	MainCamera = new Camera(0.01f, 10.0f, Deg2Rad(90.0f), Width, Height, Mat4().Rotate({ -18.0f, 0.0f, 0 }).Translate({ 0, 0.5, -4.5 }));

	StartEvent.Notify();

	IsRunning = true;

	//constexpr auto halfScale = 0.5f / 2;
	/*auto* a1 = Spawn();
	auto* a1Comp = a1->AddComponent(new StaticMeshComponent(CUBE_MESH));
	a1->WorldTransform.Translate({ 0, 0.25f, 0 });
	dynamic_cast<StaticMeshComponent*>(a1Comp)->Material = CUBE_SHADER;*/


	auto stoneHengeActor = Spawn();
	stoneHengeActor->WorldTransform.Scale({0.1f, 0.1f, 0.1f});
	auto stoneHengeSMComp = stoneHengeActor->AddComponent(new StaticMeshComponent(ModelParser::LoadMesh(StoneHenge_data, 1457, StoneHenge_indicies, 2532)));
	dynamic_cast<StaticMeshComponent*>(stoneHengeSMComp)->Material = STONEHENGE_SHADER;
	dynamic_cast<StaticMeshComponent*>(stoneHengeSMComp)->RenderWire = false;


	// Calculate star positions.
	for (Vert& star : Stars) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(-100, 100);

		const auto x = dist(gen) / 100.0f;
		const auto y = dist(gen) / 100.0f;
		const auto z = dist(gen) / 100.0f;
		const auto pos = Vec3F(x, y, z);
		star.Pos = Vec3F::Scale(pos, 50.0f);
		star.C = Color(Color::White);
		star.Light = {1.0f, 1.0f, 1.0f};
		star.Norm = Vec3F(0, 1.0f, 0);
	}

	do {
		Update();
		Render();
	}
	while (RS_Update(&OldPixels[0], OldPixels.size()));

	Destroy();
}

Actor* GEngine::Spawn() {
	SpawnedObjects.push_back(new Actor());

	return SpawnedObjects.back();
}

int GEngine::AllocateObjectId() {
	CurObjId++;
	return CurObjId;
}

GEngine::GEngine(): MainCamera(nullptr), IsInitialized(false), IsRunning(false), DeltaTime(0), ElapsedTime(0.0f), Width(0), Height(0), CurObjId(-1) {}

void GEngine::Update() {
	// Update engine delta time.
	DeltaTimer.Signal();
	DeltaTime = DeltaTimer.Delta();
	ElapsedTime += DeltaTime;

	UpdateEvent.Notify();

	auto transform = MainCamera->WorldTransform;
	auto worldPos = transform.GetPosition();
	MainCamera->WorldTransform.Translate({-worldPos.X, -worldPos.Y, -worldPos.Z});
	MainCamera->WorldTransform.Rotate({0, -5.0f * DeltaTime, 0});
	MainCamera->WorldTransform.Translate(worldPos);
}

void GEngine::Render() {
	RenderHelper::ClearBuffer();

	// Draw stars
	for (Vert& star : Stars) {
		// Convert to screen space position
		Mat4 t = {};
		const auto screenSpace = Camera::WorldToScreen(*MainCamera, star, t);
		RenderHelper::DrawPixel(star.C.Get(), screenSpace.X, screenSpace.Y);
	}


	//RenderHelper::DrawWireCube(MainCamera, CubeTransform, 0.5f);
	//RenderHelper::DrawGrid(MainCamera, 10, 10, 0.5, 0.5, 0xFF888888);
	RenderEvent.Notify();

	//RenderHelper::DrawDepth(Depth);

	// Draw a wire cube at the center of the screen.
	/*Mat4 T{};
	T.Rotate({0, -18, 0});
	T.Translate({0, 0.25f, 0});
	RenderHelper::DrawWireCube(MainCamera, T, 0.5f, DEFAULT_SHADER);*/

	//const auto sm = dynamic_cast<StaticMeshComponent*>(SpawnedObjects.back()->GetComponent(0))->Sm;
	//RenderHelper::DrawWireMesh(MainCamera, SpawnedObjects.back()->WorldTransform, sm.Vertices, sm.Indices);

	// Update the old pixels to match the next frame.
	OldPixels = Pixels;
}

void GEngine::Destroy() {
	IsRunning = false;

	DestroyEvent.Notify();

	for (const auto & object : SpawnedObjects) {
		delete object;
	}
	SpawnedObjects.clear();
	delete MainCamera;
	MainCamera = nullptr;

	RS_Shutdown();
	delete Instance;
}

