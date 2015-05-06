#include "bt_selector.h"


void BTSelector::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_current_leaf_index"),&BTSelector::get_current_leaf_index);
}


void BTSelector::execute() {
	int node_state = nodes[current_node]->process_logic();

	if ( node_state == SUCCESS ) {
		current_node = 0;
		state = SUCCESS;
		return;
	}

	if ( node_state == FAILED ) {
		current_node++;

		if ( current_node >= nodes.size() ) {
			state = FAILED;
			return;
		}
	}

	state = RUNNING;
}


void BTSelector::init_composite() {
	current_node = 0;
}


int BTSelector::get_current_leaf_index() {
	return current_node;
}
