#include "EffekseerManagerCore.h"
#include "EffekseerRendererGL.h"
#include "Effekseer.h"
#include <assert.h>
#include <iostream>


#if   defined(__EFFEKSEER_RENDERER_GLES2__)

#include <android/log.h>

#define TAG "PARTICLES"

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,    TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,     TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,     TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,    TAG, __VA_ARGS__)

#endif


const float DistanceBase = 15.0f;
const float OrthoScaleBase = 16.0f;
const float ZoomDistanceFactor = 1.125f;
const float MaxZoom = 40.0f;
const float MinZoom = -40.0f;

static float g_RotX = 30.0f;
static float g_RotY = -30.0f;
static Effekseer::Vector3D g_lightDirection = Effekseer::Vector3D(1, 1, 1);
static float g_Zoom = 0.0f;
const float PI = 3.14159265f;

static bool g_mouseRotDirectionInvX = false;
static bool g_mouseRotDirectionInvY = false;

static bool g_mouseSlideDirectionInvX = false;
static bool g_mouseSlideDirectionInvY = false;

static int g_lastViewWidth = 0;
static int g_lastViewHeight = 0;


void SetZoom(float zoom) { g_Zoom = Effekseer::Max(MinZoom, Effekseer::Min(MaxZoom, zoom)); }

float GetDistance() { return DistanceBase * powf(ZoomDistanceFactor, g_Zoom); }

float GetOrthoScale() { return OrthoScaleBase / powf(ZoomDistanceFactor, g_Zoom); }

static Effekseer::Manager::DrawParameter drawParameter;
static ::Effekseer::Vector3D g_focus_position;
Effekseer::Vector3D cameraPosition = ::Effekseer::Vector3D(0.0f, 50.0f, 200.0f);

EffekseerManagerCore::~EffekseerManagerCore() {
    if (manager_ != nullptr) {
        manager_->Destroy();
        manager_ = nullptr;
    }

    if (renderer_ != nullptr) {
        renderer_->Destroy();
        renderer_ = nullptr;
    }
}

bool EffekseerManagerCore::Initialize(int32_t spriteMaxCount, int32_t id) {
    if (manager_ != nullptr || renderer_ != nullptr) {
        return false;
    }

    manager_ = ::Effekseer::Manager::Create(spriteMaxCount);


    if (id == 2) {
        openglDeviceType = EffekseerRendererGL::OpenGLDeviceType::OpenGL2;


    }

    if (id == 3) {
        openglDeviceType = EffekseerRendererGL::OpenGLDeviceType::OpenGL3;

    }


    if (id == 4) {
        openglDeviceType = EffekseerRendererGL::OpenGLDeviceType::OpenGLES2;

    }


    if (id == 5) {
        openglDeviceType = EffekseerRendererGL::OpenGLDeviceType::OpenGLES3;

    }


    renderer_ = ::EffekseerRendererGL::Renderer::Create(spriteMaxCount, openglDeviceType);


    auto device = EffekseerRendererGL::CreateDevice(openglDeviceType);


    if (manager_ == nullptr || renderer_ == nullptr) {
        ES_SAFE_RELEASE(manager_);
        ES_SAFE_RELEASE(renderer_);
        return false;
    }


    manager_->SetSpriteRenderer(renderer_->CreateSpriteRenderer());
    manager_->SetRibbonRenderer(renderer_->CreateRibbonRenderer());
    manager_->SetRingRenderer(renderer_->CreateRingRenderer());
    manager_->SetTrackRenderer(renderer_->CreateTrackRenderer());
    manager_->SetModelRenderer(renderer_->CreateModelRenderer());


    auto settingCore = EffekseerSettingCore::create();

    settingCore->SetModelLoader(renderer_->CreateModelLoader());
    settingCore->SetMaterialLoader(renderer_->CreateMaterialLoader());
    settingCore->SetTextureLoader(renderer_->CreateTextureLoader());

    if (settingCore == nullptr) {
        ES_SAFE_RELEASE(settingCore);
        return false;
    }


    renderer_->SetRenderMode(Effekseer::RenderMode::Normal);
    settingCore->SetCoordinateSystem(Effekseer::CoordinateSystem::RH);

    manager_->SetSetting(settingCore);


    return true;
}

void EffekseerManagerCore::Update(float deltaFrames) {
    if (manager_ == nullptr) {
        return;
    }

    deltaFrames += restDeltaTime_;
    restDeltaTime_ = deltaFrames - int(deltaFrames);
    for (int loop = 0; loop < int(deltaFrames); loop++) {

        manager_->Update(1);



    }
}

int EffekseerManagerCore::Play(EffekseerEffectCore *effect) {
    if (manager_ == nullptr) {
        return -1;
    }

    return manager_->Play(effect->GetInternal(), 0, 0, 0);
}


bool EffekseerManagerCore::isPlaing(int handle) {
    if (manager_ == nullptr) {
        return false;
    }

    return manager_->GetShown(handle);
}


void EffekseerManagerCore::SetEffectPosition(int handle, float x, float y, float z) {
    manager_->SetLocation(handle, x, y, z);

}
void EffekseerManagerCore::SetEffectRoate(int handle, float x, float y, float z) {
    manager_->SetRotation(handle, x, y, z);
}


