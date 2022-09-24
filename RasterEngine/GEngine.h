/**
 * \author Dustin Roden
 * \date 08/24/22
 * \brief Global engine class, this is the main header for the engine and it started from main.
 */

#pragma once

#include <vector>

#include "EngineDefines.h"
#include "Event.h"
#include "XTime.h"

class Actor;

class GEngine {
	static GEngine* Instance;

public:
	static GEngine* Get() {
		if (!Instance) Instance = new GEngine;
		return Instance;
	}

	void Start(unsigned NewWidth, unsigned NewHeight);

	Event StartEvent;
	Event UpdateEvent;
	Event RenderEvent;
	Event DestroyEvent;

	Camera* MainCamera;

	Actor* Spawn();

	void Update();
	void Render();
	void Destroy();

	/**
	 * \brief Allocates a new id for an object, this is allocated by creation.
	 * \return New id from global engine id's.
	 */
	int AllocateObjectId();

	bool IsInitialized;
	bool IsRunning;

	float DeltaTime;
	float ElapsedTime{};
	unsigned Width, Height;

	int CurObjId;

	// Collection for rendering.
	std::vector<unsigned> Pixels;
	std::vector<unsigned> OldPixels;

	std::vector<Vert> Stars;

	std::vector<Actor*> SpawnedObjects;

	// Collection for depth buffer.
	std::vector<float> Depth;

	XTime DeltaTimer{};

protected:
	GEngine();
};

