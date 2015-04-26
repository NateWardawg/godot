#ifndef BT_AGENT_3D_H
#define BT_AGENT_3D_H

#include "scene/3d/spatial.h"
#include "../core/behavior_tree.h"


class BTAgent3D : public Spatial {

	OBJ_TYPE( BTAgent3D, Spatial )
	OBJ_CATEGORY("AI")

private:

	struct Data {
		BehaviorTree behavior_tree;
	} data;

public:

	static void _bind_methods();
	void _notification(int p_what);
	void set_behavior_tree(const BehaviorTree& p_behavior_tree);
	void update_behavior_tree();
	void notify_target_changed(Node* target);

};

#endif // BT_AGENT_3D_H
