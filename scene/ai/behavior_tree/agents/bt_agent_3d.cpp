#include "bt_agent_3d.h"
#include "scene/main/node.h"


void BTAgent3D::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_READY: {
			update_behavior_tree();

			if ( data.behavior_tree.get_root_node() != NULL ) {
				data.behavior_tree.get_root_node()->reset_node();
			}
		} break;
		case NOTIFICATION_PROCESS: {
			if ( data.behavior_tree.get_root_node()->process_logic() != BehaviorTreeNode::RUNNING ) {
				data.behavior_tree.get_root_node()->reset_node();
			}
		} break;
	}
}


void BTAgent3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update_behavior_tree"),&BTAgent3D::update_behavior_tree);
	ClassDB::bind_method(D_METHOD("set_target"),&BTAgent3D::set_target);
	ClassDB::bind_method(D_METHOD("get_target"),&BTAgent3D::get_target);

	BIND_VMETHOD( MethodInfo("_target_changed", PropertyInfo(Variant::OBJECT,"target",PROPERTY_HINT_RESOURCE_TYPE,"Spatial")) )
}


void BTAgent3D::set_behavior_tree(const BehaviorTree& p_behavior_tree) {
	data.behavior_tree = p_behavior_tree;
}


void BTAgent3D::update_behavior_tree() {
	data.behavior_tree.set_agent_node(this);

	for ( int i = 0; i < get_child_count(); i++ ) {
		BehaviorTreeNode* node = dynamic_cast<BehaviorTreeNode*>(get_child(i));

		if ( node != NULL ) {
			data.behavior_tree.set_root_node(node);
			data.behavior_tree.update_behavior_tree();
			break;
		}
	}
}


void BTAgent3D::set_target(Node* p_target) {
	Spatial* new_target = dynamic_cast<Spatial*>(p_target);

	if ( new_target != NULL && target != p_target ) {
		target = new_target;
		_notify_target_changed();
	}
}


void BTAgent3D::_notify_target_changed() {
	if (get_script_instance()) {
		get_script_instance()->call("_target_changed", target);
	}
}
