
#include "bt_sequence_node.h"


void BTSequenceNode::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_current_leaf_index"),&BTSequenceNode::get_current_leaf_index);
}


int BTSequenceNode::check_state() {
	int state = nodes[current_node]->process_logic();

	if ( state == FAILED ) {
		current_node = 0;
		return FAILED;
	}

	if ( state == SUCCESS ) {
		current_node++;

		if ( current_node >= nodes.size() ) {
			return SUCCESS;
		}
	}

	return RUNNING;
}


void BTSequenceNode::init_composite() {
	current_node = 0;
}


int BTSequenceNode::get_current_leaf_index() {
	return current_node;
}
