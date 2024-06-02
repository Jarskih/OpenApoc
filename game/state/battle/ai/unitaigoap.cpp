#include "game/state/battle/ai/unitaigoap.h"
#include "game/state/battle/battle.h"
#include "game/state/battle/battleunit.h"
#include "game/state/gamestate.h"
#include "game/state/shared/aequipment.h"
#include <iostream>
#include <queue>
#include <vector>
#include <glm/glm.hpp>
#include "game/state/rules/battle/damage.h"

namespace OpenApoc
{

UnitAIGoap::UnitAIGoap(GameState &p_state, BattleUnit &p_unit)
{
	type = Type::GOAP;
	CreateActions();
	CreateWorldState();
	state = p_state.shared_from_this();
	unit = p_unit.shared_from_this();
}

void UnitAIGoap::CreateActions()
{
	// TODO get these from Lua script

	auto search = mksp<Action>("search", 1);
	search->setPrecondition(target_visible, false);
	search->setEffect(target_visible, true);
	search->setAction([this]() { Search(); });
	actions.push_back(search);

	auto intercept = mksp<Action>("interceptTarget", 2);
	intercept->setPrecondition(target_visible, true);
	intercept->setPrecondition(target_dead, false);
	intercept->setPrecondition(target_in_range, false);
	intercept->setEffect(target_in_range, true);
	actions.push_back(intercept);

	auto takeGrenade = mksp<Action>("takeGrenade", 4);
	intercept->setPrecondition(target_visible, true);
	takeGrenade->setPrecondition(holding_grenade, false);
	takeGrenade->setEffect(holding_grenade, true);
	actions.push_back(takeGrenade);

	auto throwGrenade = mksp<Action>("throwGrenade", 5);
	intercept->setPrecondition(target_visible, true);
	throwGrenade->setPrecondition(target_in_range, true);
	throwGrenade->setPrecondition(holding_grenade, true);
	throwGrenade->setPrecondition(target_dead, false);
	throwGrenade->setEffect(target_dead, true);
	actions.push_back(throwGrenade);

	auto shoot = mksp<Action>("shoot", 3);
	intercept->setPrecondition(target_visible, true);
	shoot->setPrecondition(target_in_range, true);
	shoot->setPrecondition(has_weapon, true);
	shoot->setPrecondition(can_harm_target, true);
	shoot->setPrecondition(target_dead, false);
	shoot->setEffect(target_dead, true);
	actions.push_back(shoot);

	auto retreat = mksp<Action>("retreat", 3);
	retreat->setPrecondition(low_on_health, true);
	retreat->setPrecondition(target_visible, true);
	actions.push_back(retreat);

	auto detonateNearTarget = mksp<Action>("detonateNearTarget", 1);
	detonateNearTarget->setPrecondition(suicider, true);
	detonateNearTarget->setPrecondition(target_in_range, true);
	detonateNearTarget->setPrecondition(target_dead, false);
	detonateNearTarget->setEffect(target_dead, true);
	actions.push_back(detonateNearTarget);
}

void UnitAIGoap::CreateWorldState()
{
	// Here's the initial state...
	world_state = mksp<WorldState>();
	world_state->setVariable(target_visible, false);
	world_state->setVariable(target_in_range, false);
	world_state->setVariable(has_weapon, false);
	world_state->setVariable(target_lost, false);
	world_state->setVariable(target_dead, false);

	// ...and the goal state
	goal_target = mksp<WorldState>();
	goal_target->setVariable(target_dead, true);
	goal_target->priority_ = 50;
}

void UnitAIGoap::Search() {
	int maxIterations = 50;
	int iterationCount = 0;

	if (targetLocation != Vec3<int>(0,0,0) && glm::distance(Vec3<float>(targetLocation), unit->position) > 1)
	{
		return;
	}

	while (iterationCount++ < maxIterations)
	{
		auto lbID = pickRandom(state->rng, state->current_battle->losBlockRandomizer);

		targetLocation = state->current_battle->blockCenterPos[unit->getType()][lbID];
		bool canRun = true;
		if (!unit->agent->isMovementStateAllowed(MovementState::Running))
		{
			canRun = false;
			break;
		}
		break;
	}
	std::cout << std::endl << "-------";
	std::cout << "GAOP action: Search()" << std::endl;
	std::cout << "targetLocation: " << targetLocation << std::endl;
	std::cout << "-------" << std::endl;
}

std::vector<sp<Action>> UnitAIGoap::Plan() const
{
	try
	{
		std::vector<sp<Action>> the_plan = planner->plan(world_state, goal_target, actions);
		std::cout << "Found a path!\n";
		for (auto & item : the_plan)
		{
			std::cout << item->name() << std::endl;
		}
		return the_plan;
	}
	catch (const std::exception &)
	{
		std::cout << "Sorry, could not find a path!\n";
		return std::vector<sp<Action>>();
	}
}

bool UnitAIGoap::HasTarget(GameState &state, BattleUnit &u)
{
	auto hasTarget = !u.visibleEnemies.empty();

	for (auto &e : u.agent->equipment)
	{
		if (!e->canBeUsed(state))
		{
			continue;
		}
		if (e->type->type == AEquipmentType::Type::Brainsucker)
		{
			hasTarget = false;
			for (auto &enemy : u.visibleEnemies)
			{
				if (enemy->agent->type->immuneToBrainsuckers)
				{
					continue;
				}
				hasTarget = true;
				break;
			}
		}
		else
		{
			return hasTarget;
		}
	}

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
		if (e->type->type == AEquipmentType::Type::Weapon || e->type->type == AEquipmentType::Type::Brainsucker)
		{
			return true;
		}
	}
	return false;
}

