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

    bool isPlaing(int handle);

    void SetEffectPosition(int handle, float x, float y, float z);
    void SetEffectRoate(int handle, float x, float y, float z);
    void SetEffectScale(int handle, float x, float y, float z);
    void SetCameraPosition( float x, float y, float z);
    void SetCameraRotate( float x, float y, float z);

    void DrawBack();

    void DrawFront();


    void SetViewProjectionMatrixWithSimpleWindowOrthogonal(int32_t windowWidth, int32_t windowHeight);

    void SetViewProjectionMatrixWithSimpleWindowPerspective( float_t windowWidth, float_t windowHeight,float_t up[],float_t nea, float_t faer );

    void UpdateWindowR();

    void UpdateWindowL();

    void setPause(int handle,bool pause);


    void SetProjectionMatrix(Effekseer::Matrix44 matrix44,Effekseer::Matrix44 matrix44C);
};
