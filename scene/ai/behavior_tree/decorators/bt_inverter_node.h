#ifndef BT_INVERTER_NODE_H
#define BT_INVERTER_NODE_H

#include "bt_decorator_node.h"

class BTInverterNode : public BTDecoratorNode
{

	OBJ_TYPE( BTInverterNode, BTDecoratorNode )
	OBJ_CATEGORY("AI")

protected:

	virtual int check_state() {
		return leaf_node != NULL ? -leaf_node->process_logic() : SUCCESS;
	}

};

#endif // BT_INVERTER_NODE_H
