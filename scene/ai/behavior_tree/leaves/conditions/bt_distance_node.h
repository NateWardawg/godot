
#ifndef BT_DISTANCE_NODE_H
#define BT_DISTANCE_NODE_H

#include "scene/3d/spatial.h"
#include "../bt_condition_node.h"


class BTDistanceNode : public BTConditionNode
{

	OBJ_TYPE( BTDistanceNode, BTConditionNode )
	OBJ_CATEGORY("AI")

	bool check_distances();

protected:

	real_t distance;
	String target_group;

	virtual bool _check_distance(real_t check_distance, real_t target_distance) = 0;

public:

	static void _bind_methods();

	virtual bool get_result() { return check_distances(); }

	real_t get_distance() { return distance; }
	void set_distance(real_t p_distance) { distance = p_distance; }

	const String get_target_group() { return target_group; }
	void set_target_group(String p_group) { target_group = p_group; }

	void add_target(Node* target);
	void remove_target(Node* target);
	int find_target(Node* target);

	Vector<Spatial*> targets;

	BTDistanceNode();

};

#endif // BT_DISTANCE_NODE_H
