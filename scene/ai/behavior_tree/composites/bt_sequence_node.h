
#ifndef BT_SEQUENCE_NODE_H
#define BT_SEQUENCE_NODE_H

#include "bt_composite_node.h"


class BTSequenceNode : public BTCompositeNode
{

	OBJ_TYPE( BTSequenceNode, BTCompositeNode )
	OBJ_CATEGORY("AI")

public:
	BTSequenceNode();

	virtual void update_composite_node() { print_line("BTSequenceNode"); }

};

#endif // BT_SEQUENCE_NODE_H
