#include "bt_agent_3d.h"
#include "scene/main/node.h"
#include "../composites/bt_composite_node.h"


void BTAgent3D::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_READY: {
			update_behavior_tree();
		} break;
		case NOTIFICATION_PROCESS: {
			data.behavior_tree.get_root_node()->get_result();
		} break;
	}
}


void BTAgent3D::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("update_behavior_tree"),&BTAgent3D::update_behavior_tree);

	BIND_VMETHOD( MethodInfo("_test_func") );
}


void BTAgent3D::set_behavior_tree(const BehaviorTree& p_behavior_tree) {
	data.behavior_tree = p_behavior_tree;
}


void BTAgent3D::update_behavior_tree() {
	for ( int i = 0; i < get_child_count(); i++ ) {
		BTCompositeNode* node = dynamic_cast<BTCompositeNode*>(get_child(i));

		if ( node != NULL ) {
			data.behavior_tree.set_root_node(node);
			data.behavior_tree.update_behavior_tree();
			break;
		}
	}

	if (get_script_instance()) {
		get_script_instance()->call_multilevel_reversed("_test_func",NULL,0);
	}
}
