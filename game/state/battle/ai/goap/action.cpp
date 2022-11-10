#include "game/state/battle/ai/goap/action.h"
#include "game/state/battle/ai/goap/worldstate.h"

namespace OpenApoc
{
Action::Action(std::string name, int cost)
{
	name_ = name;
	cost_ = cost;
}

bool Action::operableOn(const WorldState &ws) const
{
	for (const auto &precond : preconditions_)
	{
		try
		{
			if (ws.vars_.at(precond.first) != precond.second)
			{
				return false;
			}
		}
		catch (const std::out_of_range &)
		{
			return false;
		}
	}
	return true;
}

WorldState Action::actOn(const WorldState &ws) const
{
	WorldState tmp(ws);
	for (const auto &effect : effects_)
	{
		tmp.setVariable(effect.first, effect.second);
	}
	return tmp;
}

void Action::setAction(std::function<void()> value)
{
	action = value;
};

void Action::act() const {
	
}

bool Action::can_act() { return true; }
} // namespace OpenApoc