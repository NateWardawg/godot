#ifndef BT_SEEK_NODE_H
#define BT_SEEK_NODE_H

#include "../bt_action_node.h"


class BTSeekNode : public BTActionNode
{

	OBJ_TYPE( BTSeekNode, BTActionNode )
	OBJ_CATEGORY("AI")

protected:

	virtual int check_state();

public:

	static void _bind_methods();

	virtual void reset_node() {}

	BTSeekNode();

};

#endif // BT_SEEK_NODE_H
