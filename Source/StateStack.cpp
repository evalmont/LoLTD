#include <StateStack.hpp>
#include <Foreach.hpp>

#include <cassert>


StateStack::StateStack(State::Context context)
: stack_()
, pendingList_()
, context_(context)
, factories_()
{
}

void StateStack::update(sf::Time dt)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	// Draw all active states from bottom to top
	FOREACH(State::Ptr& state, stack_)
		state->draw();
}

void StateStack::handleEvent(const sf::Event& event)
{
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			break;
	}

	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
	pendingList_.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
	pendingList_.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
	pendingList_.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
	return stack_.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = factories_.find(stateID);
	assert(found != factories_.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	FOREACH(PendingChange change, pendingList_)
	{
		switch (change.action)
		{
			case Push:
				stack_.push_back(createState(change.stateID));
				break;

			case Pop:
				stack_.pop_back();
				break;

			case Clear:
				stack_.clear();
				break;
		}
	}

	pendingList_.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
: action(action)
, stateID(stateID)
{
}
