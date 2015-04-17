
#include "behavior_tree.h"

void BehaviorTree::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_ENTER_TREE: {
		} break;
		case NOTIFICATION_PROCESS: {
		}
	}
}


void BehaviorTree::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_value"),&BehaviorTree::get_value);
	ObjectTypeDB::bind_method(_MD("set_value"),&BehaviorTree::set_value);
}
