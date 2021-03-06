include $(CLEAR_VARS)

LOCAL_PATH := $(call my-dir)



LOCAL_ARM_MODE  := arm
LOCAL_PATH      := $(NDK_PROJECT_PATH)
LOCAL_MODULE    := libEffekseer
LOCAL_CFLAGS    := -O2 -D__EFFEKSEER_RENDERER_GLES2__  -funwind-tables -Wl,--no-merge-exidx-entries  -D__EFFEKSEER_RENDERER_INTERNAL_LOADER__	
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 
APP_CPPFLAGS += -fexceptions



LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/../../../Effekseer/Dev/Cpp/Effekseer \
	$(LOCAL_PATH)/../../../Effekseer/Dev/Cpp/EffekseerRendererCommon \
	$(LOCAL_PATH)/../../../Effekseer/Dev/Cpp/EffekseerRendererGL

LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/particles_EffekseerCoreJNI.cpp \
	$(LOCAL_PATH)/lib/EffekseerSettingCore.cpp \
	$(LOCAL_PATH)/lib/EffekseerBackendCore.cpp \
	$(LOCAL_PATH)/lib/EffekseerEffectCore.cpp \
	$(LOCAL_PATH)/lib/EffekseerManagerCore.cpp \
	
	
	

LIB_SRC_PATH := $(LOCAL_PATH)/../../../Effekseer/Dev/Cpp/Effekseer/Effekseer
LOCAL_SRC_FILES += \
	$(LIB_SRC_PATH)/Effekseer.Client.cpp \
	$(LIB_SRC_PATH)/Effekseer.Color.cpp \
	$(LIB_SRC_PATH)/Effekseer.DefaultEffectLoader.cpp \
	$(LIB_SRC_PATH)/Effekseer.DefaultFile.cpp \
	$(LIB_SRC_PATH)/Effekseer.Effect.cpp \
	$(LIB_SRC_PATH)/Effekseer.EffectNode.cpp \
	$(LIB_SRC_PATH)/Effekseer.EffectNodeModel.cpp \
	$(LIB_SRC_PATH)/Effekseer.EffectNodeRibbon.cpp \
	$(LIB_SRC_PATH)/Effekseer.EffectNodeRing.cpp \
	$(LIB_SRC_PATH)/Effekseer.EffectNodeRoot.cpp \
	$(LIB_SRC_PATH)/Effekseer.EffectNodeSprite.cpp \
	$(LIB_SRC_PATH)/Effekseer.EffectNodeTrack.cpp \
	$(LIB_SRC_PATH)/Effekseer.FCurves.cpp \
	$(LIB_SRC_PATH)/Effekseer.Instance.cpp \
	$(LIB_SRC_PATH)/Effekseer.InstanceContainer.cpp \
	$(LIB_SRC_PATH)/Effekseer.InstanceGlobal.cpp \
	$(LIB_SRC_PATH)/Effekseer.InstanceGroup.cpp \
	$(LIB_SRC_PATH)/Effekseer.InstanceChunk.cpp \
	$(LIB_SRC_PATH)/Effekseer.InternalScript.cpp \
	$(LIB_SRC_PATH)/Effekseer.Manager.cpp \
	$(LIB_SRC_PATH)/Effekseer.Matrix43.cpp \
	$(LIB_SRC_PATH)/Effekseer.Matrix44.cpp \
	$(LIB_SRC_PATH)/Effekseer.RectF.cpp \
	$(LIB_SRC_PATH)/Effekseer.Server.cpp \
	$(LIB_SRC_PATH)/Effekseer.Setting.cpp \
	$(LIB_SRC_PATH)/Effekseer.Socket.cpp \
	$(LIB_SRC_PATH)/Effekseer.Vector2D.cpp \
	$(LIB_SRC_PATH)/Effekseer.Vector3D.cpp \
	$(LIB_SRC_PATH)/Effekseer.WorkerThread.cpp \
	$(LIB_SRC_PATH)/Effekseer.Random.cpp \
	$(LIB_SRC_PATH)/Culling/Culling3D.Grid.cpp \
	$(LIB_SRC_PATH)/Culling/Culling3D.Layer.cpp \
	$(LIB_SRC_PATH)/Culling/Culling3D.Matrix44.cpp \
	$(LIB_SRC_PATH)/Culling/Culling3D.ObjectInternal.cpp \
	$(LIB_SRC_PATH)/Culling/Culling3D.ReferenceObject.cpp \
	$(LIB_SRC_PATH)/Culling/Culling3D.Vector3DF.cpp \
	$(LIB_SRC_PATH)/Culling/Culling3D.WorldInternal.cpp \
	$(LIB_SRC_PATH)/IO/Effekseer.EfkEfcFactory.cpp \
	$(LIB_SRC_PATH)/Material/Effekseer.CompiledMaterial.cpp \
	$(LIB_SRC_PATH)/Material/Effekseer.Material.cpp \
	$(LIB_SRC_PATH)/Material/Effekseer.MaterialCompiler.cpp \
	$(LIB_SRC_PATH)/Utils/Effekseer.CustomAllocator.cpp \
	$(LIB_SRC_PATH)/Parameter/Effekseer.Parameters.cpp \
	$(LIB_SRC_PATH)/SIMD/Effekseer.Mat43f.cpp \
	$(LIB_SRC_PATH)/SIMD/Effekseer.Mat44f.cpp \
	$(LIB_SRC_PATH)/SIMD/Effekseer.SIMDUtils.cpp

