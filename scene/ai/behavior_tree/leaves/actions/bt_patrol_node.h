
#ifndef BT_PATROL_NODE_H
#define BT_PATROL_NODE_H

#include "../bt_action_node.h"
#include "scene/3d/spatial.h"


class BTPatrolNode : public BTActionNode
{

	OBJ_TYPE( BTPatrolNode, BTActionNode )
	OBJ_CATEGORY("AI")

	int current_patrol_index;

	void _init_patrol_points();
	void _correct_patrol_index();
	bool _check_points();

protected:

	Node *navigator;
	String target_patrol_group;
	real_t distance;

	virtual const String _incorrect_node_type_warning() = 0;

	const Node* _get_navigator() { return navigator; }

	template<class T>
	void _set_navigator(Node* p_navigator) {
		T* potential_navigator = dynamic_cast<T*>(p_navigator);

		if ( potential_navigator != NULL ) {
			navigator = potential_navigator;
		}
		else {
			print_line(_incorrect_node_type_warning());
		}
	}

	template<class T>
	void _add_target(Node* target) {
		int target_index = find_target(target);

		if ( target_index == -1 ) {
			T* potential_target = dynamic_cast<T*>(target);

			if ( potential_target != NULL ) {
				patrol_targets.insert(patrol_targets.size(), potential_target);
			}
		}
	}

	virtual float _get_distance_to_node(Node* p_patrol_node) = 0;

public:

	static void _bind_methods();

	virtual void update_child_nodes() { _init_patrol_points(); }

	bool get_result() { return _check_points(); }

	virtual const Node* get_navigator() = 0;
	virtual void set_navigator(Node* p_navigator) = 0;

	String get_target_group() const { return target_patrol_group; }
	void set_target_group(const String& p_group) { target_patrol_group = p_group; }

	real_t get_distance() { return distance; }
	void set_distance(real_t p_distance) { distance = p_distance; }

	virtual void add_target(Node* target) { _add_target<Node>(target); }
	void remove_target(Node* target);
	int find_target(Node* target);

	Vector<Node*> patrol_targets;

	BTPatrolNode();

};

#endif // BT_PATROL_NODE_H
