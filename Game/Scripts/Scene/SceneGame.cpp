#include "SceneGame.h"

#include <Engine/Assets/Shader/ShaderLibrary.h>
#include <Engine/Module/Render/RenderNode/Debug/PrimitiveLine/PrimitiveLineNode.h>
#include <Engine/Module/Render/RenderNode/Deferred/DeferredAdaptor.h>
#include <Engine/Module/Render/RenderNode/Deferred/Lighting/DirectionalLighingNode.h>
#include <Engine/Module/Render/RenderNode/Deferred/Lighting/NonLightingPixelNode.h>
#include <Engine/Module/Render/RenderNode/Deferred/Mesh/SkinningMeshNodeDeferred.h>
#include <Engine/Module/Render/RenderNode/Deferred/Mesh/StaticMeshNodeDeferred.h>
#include <Engine/Module/Render/RenderNode/Forward/Particle/ParticleBillboardNode/ParticleBillboardNode.h>
#include <Engine/Module/Render/RenderNode/Forward/Primitive/Rect3dNode.h>

#include <Engine/Module/World/Mesh/SkinningMeshInstance.h>
#include <Engine/Module/World/Mesh/StaticMeshInstance.h>

#include <Engine/Assets/Animation/NodeAnimation/NodeAnimationLibrary.h>
#include <Engine/Assets/Animation/Skeleton/SkeletonLibrary.h>
#include <Engine/Assets/Audio/AudioLibrary.h>
#include <Engine/Assets/PolygonMesh/PolygonMeshLibrary.h>
#include <Engine/Assets/Texture/TextureLibrary.h>

#include <Engine/Runtime/Clock/WorldClock.h>

#include <Engine/Debug/DebugValues/DebugValues.h>

#include "Scripts/Util/LookAtRect.h"

#include "Scripts/MiscInstance/Enemy/Enemy.h"
#include "Scripts/RenderNode/CubemapNode/CubemapNode.h"
#include "Scripts/RenderNode/PostEffect/BloomNode.h"
#include "Scripts/RenderNode/PostEffect/GaussianBlurNode.h"
#include "Scripts/RenderNode/PostEffect/LuminanceExtractionNode.h"
#include "Scripts/RenderNode/PostEffect/MargeTextureNode.h"

void SceneGame::load() {
	PolygonMeshLibrary::RegisterLoadQue("./Game/Resources/Game/Models/skydome.gltf");
	PolygonMeshLibrary::RegisterLoadQue("./Game/Resources/Game/Models/Comet.obj");
	PolygonMeshLibrary::RegisterLoadQue("./Game/Resources/Game/Models/Player.gltf");
	NodeAnimationLibrary::RegisterLoadQue("./Game/Resources/Game/Models/Player.gltf");
	SkeletonLibrary::RegisterLoadQue("./Game/Resources/Game/Models/Player.gltf");
	PolygonMeshLibrary::RegisterLoadQue("./Game/Resources/Game/Models/RedComet.gltf");
	NodeAnimationLibrary::RegisterLoadQue("./Game/Resources/Game/Models/RedComet.gltf");
	SkeletonLibrary::RegisterLoadQue("./Game/Resources/Game/Models/RedComet.gltf");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/Circle.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/white.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/shadow.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/AOEBase.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/DustCloud1.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/DustCloud2.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/Fire.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/CometGround1.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/CometGround2.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/CometGround3.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/PlayerEffect/PaladinHolySpiritEffectTargetCenter6.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/PlayerEffect/PaladinHolySpiritEffectTargetShining.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/PlayerEffect/PaladinHolySpiritEffectTargetAbsorption.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/PlayerEffect/PaladinHolySpiritEffectTargetLight.png");
	TextureLibrary::RegisterLoadQue("./Game/Resources/Game/Texture/rogland_clear_night_2k.dds");

	PolygonMeshLibrary::RegisterLoadQue(".\\DirectXGame\\EngineResources\\Models\\Grid\\Grid.obj");

	ShaderLibrary::RegisterLoadQue("./DirectXGame/EngineResources/HLSL/FullscreenShader.VS.hlsl");
	ShaderLibrary::RegisterLoadQue("./DirectXGame/EngineResources/HLSL/Deferred/Mesh/StaticMesh.VS.hlsl");
	ShaderLibrary::RegisterLoadQue("./DirectXGame/EngineResources/HLSL/Deferred/Mesh/SkinningMesh.VS.hlsl");
	ShaderLibrary::RegisterLoadQue("./DirectXGame/EngineResources/HLSL/Deferred/Deferred.PS.hlsl");
	ShaderLibrary::RegisterLoadQue("./DirectXGame/EngineResources/HLSL/Deferred/Lighting/NonLighting.PS.hlsl");
	ShaderLibrary::RegisterLoadQue("./DirectXGame/EngineResources/HLSL/Deferred/Lighting/DirectionalLighting.PS.hlsl");
	ShaderLibrary::RegisterLoadQue("./DirectXGame/EngineResources/HLSL/Deferred/Lighting/PointLighting.PS.hlsl");
	ShaderLibrary::RegisterLoadQue("./DirectXGame/EngineResources/HLSL/Forward/Primitive/Rect3d.VS.hlsl");
	ShaderLibrary::RegisterLoadQue("./DirectXGame/EngineResources/HLSL/Forward/ForwardAlpha.PS.hlsl");
	ShaderLibrary::RegisterLoadQue("./DirectXGame/EngineResources/HLSL/Forward/Particle/ParticleBillboard/ParticleBillboard.VS.hlsl");
	ShaderLibrary::RegisterLoadQue("./DirectXGame/EngineResources/HLSL/Forward/Particle/ParticleBillboard/ParticleBillboard.PS.hlsl");

	ShaderLibrary::RegisterLoadQue("./DirectXGame/EngineResources/HLSL/Posteffect/RadialBlur/RadialBlur.PS.hlsl");

	ShaderLibrary::RegisterLoadQue("./Game/Resources/HLSL/Mesh/Skybox/Skybox.VS.hlsl");
	ShaderLibrary::RegisterLoadQue("./Game/Resources/HLSL/Mesh/Skybox/Skybox.PS.hlsl");
	ShaderLibrary::RegisterLoadQue("./Game/Resources/HLSL/Bloom.PS.hlsl");
	ShaderLibrary::RegisterLoadQue("./Game/Resources/HLSL/DownSampling.PS.hlsl");
	ShaderLibrary::RegisterLoadQue("./Game/Resources/HLSL/GaussianBlur.PS.hlsl");
	ShaderLibrary::RegisterLoadQue("./Game/Resources/HLSL/LuminanceExtraction.PS.hlsl");
	ShaderLibrary::RegisterLoadQue("./Game/Resources/HLSL/MargeTexture4.PS.hlsl");
}

