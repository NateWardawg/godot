
#include "bt_parallel_all.h"


BTParallelAll::BTParallelAll() {
	fail_on_child_failure = true;
}


void BTParallelAll::_bind_methods() {
	//ObjectTypeDB::bind_method(_MD("get_current_leaf_index"),&BTSelectorNode::get_current_leaf_index);
}


void BTParallelAll::execute() {
	int successes = 0;

	for ( int i = 0; i < nodes.size(); i++ ) {
		int node_state = nodes[i]->get_result();

		if ( node_state == RUNNING ) {
			nodes[i]->process_logic();
		}
		else {
			if ( node_state == SUCCESS ) {
				successes++;
			}
			else if ( node_state == FAILED ) {
				if ( fail_on_child_failure ) {
					state = FAILED;
					return;
				}
				else {
					successes++;
				}
			}
		}
	}

	state = (successes == nodes.size()) ? SUCCESS : RUNNING;
}


void BTParallelAll::init_composite() {
	state = RUNNING;
}