void EffekseerManagerCore::SetEffectScale(int handle, float x, float y, float z) {
    manager_->SetScale(handle, x, y, z);
}

void EffekseerManagerCore::SetCameraPosition(float x, float y, float z) {



    drawParameter.CameraPosition.X = x;
    drawParameter.CameraPosition.Y = y;
    drawParameter.CameraPosition.Z = z;


  //  std::cout << z << std::endl;



}

void EffekseerManagerCore::SetCameraRotate(float x, float y, float z) {

    drawParameter.CameraDirection .X = x;
    drawParameter.CameraDirection.Y = y;
    drawParameter.CameraDirection.Z = z;


}

void EffekseerManagerCore::DrawBack() {
    if (manager_ == nullptr) {
        return;
    }


    renderer_->BeginRendering();

    manager_->DrawBack(drawParameter);

    renderer_->EndRendering();

}

void EffekseerManagerCore::DrawFront() {
    if (manager_ == nullptr) {
        return;
    }

    renderer_->BeginRendering();
    manager_->DrawFront(drawParameter);
    renderer_->EndRendering();

}

void
EffekseerManagerCore::SetViewProjectionMatrixWithSimpleWindowOrthogonal(int32_t windowWidth, int32_t windowHeight) {
    if (manager_ == nullptr) {
        return;
    }

    renderer_->SetProjectionMatrix(
            ::Effekseer::Matrix44().OrthographicRH(static_cast<float>(windowWidth), static_cast<float>(windowHeight),
                                                   1.0f, 400.0f));

    renderer_->SetCameraMatrix(
            ::Effekseer::Matrix44().LookAtRH(::Effekseer::Vector3D(windowWidth / 2.0f, windowHeight / 2.0f, 200.0f),
                                             ::Effekseer::Vector3D(windowWidth / 2.0f, windowHeight / 2.0f, -200.0f),
                                             ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));
}

void
EffekseerManagerCore::SetViewProjectionMatrixWithSimpleWindowPerspective(float_t windowWidth, float_t windowHeight,float_t up[],float_t nea, float_t faer) {

    if (manager_ == nullptr) {
        return;
    }


    renderer_->SetProjectionMatrix(
            ::Effekseer::Matrix44().PerspectiveFovRH_OpenGL(67.0f / 180.0f * 3.14f, (float) windowWidth / (float) windowHeight,
                                                     nea, faer));




    renderer_->SetCameraMatrix(
            ::Effekseer::Matrix44().LookAtRH(

                    drawParameter.CameraPosition,
                    ::Effekseer::Vector3D(0.0f,0.0f,0.0f),
                    ::Effekseer::Vector3D(up[0], up[1], up[2])));





}





void EffekseerManagerCore::UpdateWindowR() {


    assert(manager_ != NULL);
    assert(renderer_ != NULL);

    ::Effekseer::Vector3D position(0, 0, GetDistance());
    ::Effekseer::Matrix43 mat, mat_rot_x, mat_rot_y;


    mat_rot_x.RotationX(-g_RotX / 180.0f * PI);


    mat_rot_y.RotationY(-g_RotY / 180.0f * PI);
    ::Effekseer::Matrix43::Multiple(mat, mat_rot_x, mat_rot_y);
    ::Effekseer::Vector3D::Transform(position, position, mat);

    Effekseer::Vector3D::Normal(drawParameter.CameraDirection, position);

    position.X += g_focus_position.X;
    position.Y += g_focus_position.Y;
    position.Z += g_focus_position.Z;

    ::Effekseer::Matrix44 cameraMat;
    renderer_->SetCameraMatrix(
            ::Effekseer::Matrix44().LookAtRH(position, g_focus_position, ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

    drawParameter.CameraPosition = position;


    manager_->Draw(drawParameter);

}


void EffekseerManagerCore::UpdateWindowL() {


    assert(manager_ != NULL);
    assert(renderer_ != NULL);

    ::Effekseer::Vector3D position(0, 0, GetDistance());
    ::Effekseer::Matrix43 mat, mat_rot_x, mat_rot_y;


    mat_rot_x.RotationX(-g_RotX / 180.0f * PI);


    mat_rot_y.RotationY((g_RotY + 180.0f) / 180.0f * PI);


    ::Effekseer::Matrix43::Multiple(mat, mat_rot_x, mat_rot_y);
    ::Effekseer::Vector3D::Transform(position, position, mat);
    ::Effekseer::Vector3D temp_focus = g_focus_position;


    temp_focus.Z = -temp_focus.Z;

    Effekseer::Vector3D::Normal(drawParameter.CameraDirection, position);

    position.X += temp_focus.X;
    position.Y += temp_focus.Y;
    position.Z += temp_focus.Z;


    renderer_->SetCameraMatrix(
            ::Effekseer::Matrix44().LookAtLH(position, temp_focus, ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

    drawParameter.CameraPosition = position;




    manager_->Draw(drawParameter);


}

void EffekseerManagerCore::setPause(int i,bool pause) {

    manager_->SetPaused(i,pause);
}






