
#include "behavior_tree.h"


BehaviorTree::BehaviorTree() {
	root_node = NULL;
}


void BehaviorTree::set_agent_node(Node *p_agent_node) {
	agent_node = p_agent_node;
}


Node* BehaviorTree::get_agent_node() const {
	return agent_node;
}


void BehaviorTree::set_root_node(BehaviorTreeNode *p_root_node) {
	root_node = p_root_node;
}


BehaviorTreeNode* BehaviorTree::get_root_node() {
	return root_node;
}



void BehaviorTree::update_behavior_tree() {
	if ( root_node != NULL ) {
		root_node->update_child_nodes();
		set_behavior_tree_on_children(root_node);
	} else {
		print_line("root_node not assigned!");
	}
}


void BehaviorTree::set_behavior_tree_on_children(BehaviorTreeNode* p_base_node) {
	Vector<BehaviorTreeNode*> nodes = p_base_node->get_child_nodes_by_type<BehaviorTreeNode*>();

	p_base_node->set_behavior_tree(this);

	for ( int i = 0; i < nodes.size(); i++ ) {
		nodes[i]->set_behavior_tree(this);
		set_behavior_tree_on_children(nodes[i]);
	}
}
