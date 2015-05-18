#ifndef BT_PARALLEL_ALL_H
#define BT_PARALLEL_ALL_H

#include "bt_composite.h"


class BTParallelAll : public BTComposite
{

	OBJ_TYPE( BTParallelAll, BTComposite )
    OBJ_CATEGORY("AI")

public:

	bool fail_on_child_failure;
	bool use_master_node;

	static void _bind_methods();

	virtual void execute();

	virtual void init_composite();

	bool get_fail_on_child_failure() { return fail_on_child_failure; }
	void set_fail_on_child_failure(bool p_fail_on_child_failure) { fail_on_child_failure = p_fail_on_child_failure; }

	bool get_use_master_node() { return use_master_node; }
	void set_use_master_node(bool p_use_master_node) { use_master_node = p_use_master_node; }

	BTParallelAll();

};

#endif // BT_PARALLEL_ALL_H
