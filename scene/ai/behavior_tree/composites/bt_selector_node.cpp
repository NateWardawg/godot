#include "bt_selector_node.h"


void BTSelectorNode::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_current_leaf_index"),&BTSelectorNode::get_current_leaf_index);
}


int BTSelectorNode::check_state() {
	int state = nodes[current_node]->process_logic();

	if ( state == SUCCESS ) {
		current_node = 0;
		return SUCCESS;
	}

	if ( state == FAILED ) {
		current_node++;

		if ( current_node >= nodes.size() ) {
			return FAILED;
		}
	}

	return RUNNING;
}


void BTSelectorNode::init_composite() {
	current_node = 0;
}


int BTSelectorNode::get_current_leaf_index() {
	return current_node;
}
