#include "bt_node.h"

void BehaviorTreeNode::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_result"),&BehaviorTreeNode::get_result);
}
