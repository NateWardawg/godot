#ifndef BT_NODE_H
#define BT_NODE_H

#include "../ai.h"
#include "core/behavior_tree.h"


class BehaviorTree;


class BehaviorTreeNode : public AI {

	GDCLASS( BehaviorTreeNode, AI )
	OBJ_CATEGORY("AI")

	void _execute_calls(int result);

protected:

	BehaviorTree *behavior_tree;
	int status;
	virtual void execute() = 0;

	static void _bind_methods();

public:

	enum BehaviorStatus {
		FAILURE = -1,
		RUNNING = 0,
		SUCCESS = 1
	};

	int process_logic();

	void set_behavior_tree(BehaviorTree *p_behavior_tree) { behavior_tree = p_behavior_tree; }
	BehaviorTree* get_behavior_tree() { return behavior_tree; }

	Node* get_agent() const;

	virtual void update_child_nodes() {}
	virtual void reset_node();

	int get_status() { return status; }
	void set_status(int p_status);


	BehaviorTreeNode();

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
