
#include "bt_parallel_any.h"


BTParallelAny::BTParallelAny() {
	fail_on_child_failure = true;
}


void BTParallelAny::_bind_methods() {
	//ObjectTypeDB::bind_method(_MD("get_current_leaf_index"),&BTSelectorNode::get_current_leaf_index);
}


void BTParallelAny::execute() {
	int failures = 0;

	for ( int i = 0; i < nodes.size(); i++ ) {
		int node_state = nodes[i]->get_result();

		if ( node_state == RUNNING ) {
			nodes[i]->process_logic();
		}
		else {
			if ( node_state == SUCCESS ) {
				state = SUCCESS;
				return;
			}
			else if ( node_state == FAILED ) {
				if ( fail_on_child_failure ) {
					state = FAILED;
					return;
				}
				else {
					failures++;
				}
			}
		}
	}

	state = (failures == nodes.size()) ? FAILED : RUNNING;
}


void BTParallelAny::init_composite() {
	state = RUNNING;
}
