#include "game/state/battle/ai/unitaigoap.h"
#include "game/state/battle/battle.h"
#include "game/state/battle/battleunit.h"
#include "game/state/gamestate.h"
#include "game/state/shared/aequipment.h"
#include <iostream>
#include <queue>
#include <vector>

#include "game/state/rules/battle/damage.h"

namespace OpenApoc
{

UnitAIGoap::UnitAIGoap()
{
	type = Type::GOAP;
	CreateActions();
	CreateWorldState();
}

void UnitAIGoap::CreateActions()
{
	auto attack = mksp<Action>("attack", 5);
	attack->setPrecondition(target_in_range, true);
	attack->setPrecondition(target_acquired, true);
	attack->setPrecondition(has_weapon, true);
	attack->setPrecondition(target_dead, false);
	attack->setEffect(target_dead, true);
	actions.push_back(attack);

	auto spiral = mksp<Action>("searchSpiral", 5);
	spiral->setPrecondition(target_acquired, false);
	spiral->setPrecondition(target_lost, true);
	spiral->setEffect(target_acquired, true);
	actions.push_back(spiral);

	auto serpentine = mksp<Action>("searchSerpentine", 5);
	serpentine->setPrecondition(target_acquired, false);
	serpentine->setPrecondition(target_lost, false);
	serpentine->setEffect(target_acquired, true);
	actions.push_back(serpentine);

	auto intercept = mksp<Action>("interceptTarget", 5);
	intercept->setPrecondition(target_acquired, true);
	intercept->setPrecondition(target_dead, false);
	intercept->setEffect(target_in_range, true);
	actions.push_back(intercept);

	auto detonateNearTarget = mksp<Action>("detonateNearTarget", 5);
	detonateNearTarget->setPrecondition(target_in_range, true);
	detonateNearTarget->setPrecondition(target_acquired, true);
	detonateNearTarget->setPrecondition(target_dead, false);
	detonateNearTarget->setEffect(target_dead, true);
	actions.push_back(detonateNearTarget);
}

void UnitAIGoap::CreateWorldState()
{
	// Here's the initial state...
	world_state = mksp<WorldState>();
	world_state->setVariable(target_acquired, false);
	world_state->setVariable(target_in_range, false);
	world_state->setVariable(has_weapon, false);
	world_state->setVariable(target_lost, true);
	world_state->setVariable(target_dead, false);

	// ...and the goal state
	goal_target = mksp<WorldState>();
	goal_target->setVariable(target_dead, true);
	goal_target->priority_ = 50;
}

std::queue<Action> UnitAIGoap::Plan() const
{
	try
	{
		std::queue<Action> the_plan = planner->plan(world_state, goal_target, actions);
		std::cout << "Found a path!\n";
		return the_plan;
	}
	catch (const std::exception &)
	{
		std::cout << "Sorry, could not find a path!\n";
		return std::queue<Action>();
	}
}

bool UnitAIGoap::HasTarget(GameState &state, BattleUnit &u)
{
	const auto hasTarget = !u.visibleEnemies.empty();
	return hasTarget;
}

bool UnitAIGoap::HasWeapon(GameState &state, const BattleUnit &u) const
{
	for (auto &e : u.agent->equipment)
	{
		if (!e->canBeUsed(state))
		{
			continue;
		}
		if (e->type->type == AEquipmentType::Type::Weapon)
		{
			return true;
		}
	}
	return false;
}

bool UnitAIGoap::HasGrenade(GameState &state, const BattleUnit &u) const
{
	for (auto &e : u.agent->equipment)
	{
		if (!e->canBeUsed(state))
		{
			continue;
		}
		if (e->type->type == AEquipmentType::Type::Grenade)
		{
			return true;
		}
	}
	return false;
}

void UnitAIGoap::UpdateWorldState(GameState &state, BattleUnit &u) const
{
	world_state->setVariable(target_acquired, HasTarget(state, u));
	world_state->setVariable(has_weapon, HasWeapon(state, u));
	world_state->setVariable(has_grenade, HasGrenade(state, u));
	world_state->setVariable(target_in_range, true);

	std::cout << std::endl << u.agent->name << std::endl;
	std::cout << "target_acquired " << world_state->getVariable(target_acquired) << std::endl;
	std::cout << "has_weapon " << world_state->getVariable(has_weapon) << std::endl;
	std::cout << "has_grenade " << world_state->getVariable(has_grenade) << std::endl;
	std::cout << "target_in_range " << world_state->getVariable(target_in_range) << std::endl
	          << std::endl;
}

std::tuple<AIDecision, bool> UnitAIGoap::think(GameState &state, BattleUnit &u, bool interrupt)
{
	switch (u.getAIType())
	{
		case AIType::None:
		case AIType::Civilian:
			return {};
		case AIType::PanicFreeze:
		case AIType::PanicRun:
		case AIType::Berserk:
			LogError("Calling UnitAIGOAP on panic/berserk unit!?");
			return {};
		case AIType::Loner:
		case AIType::Group:
			// Go on below
			break;
	}

	UpdateWorldState(state, u);

	if (current_plan.empty())
	{
		current_plan = Plan();
		if (!current_plan.empty())
		{
			current_action = current_plan.front();
			current_plan.pop();
		}
		else
		{
			std::cout << "current_plan empty " << std::endl;
			AIDecision decision;
			return std::make_tuple(decision, false);
		}
	}

	if (current_action.can_act() == false)
	{
		current_plan = Plan();
		current_action = current_plan.front();
		current_plan.pop();
	}

	std::cout << "current_action " << current_action.name() << std::endl;
	current_action.act();

	AIDecision decision;
	return std::make_tuple(decision, false);
}

} // namespace OpenApoc