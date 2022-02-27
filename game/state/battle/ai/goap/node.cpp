#include "game/state/battle/ai/goap/node.h"

namespace OpenApoc
{
int Node::last_id_ = 0;

Node::Node() : parent_id_(0), g_(0), h_(0), action_(nullptr) { id_ = ++last_id_; }

Node::Node(WorldState &state, int g, int h, int parent_id, const sp<Action> action)
    : ws_(state), g_(g), h_(h), parent_id_(parent_id), action_(action)
{
	id_ = ++last_id_;
}

bool operator<(const Node &lhs, const Node &rhs) { return lhs.f() < rhs.f(); }

// bool goap::Node::operator<(const Node& other) {
//    return f() < other.f();
//}
} // namespace OpenApoc