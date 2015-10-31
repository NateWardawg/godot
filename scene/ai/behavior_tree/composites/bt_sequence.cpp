
#include "bt_sequence.h"


void BTSequence::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_current_leaf_index"),&BTSequence::get_current_leaf_index);
}


void BTSequence::comp_execute() {
	int node_state = nodes[current_node]->process_logic();

	if ( node_state == FAILURE ) {
		status = FAILURE;
		return;
	}

	if ( node_state == SUCCESS ) {
		current_node++;

		if ( current_node >= nodes.size() ) {
			status = SUCCESS;
			return;
		}
		else {
			nodes[current_node]->reset_node();
		}
	}

	status = RUNNING;
}


int BTSequence::get_current_leaf_index() {
	return current_node;
}
