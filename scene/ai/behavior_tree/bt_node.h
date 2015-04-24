#ifndef BT_NODE_H
#define BT_NODE_H

#include "../ai.h"


class BehaviorTreeNode : public AI {

	OBJ_TYPE( BehaviorTreeNode, AI )
	OBJ_CATEGORY("AI")

public:


	virtual void update_child_nodes() {}


	template<class T>
	Vector<BehaviorTreeNode*> get_child_nodes_by_type() {
		Vector<BehaviorTreeNode*> nodes;
		int child_count = get_child_count();
		int current_index = 0;

		for ( int i = 0; i < child_count; i++ ) {
			T node = dynamic_cast<T>(get_child(i));

			if ( node != NULL ) {
				nodes.insert(current_index++, node);
			}
		}

		return nodes;
	}
};

#endif // BT_NODE_H
