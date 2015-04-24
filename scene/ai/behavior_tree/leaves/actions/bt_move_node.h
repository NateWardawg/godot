
#ifndef BT_MOVE_NODE_H
#define BT_MOVE_NODE_H

#include "../bt_action_node.h"


class BTMoveNode : public BTActionNode
{

	OBJ_TYPE( BTMoveNode, BTActionNode )
	OBJ_CATEGORY("AI")

public:

	bool get_result() { return false; }

};

#endif // BT_MOVE_NODE_H
