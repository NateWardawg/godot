#ifndef BT_CUSTOM_LEAF_NODE_H
#define BT_CUSTOM_LEAF_NODE_H


#include "bt_leaf_node.h"

class BTCustomLeafNode : public BTLeafNode
{

	OBJ_TYPE( BTCustomLeafNode, BTLeafNode )
	OBJ_CATEGORY("AI")

	virtual int get_result() { return state; }
	bool get_state() const { return state; }
	void set_state(const int p_state) { state = p_state; }

	int state;

public:

	BTCustomLeafNode();

};

#endif // BT_CUSTOM_LEAF_NODE_H
