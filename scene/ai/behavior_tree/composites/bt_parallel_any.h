#ifndef BT_PARALLEL_ANY_H
#define BT_PARALLEL_ANY_H

#include "bt_composite.h"


class BTParallelAny : public BTComposite
{

	OBJ_TYPE( BTParallelAny, BTComposite )
    OBJ_CATEGORY("AI")

public:

	bool fail_on_child_failure;

    static void _bind_methods();

	virtual void execute();

	virtual void init_composite();

	BTParallelAny();

};

#endif // BT_PARALLEL_ANY_H
