/**
 * @class Action
 * @brief Operates on the world state.
 *
 * @date  July 2014
 * @copyright (c) 2014 Prylis Inc.. All rights reserved.
 */

#pragma once
#include <string>
#include <unordered_map>
#include <functional>

class GameState;
class BattleUnit;

namespace OpenApoc
{
struct WorldState;

class Action
{
  protected:
	std::string name_; // The human-readable action name
	int cost_{};       // The numeric cost of this action

	// Preconditions are things that must be satisfied before this
	// action can be taken. Only preconditions that "matter" are here.
	std::unordered_map<int, bool> preconditions_;

	// Effects are things that happen when this action takes place.
	std::unordered_map<int, bool> effects_;

	std::function<void()> action;

  public:
	Action() = default;
	Action(std::string name, int cost);

	/**
	 Is this action eligible to operate on the given worldstate?
	 @param ws the worldstate in question
	 @return true if this worldstate meets the preconditions
	 */
	[[nodiscard]] virtual bool operableOn(const WorldState &ws) const;

	/**
	 Act on the given worldstate. Will not check for "eligiblity" and will happily
	 act on whatever worldstate you provide it.
	 @param the worldstate to act on
	 @return a copy worldstate, with effects applied
	 */
	[[nodiscard]] virtual WorldState actOn(const WorldState &ws) const;

	/**
	 Set the given precondition variable and value.
	 @param key the name of the precondition
	 @param value the value the precondition must hold
	 */
	void setPrecondition(int key, bool value) { preconditions_[key] = value; }

	/**
	 Set the given effect of this action, in terms of variable and new value.
	 @param key the name of the effect
	 @param value the value that will result
	 */
	void setEffect(int key, bool value) { effects_[key] = value; }

	void setAction(std::function<void()> value);

	int cost() const { return cost_; }

	[[nodiscard]] std::string name() const { return name_; }
	void act() const;
	bool can_act();
};

} // namespace OpenApoc