
#ifndef BT_DECORATOR_NODE_H
#define BT_DECORATOR_NODE_H

#include "../behavior_tree.h"


class BTDecoratorNode : public BehaviorTree {

	OBJ_TYPE( BTDecoratorNode, BehaviorTree )
	OBJ_CATEGORY("AI")

protected:

	void _notification(int p_what);

};

#endif // BT_DECORATOR_NODE_H
