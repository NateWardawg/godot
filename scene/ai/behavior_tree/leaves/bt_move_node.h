#ifndef BT_MOVE_NODE_H
#define BT_MOVE_NODE_H

#include "bt_leaf_node.h"

class BTMoveNode : public BTLeafNode
{

	OBJ_TYPE( BTMoveNode, BTLeafNode )
	OBJ_CATEGORY("AI")

public:
	BTMoveNode();
};

#endif // BT_MOVE_NODE_H
