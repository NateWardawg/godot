#ifndef BT_PATROL_NODE_3D_H
#define BT_PATROL_NODE_3D_H

#include "bt_patrol_node.h"
#include "scene/3d/spatial.h"


class BTPatrolNode3D : public BTPatrolNode {

	OBJ_TYPE( BTPatrolNode3D, BTPatrolNode )
	OBJ_CATEGORY("AI")

protected:

	virtual const String _incorrect_node_type_warning() {
		return "Navigator must be a Spatial node";
	}

	virtual float _get_distance_to_node(Node* p_patrol_node) {
		Spatial* spatial_navigator = (Spatial*)navigator;
		Spatial* spatial_target = (Spatial*)p_patrol_node;

		return spatial_navigator->get_translation().distance_squared_to(spatial_target->get_translation());
	}

public:

	virtual const Node* get_navigator() { return _get_navigator(); }
	virtual void set_navigator(Node* p_navigator) { _set_navigator<Spatial>(p_navigator); }

	virtual void add_target(Node* target) { _add_target<Spatial>(target); }

	BTPatrolNode3D();
};

#endif // BT_PATROL_NODE_3D_H