void SceneGame::initialize() {
	// WorldManager
	worldManager = eps::CreateUnique<WorldManager>();
	entityManager = eps::CreateUnique<EntityManager>();
	enemyManager = eps::CreateUnique<EnemyManager>();
	effectManager = eps::CreateUnique<EffectManager>();

	// DrawManager
	skinningMeshDrawManager = eps::CreateUnique<SkinningMeshDrawManager>();
	skinningMeshDrawManager->initialize(1);

	staticMeshDrawManager = eps::CreateUnique<StaticMeshDrawManager>();
	staticMeshDrawManager->initialize(1);

	rect3dDrawManager = eps::CreateUnique<Rect3dDrawManager>();
	rect3dDrawManager->initialize(1);
	rect3dDrawManager->make_instancing(0, 1024);
	//rect3dDrawManager->make_instancing(0, PrimitiveBlendMode::Add, 100);
	//rect3dDrawManager->make_instancing(0, PrimitiveBlendMode::Alpha, 100);

	directionalLightingExecutor = eps::CreateUnique<DirectionalLightingExecutor>(1);

	entityManager->setup(worldManager, skinningMeshDrawManager, rect3dDrawManager);
	enemyManager->setup(entityManager);
	effectManager->setup(staticMeshDrawManager, rect3dDrawManager);

	// WorldInstances
	// Allocation
	directionalLight = worldManager->create<DirectionalLightInstance>();
	player = entityManager->generate<Player>(0, "Player.json");
	skydome = worldManager->create<StaticMeshInstance>(nullptr, "skydome.gltf");
	camera3D = worldManager->create<FollowCamera>();

	LookAtRect::camera = camera3D;
	Particle::lookAtDefault = camera3D.get();
	CometEffect::camera = camera3D;

	skydome->get_transform().set_scale(CVector3::BASIS * 100);
	skydome->get_materials()[0].lightingType = LighingType::None;
	skydome->set_active(false);
	camera3D->initialize();
	camera3D->set_offset({ 0,1,-40 });
	camera3D->set_target(player);
	enemyManager->generate(1, "RedComet.json", Vector3{ 0,0,8 });

	localPlayerCommandHandler = std::make_unique<LocalPlayerCommandHandler>();
	localPlayerCommandHandler->initialize(player);
	localPlayerCommandHandler->start(camera3D);

	// RenderPath
	renderTextures.resize(10);
	renderTextures[0].initialize(DeferredAdaptor::DXGI_FORMAT_LIST[0]);
	renderTextures[1].initialize(DeferredAdaptor::DXGI_FORMAT_LIST[1]);
	renderTextures[2].initialize(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB); // シーン結果
	renderTextures[3].initialize(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB); // ラジアルブラー
	renderTextures[4].initialize(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB); // 輝度抽出
	renderTextures[5].initialize(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, EngineSettings::CLIENT_WIDTH / 2, EngineSettings::CLIENT_HEIGHT / 2); // ダウンサンプリング 1/2
	renderTextures[6].initialize(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, EngineSettings::CLIENT_WIDTH / 4, EngineSettings::CLIENT_HEIGHT / 4); // ダウンサンプリング 1/4
	renderTextures[7].initialize(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, EngineSettings::CLIENT_WIDTH / 8, EngineSettings::CLIENT_HEIGHT / 8); // ダウンサンプリング 1/8
	renderTextures[8].initialize(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, EngineSettings::CLIENT_WIDTH / 16, EngineSettings::CLIENT_HEIGHT / 16); // ダウンサンプリング 1/16
	renderTextures[9].initialize(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB); // ダウンサンプリングを合成
	gBuffer.initialize({ renderTextures[0],renderTextures[1] });
	baseRenderTexture.initialize(renderTextures[2]);
	radialBlurRenderTexture.initialize(renderTextures[3]);
	luminanceRenderTexture.initialize(renderTextures[4]);
	downSampleRenderTexture2.initialize(renderTextures[5]);
	downSampleRenderTexture4.initialize(renderTextures[6]);
	downSampleRenderTexture8.initialize(renderTextures[7]);
	downSampleRenderTexture16.initialize(renderTextures[8]);
	bloomBaseRenderTexture.initialize(renderTextures[9]);

	auto deferredMeshNode = eps::CreateShared<StaticMeshNodeDeferred>();
	deferredMeshNode->initialize();
	deferredMeshNode->set_render_target(gBuffer);

	auto skinMeshNodeDeferred = eps::CreateShared<SkinningMeshNodeDeferred>();
	skinMeshNodeDeferred->initialize();
	skinMeshNodeDeferred->set_render_target(gBuffer);
	skinMeshNodeDeferred->set_config(RenderNodeConfig::NoClearRenderTarget | RenderNodeConfig::NoClearDepth);

	auto nonLightingPixelNode = eps::CreateShared<NonLightingPixelNode>();
	nonLightingPixelNode->initialize();
	nonLightingPixelNode->set_render_target(baseRenderTexture);
	nonLightingPixelNode->set_gbuffers(renderTextures[0]);

	auto directionalLightingNode = eps::CreateShared<DirectionalLightingNode>();
	directionalLightingNode->initialize();
	directionalLightingNode->set_config(RenderNodeConfig::NoClearRenderTarget | RenderNodeConfig::NoClearDepth);
	directionalLightingNode->set_render_target(baseRenderTexture);
	directionalLightingNode->set_gbuffers({ renderTextures[0], renderTextures[1] });

	auto cubemapNode = eps::CreateShared<CubemapNode>();
	cubemapNode->initialize();
	cubemapNode->set_cubemap_texture("rogland_clear_night_2k.dds");
	cubemapNode->set_camera(camera3D);
	cubemapNode->set_render_target(baseRenderTexture);
	cubemapWorld = cubemapNode->get_world();
	cubemapNode->set_config(RenderNodeConfig::NoClearRenderTarget | RenderNodeConfig::NoClearDepth);

	auto rect3dNode = eps::CreateShared<Rect3dNode>();
	rect3dNode->initialize();
	rect3dNode->set_render_target(baseRenderTexture);
	rect3dNode->set_config(RenderNodeConfig::NoClearRenderTarget | RenderNodeConfig::NoClearDepth);

	std::shared_ptr<ParticleBillboardNode> particleBillboardNode;
	particleBillboardNode = std::make_unique<ParticleBillboardNode>();
	particleBillboardNode->initialize();
	particleBillboardNode->set_config(RenderNodeConfig::NoClearRenderTarget | RenderNodeConfig::NoClearDepth);
	particleBillboardNode->set_render_target(baseRenderTexture);

	radialBlurNode = eps::CreateShared<RadialBlurNode>();
	radialBlurNode->initialize();
	radialBlurNode->set_render_target(radialBlurRenderTexture);
	radialBlurNode->set_texture_resource(renderTextures[2]);

	luminanceExtractionNode = eps::CreateShared<LuminanceExtractionNode>();
	luminanceExtractionNode->initialize();
	luminanceExtractionNode->set_render_target(luminanceRenderTexture);
	luminanceExtractionNode->set_texture_resource(renderTextures[3]);

	gaussianBlurNode2 = eps::CreateShared<GaussianBlurNode>();
	gaussianBlurNode2->initialize();
	gaussianBlurNode2->set_render_target(downSampleRenderTexture2);
	gaussianBlurNode2->set_base_texture(renderTextures[4]);

	gaussianBlurNode4 = eps::CreateShared<GaussianBlurNode>();
	gaussianBlurNode4->initialize();
	gaussianBlurNode4->set_render_target(downSampleRenderTexture4);
	gaussianBlurNode4->set_base_texture(renderTextures[5]);

	gaussianBlurNode8 = eps::CreateShared<GaussianBlurNode>();
	gaussianBlurNode8->initialize();
	gaussianBlurNode8->set_render_target(downSampleRenderTexture8);
	gaussianBlurNode8->set_base_texture(renderTextures[6]);

	gaussianBlurNode16 = eps::CreateShared<GaussianBlurNode>();
	gaussianBlurNode16->initialize();
	gaussianBlurNode16->set_render_target(downSampleRenderTexture16);
	gaussianBlurNode16->set_base_texture(renderTextures[7]);

	margeTextureNode = eps::CreateShared<MargeTextureNode>();
	margeTextureNode->initialize();
	margeTextureNode->set_render_target(bloomBaseRenderTexture);
	margeTextureNode->set_texture_resources({ renderTextures[5] ,renderTextures[6] ,renderTextures[7], renderTextures[8] });

	bloomNode = eps::CreateShared<BloomNode>();
	bloomNode->initialize();
	bloomNode->set_render_target_SC();
	bloomNode->set_base_texture(renderTextures[3]);
	bloomNode->set_blur_texture(renderTextures[9]);

#ifdef DEBUG_FEATURES_ENABLE
	std::shared_ptr<PrimitiveLineNode> primitiveLineNode;
	primitiveLineNode = std::make_unique<PrimitiveLineNode>();
	primitiveLineNode->initialize();
#endif // _DEBUG

	renderPath = eps::CreateUnique<RenderPath>();
#ifdef DEBUG_FEATURES_ENABLE
	renderPath->initialize({ deferredMeshNode,skinMeshNodeDeferred,nonLightingPixelNode,directionalLightingNode, cubemapNode,rect3dNode,particleBillboardNode,
		radialBlurNode, luminanceExtractionNode, gaussianBlurNode2, gaussianBlurNode4, gaussianBlurNode8, gaussianBlurNode16 , margeTextureNode, bloomNode,primitiveLineNode });
#else
	renderPath->initialize({ deferredMeshNode,skinMeshNodeDeferred,nonLightingPixelNode,directionalLightingNode, cubemapNode,rect3dNode,particleBillboardNode,
		radialBlurNode, luminanceExtractionNode, gaussianBlurNode2, gaussianBlurNode4, gaussianBlurNode8, gaussianBlurNode16 , margeTextureNode, bloomNode });
#endif // DEFERRED_RENDERING

	// CreateInstancing
	skinningMeshDrawManager->make_instancing(0, "Player.gltf", 1);
	skinningMeshDrawManager->make_instancing(0, "Enemy.gltf", 100);
	skinningMeshDrawManager->make_instancing(0, "RedComet.gltf", 1);
	staticMeshDrawManager->make_instancing(0, "skydome.gltf", 1);
	staticMeshDrawManager->make_instancing(0, "Comet.obj", 100);
	staticMeshDrawManager->make_instancing(0, "Grid.obj", 1);

	// RegisterDraw
#ifdef DEBUG_FEATURES_ENABLE
	staticMeshDrawManager->register_debug_instance(0, camera3D, true);
#else
	staticMeshDrawManager->register_instance(DebugValues::GetGridInstance());
#endif // DEBUG_FEATURES_ENABLE
	staticMeshDrawManager->register_instance(skydome);

	inputHandler.initialize({ PadID::A });
}

