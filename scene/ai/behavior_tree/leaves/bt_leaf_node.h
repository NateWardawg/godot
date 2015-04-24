
#ifndef BT_LEAF_NODE_H
#define BT_LEAF_NODE_H

#include "../core/behavior_tree.h"
#include "../bt_node.h"


class BTLeafNode : public BehaviorTreeNode {

	OBJ_TYPE( BTLeafNode, BehaviorTreeNode )
	OBJ_CATEGORY("AI")

protected:

	void _notification(int p_what);
};

#endif // BT_LEAF_NODE_H
