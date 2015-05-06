
#include "bt_sequence.h"


void BTSequence::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_current_leaf_index"),&BTSequence::get_current_leaf_index);
}


void BTSequence::execute() {
	int node_state = nodes[current_node]->process_logic();

	if ( node_state == FAILED ) {
		current_node = 0;
		state = FAILED;
		return;
	}

	if ( node_state == SUCCESS ) {
		current_node++;

		if ( current_node >= nodes.size() ) {
			state = SUCCESS;
			return;
		}
	}

	state = RUNNING;
}


void BTSequence::init_composite() {
	current_node = 0;
}


int BTSequence::get_current_leaf_index() {
	return current_node;
}
