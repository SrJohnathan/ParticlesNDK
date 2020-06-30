#pragma once

#include <Effekseer.h>
#include "EffekseerRendererGL.h"



class EffekseerSettingCore : public ::Effekseer::Setting {



private:
    static EffekseerSettingCore *effekseerSetting_;
    EffekseerRenderer::GraphicsDevice *graphicsDevice_ = nullptr;

public:

    EffekseerSettingCore();
    ~EffekseerSettingCore();
    EffekseerRenderer::GraphicsDevice *GetGraphicsDevice() const;

    static EffekseerSettingCore *create();
};



