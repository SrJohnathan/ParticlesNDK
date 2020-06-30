#pragma once

#include "EffekseerRendererGL.h"
#include "EffekseerBackendCore.h"
#include "Effekseer.h"


enum class EffekseerCoreDeviceType
{
	Unknown,
	OpenGL,

};


class EffekseerBackendCore
{
	static EffekseerCoreDeviceType deviceType_;

public:
	EffekseerBackendCore() = default;
	~EffekseerBackendCore() = default;

	static EffekseerCoreDeviceType GetDevice();

	static bool InitializeAsOpenGL();

	static void Terminate();
};
