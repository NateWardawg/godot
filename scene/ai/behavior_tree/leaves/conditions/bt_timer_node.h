
#ifndef BT_TIMER_NODE_H
#define BT_TIMER_NODE_H

#include "../bt_action_node.h"


class BTTimerNode : public BTActionNode
{

	OBJ_TYPE( BTTimerNode, BTActionNode )
	OBJ_CATEGORY("AI")

	real_t wait_time;

};

#endif // BT_TIMER_NODE_H
