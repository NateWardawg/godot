
#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H

#include "scene/main/node.h"
#include "scene/ai/ai.h"
#include "../bt_node.h"


class BehaviorTree {

private:
	BehaviorTreeNode *root_node;

public:
	void set_root_node(BehaviorTreeNode *p_root_node) { root_node = p_root_node; }
	BehaviorTreeNode *get_root_node() { return root_node; }
	void update_behavior_tree();

	BehaviorTree();

};

#endif // BEHAVIOR_TREE_H