void SceneGame::begin() {
	timer.ahead();

	localPlayerCommandHandler->begin();
	entityManager->begin();
	camera3D->input();
}

void SceneGame::update() {
	localPlayerCommandHandler->update();

	localPlayerCommandHandler->run();

	entityManager->update();
	camera3D->update();

	inputHandler.update();
	actionTimer.back();
	if (inputHandler.trigger(PadID::A) && actionTimer < 0) {
		actionTimer.set(2.5f);
		auto effect = paladinHolySpirit->on_impact(player, enemyManager->get_nearest(player->world_position()).ptr(), worldManager);
		for (auto& elem : effect) {
			effectManager->register_instance(std::move(elem));
		}
	}

	effectManager->update();

	if (std::fmodf(timer.time(), 7.0f) <= WorldClock::DeltaSeconds()) {
		auto& temp = comets.emplace_back(
			worldManager->create<CircleAoe>(),
			worldManager->create<CometEffect>()
		);
		temp.circleAoE->initialize(player->world_position(), 7, 3);
		temp.circleAoE->start(rect3dDrawManager);
		temp.cometEffect->initialize(player->world_position(), radialBlurNode->data());
		temp.cometEffect->setup(staticMeshDrawManager, rect3dDrawManager);
	}

	std::erase_if(comets, [&](CometAction& elem) {
		if (elem.cometEffect->is_end()) {
			elem.circleAoE->end(rect3dDrawManager);
			elem.cometEffect->terminate(staticMeshDrawManager, rect3dDrawManager);
			return true;
		}
		return false;
	});

	for (auto& comet : comets) {
		comet.circleAoE->update();
		if (comet.circleAoE->is_end()) {
			comet.cometEffect->update();
		}
	}
}

