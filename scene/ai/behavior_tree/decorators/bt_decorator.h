
#ifndef BT_DECORATOR_NODE_H
#define BT_DECORATOR_NODE_H

#include "../core/behavior_tree.h"
#include "../leaves/bt_leaf.h"
#include "../bt_node.h"


class BTDecorator : public BehaviorTreeNode {

	GDCLASS( BTDecorator, BehaviorTreeNode )
	OBJ_CATEGORY("AI")

protected:

	BehaviorTreeNode *leaf_node;

	void _notification(int p_what);

public:

	virtual void update_child_nodes();
	virtual void reset_node();

};

#endif // BT_DECORATOR_NODE_H
