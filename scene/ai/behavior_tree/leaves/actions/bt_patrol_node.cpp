
#include "bt_patrol_node.h"


BTPatrolNode::BTPatrolNode() {
	distance = 1.0;
}


void BTPatrolNode::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_navigator"),&BTPatrolNode::get_navigator);
	ObjectTypeDB::bind_method(_MD("set_navigator"),&BTPatrolNode::set_navigator);
	ObjectTypeDB::bind_method(_MD("get_target_group"),&BTPatrolNode::get_target_group);
	ObjectTypeDB::bind_method(_MD("set_target_group"),&BTPatrolNode::set_target_group);
	ObjectTypeDB::bind_method(_MD("get_distance"),&BTPatrolNode::get_distance);
	ObjectTypeDB::bind_method(_MD("set_distance"),&BTPatrolNode::set_distance);
	ObjectTypeDB::bind_method(_MD("add_target"),&BTPatrolNode::add_target);
	ObjectTypeDB::bind_method(_MD("remove_target"),&BTPatrolNode::remove_target);
	ObjectTypeDB::bind_method(_MD("find_target"),&BTPatrolNode::find_target);

	ADD_PROPERTY( PropertyInfo(Variant::STRING,"target_patrol_group"), _SCS("set_target_group"), _SCS("get_target_group") );
	ADD_PROPERTY( PropertyInfo(Variant::REAL,"distance"), _SCS("set_distance"), _SCS("get_distance") );
}


void BTPatrolNode::_init_patrol_points() {
	if ( get_tree() != NULL ) {
		List<Node*> target_nodes;

		get_tree()->get_nodes_in_group(target_patrol_group, &target_nodes);

		for ( int i = 0; i < target_nodes.size(); i++ ) {
			add_target(target_nodes[i]);
		}
	}
}


void BTPatrolNode::_correct_patrol_index() {
	current_patrol_index = current_patrol_index % patrol_targets.size();
}


bool BTPatrolNode::_check_points() {
	real_t sqr_distance = distance * distance;

	if ( patrol_targets.size() > 0 ) {
		real_t check_dist = _get_distance_to_node(patrol_targets[current_patrol_index]);

		if ( check_dist < sqr_distance ) {
			current_patrol_index++;
			_correct_patrol_index();
			print_line("Patrol: True");
			return true;
		}
	}

	print_line("Patrol: False");
	return false;
}


void BTPatrolNode::remove_target(Node* target) {
	int target_index = find_target(target);

	if ( target_index != -1 ) {
		patrol_targets.remove(target_index);
	}
}


int BTPatrolNode::find_target(Node* target) {
	for ( int i = 0; i < patrol_targets.size(); i++ ) {
		if ( patrol_targets[i] == target ) {
			return i;
		}
	}

	return -1;
}
