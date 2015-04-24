
#include "behavior_tree.h"

void BehaviorTree::update_behavior_tree() {
	if ( root_node != NULL ) {
		Vector<BehaviorTreeNode*> nodes = root_node->get_child_nodes_by_type<BehaviorTreeNode*>();
		int child_count = nodes.size();

		print_line("Composite with " + String::num_int64(nodes.size()) + " children: " + root_node->get_name());

		for ( int i = 0; i < child_count; i++ ) {
			nodes[i]->update_child_nodes();
		}
	}
	else {
		print_line("root_node not assigned!");
	}
}
