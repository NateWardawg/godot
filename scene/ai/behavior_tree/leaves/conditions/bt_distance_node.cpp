
#include "bt_distance_node.h"


BTDistanceNode::BTDistanceNode() {
	distance = 1.0;
}


void BTDistanceNode::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_distance"),&BTDistanceNode::get_distance);
	ObjectTypeDB::bind_method(_MD("set_distance"),&BTDistanceNode::set_distance);
	ObjectTypeDB::bind_method(_MD("add_target"),&BTDistanceNode::_add_target);
	ObjectTypeDB::bind_method(_MD("remove_target"),&BTDistanceNode::_remove_target);
	ObjectTypeDB::bind_method(_MD("find_target"),&BTDistanceNode::_find_target);

	ADD_PROPERTY( PropertyInfo(Variant::REAL,"distance"), _SCS("set_distance"), _SCS("get_distance") );
}


bool BTDistanceNode::check_distances() {
	int target_count = targets.size();
	real_t sqr_distance = distance * distance;
	Vector3 zero;

	for ( int i = 0; i < target_count; i++ ) {
		real_t check_dist = zero.distance_squared_to(targets[i]->get_translation());

		if ( check_distance(check_dist, sqr_distance) ) {
			return true;
		}
	}

	return false;
}


void BTDistanceNode::_add_target(Node* target) {
	int target_index = _find_target(target);

	if ( target_index == -1 ) {
		Spatial* spatial = dynamic_cast<Spatial*>(target);

		if ( spatial != NULL ) {
			targets.insert(targets.size(), spatial);
			print_line(String::num_int64(targets.size()));
		}
	}
}


void BTDistanceNode::_remove_target(Node* target) {
	int target_index = _find_target(target);

	if ( target_index != -1 ) {
		targets.remove(target_index);
	}
}


int BTDistanceNode::_find_target(Node* target) {
	for ( int i = 0; i < targets.size(); i++ ) {
		if ( targets[i] == target ) {
			return i;
		}
	}

	return -1;
}
