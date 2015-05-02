
#ifndef BT_COMPOSITE_NODE_H
#define BT_COMPOSITE_NODE_H

#include "../bt_node.h"


class BTCompositeNode : public BehaviorTreeNode {

	OBJ_TYPE( BTCompositeNode, BehaviorTreeNode )
	OBJ_CATEGORY("AI")

protected:

	Vector<BehaviorTreeNode*> nodes;

	void _notification(int p_what);

public:

	void update_child_nodes();

	virtual void init_composite() {}

	BTCompositeNode();

};

#endif // BT_COMPOSITE_NODE_H
