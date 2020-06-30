//
// Created by Johnathan on 27/06/2020.
//

#include "EffekseerSettingCore.h"
#include "EffekseerRendererGL.h"
#include <Effekseer.h>



EffekseerSettingCore*  EffekseerSettingCore::effekseerSetting_ = nullptr;

EffekseerSettingCore::~EffekseerSettingCore() {

    ES_SAFE_RELEASE(graphicsDevice_);
    effekseerSetting_ = nullptr;

}


EffekseerRenderer::GraphicsDevice *EffekseerSettingCore::GetGraphicsDevice() const {
    return graphicsDevice_;
}


EffekseerSettingCore *EffekseerSettingCore::create() {


    if ( effekseerSetting_ == nullptr) {

        effekseerSetting_ = new EffekseerSettingCore();
    } else {
        effekseerSetting_->AddRef();
    }

    return   effekseerSetting_;


}

EffekseerSettingCore::EffekseerSettingCore() = default;
