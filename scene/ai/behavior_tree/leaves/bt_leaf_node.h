
#ifndef BT_LEAF_NODE_H
#define BT_LEAF_NODE_H

#include "../behavior_tree.h"


class BTLeafNode : public BehaviorTree {

	OBJ_TYPE( BTLeafNode, BehaviorTree )
	OBJ_CATEGORY("AI")

protected:

	void _notification(int p_what);
};

#endif // BT_LEAF_NODE_H
