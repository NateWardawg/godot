
#ifndef BT_COMPOSITE_NODE_H
#define BT_COMPOSITE_NODE_H

#include "../behavior_tree.h"


class BTCompositeNode : public BehaviorTree {

	OBJ_TYPE( BTCompositeNode, BehaviorTree )
	OBJ_CATEGORY("AI")

protected:

	void _notification(int p_what);
};

#endif // BT_COMPOSITE_NODE_H
