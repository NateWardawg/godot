
#include "bt_sequence_node.h"


int BTSequenceNode::get_result() {
	int state = nodes[current_node]->process_logic();

	if ( state == FAILED ) {
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
