
#ifndef BT_SEQUENCE_NODE_H
#define BT_SEQUENCE_NODE_H

#include "bt_composite.h"


class BTSequence : public BTComposite
{

	GDCLASS( BTSequence, BTComposite )
	OBJ_CATEGORY("AI")

private:

	int current_node;

protected:

	virtual BehaviorStatus get_continue_status() { return SUCCESS; }
	virtual BehaviorStatus get_end_status() { return FAILURE; }
	virtual void comp_execute();

public:

	static void _bind_methods();

	virtual void init_composite() {
		current_node = 0;
		BTComposite::init_composite();
	}

	int get_current_leaf_index();
};

#endif // BT_SEQUENCE_NODE_H
