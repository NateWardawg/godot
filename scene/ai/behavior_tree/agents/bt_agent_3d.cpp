#include "bt_agent_3d.h"
#include "scene/main/node.h"
#include "../composites/bt_composite_node.h"


void BTAgent3D::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_READY: {
			update_behavior_tree();
			data.behavior_tree.get_root_node()->init_composite();
		} break;
		case NOTIFICATION_PROCESS: {
			if ( data.behavior_tree.get_root_node()->process_logic() == BehaviorTreeNode::SUCCESS ) {
				data.behavior_tree.get_root_node()->init_composite();
			}
			/*if ( data.behavior_tree.get_root_node()->process_logic() ) {
				data.behavior_tree.get_root_node()->init_composite();
			}*/
		} break;
	}
}


void BTAgent3D::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("update_behavior_tree"),&BTAgent3D::update_behavior_tree);

	BIND_VMETHOD( MethodInfo("_target_changed", PropertyInfo(Variant::OBJECT,"target",PROPERTY_HINT_RESOURCE_TYPE,"Spatial")) )
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
}


void BTAgent3D::notify_target_changed(Node* target) {
	if (get_script_instance()) {
		get_script_instance()->call("_target_changed", target);
	}
}
