#ifndef BT_PATROL_NODE_3D_H
#define BT_PATROL_NODE_3D_H

#include "bt_patrol.h"
#include "../../agents/bt_agent_3d.h"
#include "scene/3d/spatial.h"


class BTPatrol3D : public BTPatrol {

	GDCLASS( BTPatrol3D, BTPatrol )
	OBJ_CATEGORY("AI")

protected:

	virtual const String _incorrect_node_type_warning() { return "Navigator must be a BTAgent3D node"; }
	virtual float _get_distance_to_node(Node* p_patrol_node);
	virtual bool is_correct_agent(Node *node);

public:

	virtual Node* get_navigator() const { return _get_navigator(); }
	virtual void set_navigator(Node* p_navigator) { _set_navigator<BTAgent3D>(p_navigator); }
	virtual bool is_node_valid_patrol_point(Node* node);
	virtual void notify_target_changed(Node* new_target);

	virtual void add_target(Node* target) { _add_target<Spatial>(target); }
};

#endif // BT_PATROL_NODE_3D_H