bool UnitAIGoap::HoldingItem(GameState &state, const BattleUnit &u, int type) const
{
	if (u.agent->leftHandItem != nullptr)
	{
		if ((int)u.agent->leftHandItem->type->type == type)
		{
			return true;
		}
	}
	if (u.agent->rightHandItem != nullptr)
	{
		if ((int)u.agent->rightHandItem->type->type == type)
		{
			return true;
		}
	}
	return false;
}

void UnitAIGoap::UpdateWorldState(GameState &state, BattleUnit &u) const
{
	world_state->setVariable(target_visible, HasTarget(state, u));
	world_state->setVariable(has_weapon, HasWeapon(state, u));
	world_state->setVariable(holding_grenade, HoldingItem(state, u, (int)AEquipmentType::Type::Grenade));
	world_state->setVariable(holding_weapon,
	            HoldingItem(state, u, (int)AEquipmentType::Type::Weapon));
	world_state->setVariable(is_healing, u.isHealing);
	world_state->setVariable(is_attacking, u.isAttacking());
	world_state->setVariable(is_cloaked, u.isCloaked());
	world_state->setVariable(is_conscious, u.isConscious());
	world_state->setVariable(is_fatally_wounded, u.isFatallyWounded());

	std::cout << std::endl << u.agent->name << std::endl;
	std::cout << "target_acquired " << world_state->getVariable(target_visible) << std::endl;
	std::cout << "has_weapon " << world_state->getVariable(has_weapon) << std::endl;
	std::cout << "holding_weapon " << world_state->getVariable(holding_weapon) << std::endl;
	std::cout << "holding_grenade " << world_state->getVariable(holding_grenade) << std::endl;
	std::cout << "is_healing " << world_state->getVariable(is_healing) << std::endl;
	std::cout << "is_attacking " << world_state->getVariable(is_attacking) << std::endl;
	std::cout << "is_cloaked " << world_state->getVariable(is_cloaked) << std::endl;
	std::cout << "is_conscious " << world_state->getVariable(is_conscious) << std::endl;
	std::cout << "is_fatally_wounded " << world_state->getVariable(is_fatally_wounded) << std::endl
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
			current_action = current_plan.back();
		}
		else
		{
			std::cout << "current_plan empty " << std::endl;
			AIDecision decision;
			return std::make_tuple(decision, false);
		}
	}

	if (current_action->can_act() == false)
	{
		current_plan = Plan();
		current_action = current_plan.back();
	}

	std::cout << "----" << std::endl;
	std::cout << u.agent->name << std::endl;
	std::cout << "current_action " << current_action->name() << std::endl;
	current_action->act();

	std::vector<sp<Action>> the_plan = planner->plan(world_state, goal_target, actions);
	std::cout << std::endl;
	std::cout << "current_plan" << std::endl;
	for (auto &item : the_plan)
	{
		std::cout << item->name() << std::endl;
	}
	std::cout << "----" << std::endl;

	AIDecision decision = {};
	decision.movement->type = AIMovement::Type::Turn;
	decision.movement->targetLocation = enemyPosition;
	decision.action = current_action;
	return std::make_tuple(decision, false);
}

} // namespace OpenApoc