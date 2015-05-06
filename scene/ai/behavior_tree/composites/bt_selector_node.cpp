#include "bt_selector_node.h"


void BTSelectorNode::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_current_leaf_index"),&BTSelectorNode::get_current_leaf_index);
}


void BTSelectorNode::execute() {
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


void BTSelectorNode::init_composite() {
	current_node = 0;
}


int BTSelectorNode::get_current_leaf_index() {
	return current_node;
}
