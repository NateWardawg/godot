
#ifndef AI_LEAF_NODE_H
#define AI_LEAF_NODE_H

#include "../ai_behavior_tree.h"


class AILeafNode : public AIBehaviorTree {

	OBJ_TYPE( AILeafNode, AIBehaviorTree )
	OBJ_CATEGORY("AI")

protected:

	void _notification(int p_what);
};

#endif
