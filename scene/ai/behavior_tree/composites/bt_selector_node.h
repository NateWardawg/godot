#ifndef BTSELECTORNODE_H
#define BTSELECTORNODE_H

#include "bt_composite_node.h"


class BTSelectorNode : public BTCompositeNode
{

	OBJ_TYPE( BTSelectorNode, BTCompositeNode )
	OBJ_CATEGORY("AI")

	int current_node;

public:

	static void _bind_methods();

	virtual int check_state();

	virtual void init_composite();

	int get_current_leaf_index();

};

#endif // BTSELECTORNODE_H
