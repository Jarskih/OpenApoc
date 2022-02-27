#pragma once
#include "game/state/battle/ai/goap/planner.h"
#include "game/state/battle/ai/goap/worldstate.h"
#include "game/state/battle/ai/unitai.h"

namespace OpenApoc
{

class UnitAIGoap : public UnitAI
{

	sp<Planner> planner = mksp<Planner>();
	std::vector<sp<Action>> actions = std::vector<sp<Action>>();
	sp<WorldState> world_state = nullptr;
	sp<WorldState> goal_target = nullptr;
	std::queue<Action> current_plan = std::queue<Action>();
	Action current_action;

	const int has_weapon = 1;
	const int target_acquired = 10;
	const int target_lost = 15;
	const int target_in_range = 20;
	const int target_dead = 30;

	void CreateActions();
	void CreateWorldState();
	[[nodiscard]] std::queue<Action> Plan() const;

  public:
	UnitAIGoap();
	virtual ~UnitAIGoap() = default;
	static bool HasTarget(GameState &state, BattleUnit &u);
	bool HasWeapon(GameState &state, const BattleUnit &battle_unit) const;
	void UpdateWorldState(GameState &state, BattleUnit &u) const;
	std::tuple<AIDecision, bool> think(GameState &state, BattleUnit &u, bool interrupt) override;
};
} // namespace OpenApoc