LIB_SRC_PATH := $(LOCAL_PATH)/../../../Effekseer/Dev/Cpp/EffekseerMaterialCompiler
LOCAL_SRC_FILES += \
	$(LIB_SRC_PATH)/OpenGL/EffekseerMaterialCompilerGL.cpp

LIB_SRC_PATH := $(LOCAL_PATH)/../../../Effekseer/Dev/Cpp/EffekseerRendererCommon
LOCAL_SRC_FILES += \
	$(LIB_SRC_PATH)/EffekseerRenderer.IndexBufferBase.cpp \
	$(LIB_SRC_PATH)/EffekseerRenderer.ModelRendererBase.cpp \
	$(LIB_SRC_PATH)/EffekseerRenderer.Renderer.cpp \
	$(LIB_SRC_PATH)/EffekseerRenderer.Renderer_Impl.cpp \
	$(LIB_SRC_PATH)/EffekseerRenderer.RenderStateBase.cpp \
	$(LIB_SRC_PATH)/EffekseerRenderer.RibbonRendererBase.cpp \
	$(LIB_SRC_PATH)/EffekseerRenderer.RingRendererBase.cpp \
	$(LIB_SRC_PATH)/EffekseerRenderer.SpriteRendererBase.cpp \
	$(LIB_SRC_PATH)/EffekseerRenderer.TrackRendererBase.cpp \
	$(LIB_SRC_PATH)/EffekseerRenderer.VertexBufferBase.cpp \
	$(LIB_SRC_PATH)/EffekseerRenderer.CommonUtils.cpp \
	$(LIB_SRC_PATH)/EffekseerRenderer.DDSTextureLoader.cpp \
	$(LIB_SRC_PATH)/EffekseerRenderer.PngTextureLoader.cpp \

LIB_SRC_PATH := $(LOCAL_PATH)/../../../Effekseer/Dev/Cpp/EffekseerRendererGL/EffekseerRenderer
LOCAL_SRC_FILES += \
	$(LIB_SRC_PATH)/EffekseerRendererGL.DeviceObject.cpp \
	$(LIB_SRC_PATH)/EffekseerRendererGL.GLExtension.cpp \
	$(LIB_SRC_PATH)/EffekseerRendererGL.IndexBuffer.cpp \
	$(LIB_SRC_PATH)/EffekseerRendererGL.ModelLoader.cpp \
	$(LIB_SRC_PATH)/EffekseerRendererGL.ModelRenderer.cpp \
	$(LIB_SRC_PATH)/EffekseerRendererGL.MaterialLoader.cpp \
	$(LIB_SRC_PATH)/EffekseerRendererGL.Renderer.cpp \
	$(LIB_SRC_PATH)/EffekseerRendererGL.RenderState.cpp \
	$(LIB_SRC_PATH)/EffekseerRendererGL.Shader.cpp \
	$(LIB_SRC_PATH)/EffekseerRendererGL.TextureLoader.cpp \
	$(LIB_SRC_PATH)/EffekseerRendererGL.VertexArray.cpp \
	$(LIB_SRC_PATH)/EffekseerRendererGL.VertexBuffer.cpp \
	$(LIB_SRC_PATH)/EffekseerRendererGL.DeviceObjectCollection.cpp

include $(BUILD_SHARED_LIBRARY)