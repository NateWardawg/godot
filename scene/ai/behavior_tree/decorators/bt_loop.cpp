#include "bt_loop.h"


void BTLoop::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_iterations"),&BTLoop::get_iterations);
	ClassDB::bind_method(D_METHOD("set_iterations"),&BTLoop::set_iterations);
	ClassDB::bind_method(D_METHOD("get_infinite"),&BTLoop::get_infinite);
	ClassDB::bind_method(D_METHOD("set_infinite"),&BTLoop::set_infinite);
	ClassDB::bind_method(D_METHOD("get_continue_on_fail"),&BTLoop::get_continue_on_fail);
	ClassDB::bind_method(D_METHOD("set_continue_on_fail"),&BTLoop::set_continue_on_fail);

	ADD_PROPERTY( PropertyInfo(Variant::INT,"iterations"), "set_iterations", "get_iterations" );
	ADD_PROPERTY( PropertyInfo(Variant::BOOL,"infinite"), "set_infinite", "get_infinite" );
	ADD_PROPERTY( PropertyInfo(Variant::BOOL,"continue_on_fail"), "set_continue_on_fail", "get_continue_on_fail" );
}


void BTLoop::execute() {

	if ( leaf_node == NULL ) {
		status = SUCCESS;
		return;
	}
	else {
		int node_state = leaf_node->process_logic();

		if ( node_state == SUCCESS || ( continue_on_fail && node_state == FAILURE ) ) {
			if ( current_iteration >= iterations && !infinite ) {
				status = SUCCESS;
				return;
			}

			current_iteration++;

			leaf_node->reset_node();
		}
		else if ( node_state == FAILURE ) {
			status = FAILURE;
			return;
		}
	}

	status = RUNNING;
}


void BTLoop::reset_node()
{
	current_iteration = 0;
	BehaviorTreeNode::reset_node();
}
