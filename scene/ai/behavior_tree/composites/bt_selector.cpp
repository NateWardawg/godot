
#include "bt_selector.h"


void BTSelector::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_current_leaf_index"),&BTSelector::get_current_leaf_index);
}


void BTSelector::comp_execute() {
	int node_state = nodes[current_node]->process_logic();

	if ( node_state == SUCCESS ) {
		status = SUCCESS;
		return;
	}

	if ( node_state == FAILURE ) {
		current_node++;

		if ( current_node >= nodes.size() ) {
			status = FAILURE;
			return;
		} else {
			nodes[current_node]->reset_node();
		}
	}

	status = RUNNING;
}



int BTSelector::get_current_leaf_index() {
	return current_node;
}
