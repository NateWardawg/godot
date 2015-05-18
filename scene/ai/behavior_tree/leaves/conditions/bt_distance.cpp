
#include "bt_distance.h"


BTDistance::BTDistance() {
	distance = 1.0;
}


void BTDistance::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_navigator"),&BTDistance::get_navigator);
	ObjectTypeDB::bind_method(_MD("set_navigator"),&BTDistance::set_navigator);
	ObjectTypeDB::bind_method(_MD("get_distance"),&BTDistance::get_distance);
	ObjectTypeDB::bind_method(_MD("set_distance"),&BTDistance::set_distance);
	ObjectTypeDB::bind_method(_MD("get_target_group"),&BTDistance::get_target_group);
	ObjectTypeDB::bind_method(_MD("set_target_group"),&BTDistance::set_target_group);
	ObjectTypeDB::bind_method(_MD("add_target"),&BTDistance::add_target);
	ObjectTypeDB::bind_method(_MD("remove_target"),&BTDistance::remove_target);
	ObjectTypeDB::bind_method(_MD("find_target"),&BTDistance::find_target);

	ADD_PROPERTY( PropertyInfo(Variant::REAL,"distance"), _SCS("set_distance"), _SCS("get_distance") );
	ADD_PROPERTY( PropertyInfo(Variant::STRING,"target_group"), _SCS("set_target_group"), _SCS("get_target_group") );
}


void BTDistance::execute() {
	status = check_distances();
}


int BTDistance::check_distances() {
	real_t sqr_distance = distance * distance;
	int target_count;
	List<Node*> target_nodes;

	get_tree()->get_nodes_in_group(target_group, &target_nodes);

	for ( int i = 0; i < target_nodes.size(); i++ ) {
		add_target(target_nodes[i]);
	}

	target_count = targets.size();

	for ( int i = 0; i < target_count; i++ ) {
		real_t check_dist = navigator->get_translation().distance_squared_to(targets[i]->get_translation());

		if ( _check_distance(check_dist, sqr_distance) ) {
			return SUCCESS;
		}
	}

	return FAILED;
}


void BTDistance::add_target(Node* target) {
	int target_index = find_target(target);

	if ( target_index == -1 ) {
		Spatial* spatial = dynamic_cast<Spatial*>(target);

		if ( spatial != NULL ) {
			targets.insert(targets.size(), spatial);
		}
	}
}


void BTDistance::remove_target(Node* target) {
	int target_index = find_target(target);

	if ( target_index != -1 ) {
		targets.remove(target_index);
	}
}


int BTDistance::find_target(Node* target) {
	for ( int i = 0; i < targets.size(); i++ ) {
		if ( targets[i] == target ) {
			return i;
		}
	}

	return -1;
}