void SceneGame::late_update() {
	entityManager->late_update();

	*cubemapWorld = camera3D->world_position();
}

void SceneGame::begin_rendering() {

	worldManager->update_matrix();

	directionalLight->transfer();
	camera3D->transfer();

	directionalLightingExecutor->begin();
	directionalLightingExecutor->write_to_buffer(directionalLight);
	rect3dDrawManager->transfer();
	staticMeshDrawManager->transfer();
	skinningMeshDrawManager->transfer();
}

void SceneGame::draw() const {
	// 3DMesh
	renderPath->begin();
	camera3D->register_world_projection(2);
	staticMeshDrawManager->draw_layer(0);

	// SkinMesh
	renderPath->next();
	camera3D->register_world_projection(2);
	skinningMeshDrawManager->draw_layer(0);

	// NonLightingPixel
	renderPath->next();

	// DirectionalLight
	renderPath->next();
	camera3D->register_world_lighting(1);
	directionalLightingExecutor->draw_command();

	// Skybox
	renderPath->next();

	// Rect3D
	renderPath->next();
	camera3D->register_world_projection(3);
	camera3D->register_world_lighting(4);
	directionalLightingExecutor->set_command(5);
	rect3dDrawManager->draw_layer(0);

	// ParticleBillboard
	renderPath->next();
	camera3D->register_world_projection(1);
	for (const auto& comet : comets) {
		comet.cometEffect->draw_particle();
	}
	effectManager->draw_particle();

	// ラジアルブラー
	renderPath->next();
	radialBlurNode->draw();

	// 輝度抽出
	renderPath->next();
	luminanceExtractionNode->draw();

	// ダウンサンプリング2
	renderPath->next();
	gaussianBlurNode2->draw();

	// ダウンサンプリング4
	renderPath->next();
	gaussianBlurNode4->draw();

	// ダウンサンプリング8
	renderPath->next();
	gaussianBlurNode8->draw();

	// ダウンサンプリング16
	renderPath->next();
	gaussianBlurNode16->draw();

	// 統合
	renderPath->next();
	margeTextureNode->draw();

	// ブルーム
	renderPath->next();
	bloomNode->draw();

	renderPath->next();

#ifdef DEBUG_FEATURES_ENABLE
	// LineDraw
	camera3D->register_world_projection(1);
	camera3D->debug_draw_frustum();

	renderPath->next();
#endif // DEFERRED_RENDERING
}

#ifdef DEBUG_FEATURES_ENABLE
void SceneGame::debug_update() {
	ImGui::Begin("Camera3D");
	camera3D->debug_gui();
	ImGui::End();

	ImGui::Begin("WorldClock");
	WorldClock::DebugGui();
	ImGui::End();

	ImGui::Begin("DirectionalLight");
	directionalLight->debug_gui();
	ImGui::End();

	ImGui::Begin("Player");
	player->debug_gui();
	ImGui::End();

	enemyManager->debug_gui();

	ImGui::Begin("Blur");
	radialBlurNode->debug_gui();
	ImGui::End();

	ImGui::Begin("Test");
	effectManager->debug_gui();
	ImGui::End();
}

#endif // DEFERRED_RENDERING