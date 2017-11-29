
#ifndef BT_COMPOSITE_NODE_H
#define BT_COMPOSITE_NODE_H

#include "../bt_node.h"


class BTComposite : public BehaviorTreeNode {

	GDCLASS( BTComposite, BehaviorTreeNode )
	OBJ_CATEGORY("AI")

protected:

	Vector<BehaviorTreeNode*> nodes;

	void _notification(int p_what);

	virtual void execute();
	virtual void comp_execute() = 0;

public:

	void update_child_nodes();

	virtual void reset_node();
	virtual void init_composite();

	BTComposite();

};

#endif // BT_COMPOSITE_NODE_H
