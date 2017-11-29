#ifndef BTLOOPNODE_H
#define BTLOOPNODE_H

#include "bt_decorator.h"


class BTLoop : public BTDecorator
{

	GDCLASS( BTLoop, BTDecorator )
	OBJ_CATEGORY("AI")

protected:

	int current_iteration;
	int iterations;
	bool infinite;
	bool continue_on_fail;

	virtual void execute();

public:

	static void _bind_methods();

	virtual void reset_node();

	int get_iterations() { return iterations; }
	void set_iterations(int p_iterations) { iterations = p_iterations; }

	bool get_infinite() { return infinite; }
	void set_infinite(bool p_infinite) { infinite = p_infinite; }

	bool get_continue_on_fail() { return continue_on_fail; }
	void set_continue_on_fail(bool p_continue_on_fail) { continue_on_fail = p_continue_on_fail; }

};

#endif // BTLOOPNODE_H
