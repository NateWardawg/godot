
#ifndef AI_COMPOSITE_NODE_H
#define AI_COMPOSITE_NODE_H

#include "../ai_behavior_tree.h"


class AICompositeNode : public AIBehaviorTree {

	OBJ_TYPE( AICompositeNode, AIBehaviorTree )
	OBJ_CATEGORY("AI")

protected:

	void _notification(int p_what);
};

#endif
