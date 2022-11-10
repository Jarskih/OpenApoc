#pragma once
#include "game/state/battle/ai/goap/worldstate.h"
#include "game/state/battle/ai/goap/action.h"
#include "game/state/battle/ai/goap/planner.h"
#include "game/state/battle/ai/unitai.h"


#define GOAP_AI_DEBUG_OUTPUT

namespace OpenApoc
{
class UnitAIGoap : public UnitAI
{

	sp<Planner> planner = mksp<Planner>();
	std::vector<sp<Action>> actions = std::vector<sp<Action>>();
	sp<WorldState> world_state = nullptr;
	sp<WorldState> goal_target = nullptr;
	std::vector<sp<Action>> current_plan = std::vector<sp<Action>>();
	sp<Action> current_action;

	const int has_weapon = 1;
	const int holding_grenade = 2;
	const int target_visible = 3;
	const int target_lost = 4;
	const int target_in_range = 5;
	const int target_dead = 6;
	const int can_harm_target = 7;
	const int suicider = 8;
	const int low_on_health = 9;
	const int is_healing = 10;
	const int is_attacking = 11;
	const int is_cloaked = 12;
	const int is_conscious = 13;
	const int is_fatally_wounded = 14;
	const int holding_weapon = 2;

	void CreateActions();
	void CreateWorldState();
	[[nodiscard]] std::vector<sp<Action>> Plan() const;

  public:
	UnitAIGoap();
	virtual ~UnitAIGoap() = default;
	static bool HasTarget(GameState &state, BattleUnit &u);
	bool HasWeapon(GameState &state, const BattleUnit &battle_unit) const;
	bool HoldingItem(GameState &state, const BattleUnit &u, int type) const;
	void UpdateWorldState(GameState &state, BattleUnit &u) const;
	std::tuple<AIDecision, bool> think(GameState &state, BattleUnit &u, bool interrupt) override;
	void Search();
};
} // namespace OpenApoc
