
#ifndef BT_COMPOSITE_NODE_H
#define BT_COMPOSITE_NODE_H

#include "../bt_node.h"


class BTComposite : public BehaviorTreeNode {

	OBJ_TYPE( BTComposite, BehaviorTreeNode )
	OBJ_CATEGORY("AI")

protected:

	int current_node;

	Vector<BehaviorTreeNode*> nodes;

	void _notification(int p_what);

public:

	void update_child_nodes();

	virtual void reset_node();
	virtual void init_composite();

	BTComposite();

};

#endif // BT_COMPOSITE_NODE_H
