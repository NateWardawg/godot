#include "bt_loop.h"


void BTLoop::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_iterations"),&BTLoop::get_iterations);
	ObjectTypeDB::bind_method(_MD("set_iterations"),&BTLoop::set_iterations);
	ObjectTypeDB::bind_method(_MD("get_infinite"),&BTLoop::get_infinite);
	ObjectTypeDB::bind_method(_MD("set_infinite"),&BTLoop::set_infinite);
	ObjectTypeDB::bind_method(_MD("get_continue_on_fail"),&BTLoop::get_continue_on_fail);
	ObjectTypeDB::bind_method(_MD("set_continue_on_fail"),&BTLoop::set_continue_on_fail);

	ADD_PROPERTY( PropertyInfo(Variant::INT,"iterations"), _SCS("set_iterations"), _SCS("get_iterations") );
	ADD_PROPERTY( PropertyInfo(Variant::BOOL,"infinite"), _SCS("set_infinite"), _SCS("get_infinite") );
	ADD_PROPERTY( PropertyInfo(Variant::BOOL,"continue_on_fail"), _SCS("set_continue_on_fail"), _SCS("get_continue_on_fail") );
}


void BTLoop::execute() {

	if ( leaf_node == NULL ) {
		status = SUCCESS;
		return;
	}
	else {
		int node_state = leaf_node->process_logic();

		if ( node_state == SUCCESS || ( continue_on_fail && node_state == FAILED ) ) {
			if ( current_iteration >= iterations && !infinite ) {
				status = SUCCESS;
				return;
			}

			print_line(String::num_int64(current_iteration));

			current_iteration++;

			leaf_node->reset_node();
		}
		else if ( node_state == FAILED ) {
			status = FAILED;
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
