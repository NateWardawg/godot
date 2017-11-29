#ifndef BT_PARALLEL_H
#define BT_PARALLEL_H

#include "bt_composite.h"


class BTParallel : public BTComposite {

	GDCLASS( BTParallel, BTComposite )
	OBJ_CATEGORY("AI")

public:

	enum ExitCondition {

		FIRST_CHILD,
		ANY_CHILD,
		ALL_CHILDREN
	};


	ExitCondition success_condition;
	ExitCondition failure_condition;

	static void _bind_methods();

	virtual void comp_execute();

	virtual void init_composite();

	ExitCondition get_success_condition() const;
	void set_success_condition(ExitCondition p_success_condition);

	ExitCondition get_failure_condition() const;
	void set_failure_condition(ExitCondition p_failure_condition);

	BTParallel();

};

#endif // BT_PARALLEL_H
