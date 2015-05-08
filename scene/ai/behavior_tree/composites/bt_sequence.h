
#ifndef BT_SEQUENCE_NODE_H
#define BT_SEQUENCE_NODE_H

#include "bt_composite.h"


class BTSequence : public BTComposite
{

	OBJ_TYPE( BTSequence, BTComposite )
	OBJ_CATEGORY("AI")

public:

	static void _bind_methods();

	virtual void execute();

	int get_current_leaf_index();

};

#endif // BT_SEQUENCE_NODE_H
