#pragma once

#include "EffekseerBackendCore.h"
#include "EffekseerEffectCore.h"
#include "Effekseer.h"
#include "EffekseerSettingCore.h"



class EffekseerEffectCore;



namespace EffekseerRenderer {
    class Renderer;
}

class EffekseerManagerCore {
private:
    ::EffekseerRenderer::Renderer *renderer_ = nullptr;
    float restDeltaTime_ = 0.0f;
    EffekseerRendererGL::OpenGLDeviceType openglDeviceType = EffekseerRendererGL::OpenGLDeviceType::OpenGL2;

public:
    EffekseerManagerCore() = default;

    ~EffekseerManagerCore();

    ::Effekseer::Manager *manager_ = nullptr;


    bool Initialize(int32_t spriteMaxCount, int32_t id);

    void Update(float deltaFrames);

    int Play(EffekseerEffectCore *effect);

    bool IsPlaing(int handle);

    void SetEffectPosition(int handle, float x, float y, float z);
    void SetEffectRoate(int handle, float x, float y, float z);
    void SetEffectScale(int handle, float x, float y, float z);


    void DrawBack();

    void DrawFront();




    void SetPause(int handle,bool pause);


    void SetProjectionMatrix(Effekseer::Matrix44 matrix44,Effekseer::Matrix44 matrix44C, bool view,float_t width,float_t heith);

};
