
#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H

#include "scene/main/node.h"
#include "scene/ai/ai.h"
#include "../bt_node.h"


class BehaviorTreeNode;


class BehaviorTree {

private:

	Node *agent_node;
	BehaviorTreeNode *root_node;

	void set_behavior_tree_on_children(BehaviorTreeNode* p_base_node);

public:

	void set_agent_node(Node *p_agent_node);
	Node *get_agent_node() const;

	void set_root_node(BehaviorTreeNode *p_root_node);
	BehaviorTreeNode *get_root_node();

	void update_behavior_tree();

	BehaviorTree();

};

#endif // BEHAVIOR_TREE_H
