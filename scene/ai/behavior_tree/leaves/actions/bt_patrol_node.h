
#ifndef BT_PATROL_NODE_H
#define BT_PATROL_NODE_H

#include "scene/3d/spatial.h"
#include "../bt_action_node.h"


class BTPatrolNode : public BTActionNode
{

	OBJ_TYPE( BTPatrolNode, BTActionNode )
	OBJ_CATEGORY("AI")

	int current_patrol_index;

	void _init_patrol_points();
	void _correct_patrol_index();
	bool _check_points();

protected:

	Spatial *navigator;
	String target_patrol_group;
	real_t distance;

	//template<class T>
	const Node* _get_navigator() { return navigator; }

	//template<class T>
	void _set_navigator(Node* p_navigator) {
		Spatial* potential_navigator = dynamic_cast<Spatial*>(p_navigator);

		if ( potential_navigator != NULL ) {
			navigator = potential_navigator;
		}
		else {
			print_line("Navigator must be a Spatial node");
		}
	}

public:

	static void _bind_methods();

	virtual void update_child_nodes() { _init_patrol_points(); }

	bool get_result() { return _check_points(); }

//	const Node* get_navigator() { return _get_navigator(); }
//	void set_navigator(Node* p_navigator) {
//		_set_navigator(p_navigator);
//	}
	const Node* get_navigator() { return navigator; }

	//template<class T>
	void set_navigator(Node* p_navigator) {
		Spatial* potential_navigator = dynamic_cast<Spatial*>(p_navigator);

		if ( potential_navigator != NULL ) {
			navigator = potential_navigator;
		}
		else {
			print_line("Navigator must be a Spatial node");
		}
	}

	String get_target_group() const { return target_patrol_group; }
	void set_target_group(const String& p_group) { target_patrol_group = p_group; }

	real_t get_distance() { return distance; }
	void set_distance(real_t p_distance) { distance = p_distance; }

	void add_target(Node* target);
	void remove_target(Node* target);
	int find_target(Node* target);

	Vector<Spatial*> patrol_targets;

	BTPatrolNode();

};

#endif // BT_PATROL_NODE_H
