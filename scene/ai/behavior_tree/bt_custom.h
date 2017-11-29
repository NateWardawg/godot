#ifndef BT_CUSTOM_NODE_H
#define BT_CUSTOM_NODE_H


#include "bt_node.h"

class BTCustom : public BehaviorTreeNode
{

	GDCLASS( BTCustom, BehaviorTreeNode )
	OBJ_CATEGORY("AI")

	virtual void execute();
	bool get_state() const { return status; }
	void set_state(const int p_state) { status = p_state; }

public:

	BTCustom();

};

#endif // BT_CUSTOM_NODE_H
