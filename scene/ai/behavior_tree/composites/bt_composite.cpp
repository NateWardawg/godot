
#include "../bt_node.h"
#include "bt_composite.h"



BTComposite::BTComposite() {
	init_composite();
}


void BTComposite::_notification(int p_what) {}


void BTComposite::update_child_nodes() {
	int node_count;

	nodes = get_child_nodes_by_type<BehaviorTreeNode*>();
	node_count = nodes.size();

	if ( node_count == 0 ) {
		print_line("Warning: a Composite node needs at least one Composite, Decorator, or Leaf node. '" + get_name() + "' will automatically return true");
	}

	for ( int i = 0; i < node_count; i++ ) {
		nodes[i]->update_child_nodes();
	}
}


void BTComposite::reset_node()
{
	init_composite();

	for ( int i = 0; i < nodes.size(); i++ ) {
		nodes[i]->reset_node();
	}
}
