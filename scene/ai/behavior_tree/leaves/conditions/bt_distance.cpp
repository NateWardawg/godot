
#include "bt_distance.h"


BTDistance::BTDistance() {
	distance = 1.0;
}


void BTDistance::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_distance"),&BTDistance::get_distance);
	ClassDB::bind_method(D_METHOD("set_distance"),&BTDistance::set_distance);
	ClassDB::bind_method(D_METHOD("get_target_group"),&BTDistance::get_target_group);
	ClassDB::bind_method(D_METHOD("set_target_group"),&BTDistance::set_target_group);
	ClassDB::bind_method(D_METHOD("add_target"),&BTDistance::add_target);
	ClassDB::bind_method(D_METHOD("remove_target"),&BTDistance::remove_target);
	ClassDB::bind_method(D_METHOD("find_target"),&BTDistance::find_target);

	ADD_PROPERTY( PropertyInfo(Variant::REAL,"distance"), "set_distance", "get_distance" );
	ADD_PROPERTY( PropertyInfo(Variant::STRING,"target_group"), "set_target_group", "get_target_group" );
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
		const BTAgent3D* agent = (const BTAgent3D*)(behavior_tree->get_agent_node());

		if ( agent == NULL ) {
			print_line("is NULL");
		} else {
			print_line("not NULL");
		}

		real_t check_dist = agent->get_translation().distance_squared_to(targets[i]->get_translation());

		if ( _check_distance(check_dist, sqr_distance) ) {
			return SUCCESS;
		}
	}

	return RUNNING;
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