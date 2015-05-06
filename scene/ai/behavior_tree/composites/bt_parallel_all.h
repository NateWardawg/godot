#ifndef BT_PARALLEL_ALL_H
#define BT_PARALLEL_ALL_H

#include "bt_composite_node.h"


class BTParallelAll : public BTCompositeNode
{

    OBJ_TYPE( BTParallelAll, BTCompositeNode )
    OBJ_CATEGORY("AI")

public:

	bool fail_on_child_failure;

    static void _bind_methods();

	virtual void execute();

	virtual void init_composite();

	BTParallelAll();

};

#endif // BT_PARALLEL_ALL_H
