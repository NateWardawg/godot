
#include "bt_patrol.h"


BTPatrol::BTPatrol() {
	distance = 1.0;
	current_target = NULL;
	navigator = NULL;
}


void BTPatrol::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_navigator"),&BTPatrol::get_navigator);
	ObjectTypeDB::bind_method(_MD("set_navigator"),&BTPatrol::set_navigator);
	ObjectTypeDB::bind_method(_MD("get_target_group"),&BTPatrol::get_target_group);
	ObjectTypeDB::bind_method(_MD("set_target_group"),&BTPatrol::set_target_group);
	ObjectTypeDB::bind_method(_MD("get_distance"),&BTPatrol::get_distance);
	ObjectTypeDB::bind_method(_MD("set_distance"),&BTPatrol::set_distance);
	ObjectTypeDB::bind_method(_MD("add_target"),&BTPatrol::add_target);
	ObjectTypeDB::bind_method(_MD("remove_target"),&BTPatrol::remove_target);
	ObjectTypeDB::bind_method(_MD("find_target"),&BTPatrol::find_target);
	ObjectTypeDB::bind_method(_MD("get_target_count"),&BTPatrol::get_target_count);
	ObjectTypeDB::bind_method(_MD("get_targets"),&BTPatrol::get_targets);
	ObjectTypeDB::bind_method(_MD("get_target", "idx"),&BTPatrol::get_target);
	ObjectTypeDB::bind_method(_MD("get_current_target"),&BTPatrol::get_current_target);
	ObjectTypeDB::bind_method(_MD("get_current_target_index"),&BTPatrol::get_current_target_index);
	ObjectTypeDB::bind_method(_MD("set_current_target_index", "index"),&BTPatrol::set_current_target_index);

	ADD_PROPERTY( PropertyInfo(Variant::STRING,"target_patrol_group"), _SCS("set_target_group"), _SCS("get_target_group") );
	ADD_PROPERTY( PropertyInfo(Variant::REAL,"distance"), _SCS("set_distance"), _SCS("get_distance") );
}


void BTPatrol::reset_node() {
	current_patrol_index = 0;
	current_target = NULL;
	BehaviorTreeNode::reset_node();
}


void BTPatrol::_init_patrol_points() {
	if ( get_tree() != NULL ) {
		List<Node*> target_nodes;

		get_tree()->get_nodes_in_group(target_patrol_group, &target_nodes);

		for ( int i = 0; i < target_nodes.size(); i++ ) {
			add_target(target_nodes[i]);
		}
	}
}


inline void BTPatrol::_correct_patrol_index() {
	current_patrol_index = current_patrol_index % patrol_targets.size();
}


int BTPatrol::_check_points() {

	if ( navigator == NULL ) {
		return FAILED;
	}

	if ( patrol_targets.size() > 0 ) {
		real_t check_dist = _get_distance_to_node(patrol_targets[current_patrol_index]);
		real_t sqr_distance = distance * distance;

		if ( check_dist <= sqr_distance ) {
			Node* new_target;

			current_patrol_index++;

			if ( current_patrol_index >= patrol_targets.size() ) {

				return SUCCESS;
			}

			_correct_patrol_index();

			new_target = get_current_target();

			if ( current_target != new_target ) {
				current_target = new_target;
				notify_target_changed(new_target);
			}
		}
	}

	return RUNNING;
}


void BTPatrol::execute() {
	if ( patrol_targets.size() > 0 ) {
		if ( current_target == NULL ) {
			current_target = patrol_targets[0];
			notify_target_changed(current_target);
			status = RUNNING;
			return;
		}
		else {
			status = _check_points();
			return;
		}
	}

	status = SUCCESS;
}


void BTPatrol::remove_target(Node* target) {
	int target_index = find_target(target);

	if ( target_index != -1 ) {
		patrol_targets.remove(target_index);
	}
}


int BTPatrol::find_target(Node* target) {
	for ( int i = 0; i < patrol_targets.size(); i++ ) {
		if ( patrol_targets[i] == target ) {
			return i;
		}
	}

	return -1;
}


int BTPatrol::get_target_count() const {
	return patrol_targets.size();
}


Array BTPatrol::get_targets() const {

	Array arr;
	int cc = get_target_count();
	arr.resize(cc);
	for(int i=0;i<cc;i++)
		arr[i]=get_target(i);

	return arr;
}


Node* BTPatrol::get_target(int p_index) const {

	ERR_FAIL_INDEX_V( p_index, patrol_targets.size(), NULL );

	return patrol_targets[p_index];
}


Node* BTPatrol::get_current_target() const {

	return patrol_targets[current_patrol_index];
}


int BTPatrol::get_current_target_index() const {

	return current_patrol_index;
}


void BTPatrol::set_current_target_index(int p_index) {

	current_patrol_index = p_index;

	_correct_patrol_index();
}
