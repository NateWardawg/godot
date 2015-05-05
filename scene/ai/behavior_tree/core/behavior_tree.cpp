
#include "behavior_tree.h"


BehaviorTree::BehaviorTree()
{
	root_node = NULL;
}


void BehaviorTree::update_behavior_tree() {
	if ( root_node != NULL ) {
		root_node->update_child_nodes();
	}
	else {
		print_line("root_node not assigned!");
	}
}
