
#include "ai_behavior_tree.h"

void AIBehaviorTree::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_ENTER_TREE: {
		} break;
		case NOTIFICATION_PROCESS: {
		}
	}
}


void AIBehaviorTree::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_value"),&AIBehaviorTree::get_value);
	ObjectTypeDB::bind_method(_MD("set_value"),&AIBehaviorTree::set_value);
}
