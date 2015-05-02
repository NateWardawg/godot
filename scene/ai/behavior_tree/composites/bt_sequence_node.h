
#ifndef BT_SEQUENCE_NODE_H
#define BT_SEQUENCE_NODE_H

#include "bt_composite_node.h"


class BTSequenceNode : public BTCompositeNode
{

	OBJ_TYPE( BTSequenceNode, BTCompositeNode )
	OBJ_CATEGORY("AI")

	int current_node;

public:

	virtual int get_result();

	virtual void init_composite() { current_node = 0; }

};

#endif // BT_SEQUENCE_NODE_H
