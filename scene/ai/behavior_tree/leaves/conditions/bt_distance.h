
#ifndef BT_DISTANCE_NODE_H
#define BT_DISTANCE_NODE_H

#include "scene/3d/spatial.h"
#include "../bt_condition.h"
#include "../../agents/bt_agent_3d.h"


class BTDistance : public BTCondition {

	GDCLASS( BTDistance, BTCondition )
	OBJ_CATEGORY("AI")

	int check_distances();

protected:

	real_t distance;
	String target_group;

	virtual bool _check_distance(real_t check_distance, real_t target_distance) = 0;

public:

	static void _bind_methods();

	virtual void execute();

	real_t get_distance() { return distance; }
	void set_distance(real_t p_distance) { distance = p_distance; }

	String get_target_group() const { return target_group; }
	void set_target_group(String p_group) { target_group = p_group; }

	void add_target(Node* target);
	void remove_target(Node* target);
	int find_target(Node* target);

	Vector<Spatial*> targets;

	BTDistance();

};

#endif // BT_DISTANCE_NODE_H
