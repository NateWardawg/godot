#ifndef BT_PARALLEL_ALL_H
#define BT_PARALLEL_ALL_H

#include "bt_composite.h"


class BTParallelAll : public BTComposite {

	OBJ_TYPE( BTParallelAll, BTComposite )
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

	BTParallelAll();

};

#endif // BT_PARALLEL_ALL_H
