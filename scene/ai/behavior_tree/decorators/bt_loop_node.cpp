#include "bt_loop_node.h"


void BTLoopNode::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_iterations"),&BTLoopNode::get_iterations);
	ObjectTypeDB::bind_method(_MD("set_iterations"),&BTLoopNode::set_iterations);
	ObjectTypeDB::bind_method(_MD("get_infinite"),&BTLoopNode::get_infinite);
	ObjectTypeDB::bind_method(_MD("set_infinite"),&BTLoopNode::set_infinite);
	ObjectTypeDB::bind_method(_MD("get_continue_on_fail"),&BTLoopNode::get_continue_on_fail);
	ObjectTypeDB::bind_method(_MD("set_continue_on_fail"),&BTLoopNode::set_continue_on_fail);

	ADD_PROPERTY( PropertyInfo(Variant::INT,"iterations"), _SCS("set_iterations"), _SCS("get_iterations") );
	ADD_PROPERTY( PropertyInfo(Variant::BOOL,"infinite"), _SCS("set_infinite"), _SCS("get_infinite") );
	ADD_PROPERTY( PropertyInfo(Variant::BOOL,"continue_on_fail"), _SCS("set_continue_on_fail"), _SCS("get_continue_on_fail") );
}


void BTLoopNode::execute() {

	if ( leaf_node == NULL ) {
		state = SUCCESS;
		return;
	}
	else {
		int node_state = leaf_node->process_logic();

		if ( node_state == SUCCESS || ( continue_on_fail && node_state == FAILED ) ) {
			if ( current_iteration >= iterations && !infinite ) {
				state = SUCCESS;
				return;
			}

			print_line(String::num_int64(current_iteration));

			current_iteration++;

			leaf_node->reset_node();
		}
		else if ( node_state == FAILED ) {
			state = FAILED;
			return;
		}
	}

	state = RUNNING;
}


void BTLoopNode::reset_node()
{
	current_iteration = 0;
	BehaviorTreeNode::reset_node();
}
