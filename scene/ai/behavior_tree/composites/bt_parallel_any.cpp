
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
		int node_state = nodes[i]->get_status();

		if ( node_state == RUNNING ) {
			nodes[i]->process_logic();
		}
		else {
			if ( node_state == SUCCESS ) {
				status = SUCCESS;
				return;
			}
			else if ( node_state == FAILED ) {
				if ( fail_on_child_failure ) {
					status = FAILED;
					return;
				}
				else {
					failures++;
				}
			}
		}
	}

	status = (failures == nodes.size()) ? FAILED : RUNNING;
}


void BTParallelAny::init_composite() {
	status = RUNNING;
}
