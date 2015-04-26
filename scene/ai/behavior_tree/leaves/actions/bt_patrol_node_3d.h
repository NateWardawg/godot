#ifndef BT_PATROL_NODE_3D_H
#define BT_PATROL_NODE_3D_H

#include "bt_patrol_node.h"
#include "../../agents/bt_agent_3d.h"
#include "scene/3d/spatial.h"


class BTPatrolNode3D : public BTPatrolNode {

	OBJ_TYPE( BTPatrolNode3D, BTPatrolNode )
	OBJ_CATEGORY("AI")

protected:

	virtual const String _incorrect_node_type_warning() {
		return "Navigator must be a BTAgent3D node";
	}

	virtual float _get_distance_to_node(Node* p_patrol_node) {
		BTAgent3D* agent = (BTAgent3D*)navigator;
		Spatial* spatial_target = (Spatial*)p_patrol_node;

		return agent->get_translation().distance_squared_to(spatial_target->get_translation());
	}

public:

	virtual const Node* get_navigator() { return _get_navigator(); }
	virtual void set_navigator(Node* p_navigator) { _set_navigator<BTAgent3D>(p_navigator); }

	virtual void notify_target_changed(Node* new_target) {
		if ( navigator != NULL ) {
			BTAgent3D* navigator3D = dynamic_cast<BTAgent3D*>(navigator);
			navigator3D->notify_target_changed(new_target);
		}
	}

	virtual void add_target(Node* target) { _add_target<Spatial>(target); }

	BTPatrolNode3D();
};

#endif // BT_PATROL_NODE_3D_H
