#ifndef BT_CUSTOM_LEAF_NODE_H
#define BT_CUSTOM_LEAF_NODE_H


#include "bt_leaf.h"

class BTCustomLeaf : public BTLeaf
{

	OBJ_TYPE( BTCustomLeaf, BTLeaf )
	OBJ_CATEGORY("AI")

	virtual void execute();
	bool get_state() const { return state; }
	void set_state(const int p_state) { state = p_state; }

public:

	BTCustomLeaf();

};

#endif // BT_CUSTOM_LEAF_NODE_H
