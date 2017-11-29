
#include "bt_sequence.h"


void BTSequence::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_current_leaf_index"),&BTSequence::get_current_leaf_index);
}


void BTSequence::comp_execute() {
	int node_state = nodes[current_node]->process_logic();

	if ( node_state == get_end_status() ) {
		status = get_end_status();
		return;
	}

	if ( node_state == get_continue_status() ) {
		current_node++;

		if ( current_node >= nodes.size() ) {
			status = get_continue_status();
			return;
		} else {
			nodes[current_node]->reset_node();
		}
	}
}


int BTSequence::get_current_leaf_index() {
	return current_node;
}
