
#ifndef BT_SEQUENCE_NODE_H
#define BT_SEQUENCE_NODE_H

#include "bt_composite_node.h"


class BTSequenceNode : public BTCompositeNode
{

	OBJ_TYPE( BTSequenceNode, BTCompositeNode )
	OBJ_CATEGORY("AI")

	int current_node;

public:

	static void _bind_methods();

	virtual int check_state();

	virtual void init_composite();

	int get_current_leaf_index();

};

#endif // BT_SEQUENCE_NODE_H
