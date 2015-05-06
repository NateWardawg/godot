
#include "bt_decorator_node.h"

void BTDecoratorNode::_notification(int p_what) {}


void BTDecoratorNode::update_child_nodes() {
	Vector<BehaviorTreeNode*> nodes = get_child_nodes_by_type<BehaviorTreeNode*>();
	int node_count = nodes.size();

	if ( node_count == 0 ) {
		print_line("Warning: a Decorator node needs one (and only one) Leaf node. '" + get_name() + "' will automatically return SUCCESS");
		leaf_node = NULL;
	}
	else {
		leaf_node = (BTLeafNode*)nodes[0];

		if ( node_count > 1 ) {
			print_line("Warning: a Decorator node only accepts one sub node, only the first one will be used: '" + get_name() + "' will only use '" + leaf_node->get_name() + "'");
		}
	}

	for ( int i = 0; i < node_count; i++ ) {
		nodes[i]->update_child_nodes();
	}
}


void BTDecoratorNode::reset_node() {
	if ( leaf_node != NULL ) {
		leaf_node->reset_node();
	}

	BehaviorTreeNode::reset_node();
}
