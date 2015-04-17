#ifndef BT_INVERTER_NODE_H
#define BT_INVERTER_NODE_H

#include "bt_decorator_node.h"

class BTInverterNode : public BTDecoratorNode
{

	OBJ_TYPE( BTInverterNode, BTDecoratorNode )
	OBJ_CATEGORY("AI")

public:
	BTInverterNode();
};

#endif // BT_INVERTER_NODE_H
