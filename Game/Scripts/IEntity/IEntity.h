#pragma once

#include <Engine/Module/World/Mesh/SkinningMeshInstance.h>
#include <Engine/Module/DrawExecutor/Mesh/Primitive/Rect3dDrawManager.h>
#include <Engine/Module/DrawExecutor/Mesh/SkinningMeshDrawManager.h>

#include <Library/Utility/Template/Reference.h>
#include <Library/Utility/Template/bitflag.h>

#include <memory>
#include <vector>

#include "IActionBasic.h"
#include "EntityUi.h"
#include "Shadow.h"

enum class EntityFlag {
	Idle = 0b00001, // 通常待機
	Battle = 0b00010, // バトル状態
	Dead = 0b00100, // 死亡状態
	Invisible = 0b01000, // 不可視
	Invincible = 0b10000, // 無敵

	Default = Idle,
	Targetable = Idle | Battle,
	ShowEnmityList = Battle | Invincible,
};

__USE_BITFLAG(EntityFlag)

class IEntity : public SkinningMeshInstance {
public:
	void initialize(const std::filesystem::path& file);
	void start(
		Reference<SkinningMeshDrawManager> skinDraw,
		Reference<Rect3dDrawManager> rectDraw);
	virtual void begin() override;

	virtual void update() override;

public:
	void start_action(u32 index);
	void move(const Vector2& xzDirection);
	void jump();
	void on_damaged(i32 damage);
	void sync_position(Vector3 position, r32 yAngle);

public:
	r32 target_radius() const;

protected:
	void set_action(Reference<IActionBasic> action);
	const std::vector<u64>& get_enmity_ids() const { return enmityIds; };

protected:
	u64 id;
	i32 hitpoint;

	r32 targetRadius{};

	Vector3 velocity;
	r32 SPEED{ 5.0f };

	eps::bitflag<EntityFlag> flags;

	std::unique_ptr<EntityUi> ui;
	std::unique_ptr<Shadow> shadow;
	
	Reference<IEntity> selectionTarget; // 選択対象
	std::vector<u64> enmityIds; // 敵対一覧

	Reference<IActionBasic> nowAction{ nullptr }; // 今のアクション

	std::unique_ptr<IActionBasic> idleAction;
	std::unique_ptr<IActionBasic> fightAction;
	std::unique_ptr<IActionBasic> damagedAction;
	std::vector<std::unique_ptr<IActionBasic>> actionList;

public:
	Reference<IActionBasic> now_action() const { return nowAction; }
};
