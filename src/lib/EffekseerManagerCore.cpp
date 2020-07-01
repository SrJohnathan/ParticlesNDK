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

static Effekseer::Vector3D g_lightDirection = Effekseer::Vector3D(1, 1, 1);
const float PI = 3.14159265f;



static ::Effekseer::Matrix44 projectionmatrix,cameramatrix;


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


bool EffekseerManagerCore::IsPlaing(int handle) {
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




void EffekseerManagerCore::SetProjectionMatrix(Effekseer::Matrix44 matrix44,Effekseer::Matrix44 matrix44C , bool view,float_t width,float_t heith){

    projectionmatrix = matrix44;
    cameramatrix = matrix44C;


    if (manager_ == nullptr) {
        return;
    }

    if(view){
        renderer_->SetProjectionMatrix(projectionmatrix);
    }else{
        renderer_->SetProjectionMatrix( ::Effekseer::Matrix44().OrthographicRH(width,heith , 0.0f, 100.0f));
    }


    renderer_->SetCameraMatrix(cameramatrix);

}






void EffekseerManagerCore::DrawBack() {
    if (manager_ == nullptr) {
        return;
    }


    renderer_->BeginRendering();

    manager_->DrawBack();

    renderer_->EndRendering();

}

void EffekseerManagerCore::DrawFront() {
    if (manager_ == nullptr) {
        return;
    }

    renderer_->BeginRendering();
    manager_->DrawFront();
    renderer_->EndRendering();

}

void EffekseerManagerCore::SetPause(int i,bool pause) {
    manager_->SetPaused(i,pause);
}








