
#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H

#include "scene/main/node.h"
#include "scene/ai/ai.h"
#include "../composites/bt_composite_node.h"


class BehaviorTree {

private:
	BTCompositeNode *root_node;

public:
	void set_root_node(BTCompositeNode *p_root_node) { root_node = p_root_node; }
	BTCompositeNode *get_root_node() { return root_node; }
	void update_behavior_tree();
};

#endif // BEHAVIOR_TREE_H
