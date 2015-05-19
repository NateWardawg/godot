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

	virtual void comp_execute();

	virtual void init_composite();

	bool get_fail_on_child_failure() { return fail_on_child_failure; }
	void set_fail_on_child_failure(bool p_fail_on_child_failure) { fail_on_child_failure = p_fail_on_child_failure; }

	BTParallelAny();

};

#endif // BT_PARALLEL_ANY_H
