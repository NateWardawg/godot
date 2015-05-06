
#include "bt_sequence_node.h"


void BTSequenceNode::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_current_leaf_index"),&BTSequenceNode::get_current_leaf_index);
}


void BTSequenceNode::execute() {
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


void BTSequenceNode::init_composite() {
	current_node = 0;
}


int BTSequenceNode::get_current_leaf_index() {
	return current_node;
}
