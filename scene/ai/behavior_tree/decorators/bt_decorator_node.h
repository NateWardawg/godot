
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

public:

	virtual void update_child_nodes();
	virtual void reset_node() {
		if ( leaf_node != NULL ) {
			leaf_node->reset_node();
		}
	}

};

#endif // BT_DECORATOR_NODE_H
