
#ifndef AI_DECORATOR_NODE_H
#define AI_DECORATOR_NODE_H

#include "../ai_behavior_tree.h"


class AIDecoratorNode : public AIBehaviorTree {

	OBJ_TYPE( AIDecoratorNode, AIBehaviorTree )
	OBJ_CATEGORY("AI")

protected:

	void _notification(int p_what);

};

#endif
