
#ifndef BT_DECORATOR_NODE_H
#define BT_DECORATOR_NODE_H

#include "../core/behavior_tree.h"
#include "../leaves/bt_leaf_node.h"
#include "../bt_node.h"


class BTDecoratorNode : public BehaviorTreeNode {

	OBJ_TYPE( BTDecoratorNode, BehaviorTreeNode )
	OBJ_CATEGORY("AI")

protected:

	BTLeafNode *leaf_node;

	void _notification(int p_what);

	void update_child_nodes();

};

#endif // BT_DECORATOR_NODE_H
