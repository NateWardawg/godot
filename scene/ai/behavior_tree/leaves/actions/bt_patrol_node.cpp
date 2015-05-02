
#include "bt_patrol_node.h"


BTPatrolNode::BTPatrolNode() {
	distance = 1.0;
	current_target = NULL;
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
	ObjectTypeDB::bind_method(_MD("get_target_count"),&BTPatrolNode::get_target_count);
	ObjectTypeDB::bind_method(_MD("get_targets"),&BTPatrolNode::get_targets);
	ObjectTypeDB::bind_method(_MD("get_target", "idx"),&BTPatrolNode::get_target);
	ObjectTypeDB::bind_method(_MD("get_current_target"),&BTPatrolNode::get_current_target);
	ObjectTypeDB::bind_method(_MD("get_current_target_index"),&BTPatrolNode::get_current_target_index);
	ObjectTypeDB::bind_method(_MD("set_current_target_index", "index"),&BTPatrolNode::set_current_target_index);

	ADD_PROPERTY( PropertyInfo(Variant::STRING,"target_patrol_group"), _SCS("set_target_group"), _SCS("get_target_group") );
	ADD_PROPERTY( PropertyInfo(Variant::REAL,"distance"), _SCS("set_distance"), _SCS("get_distance") );
}

void BTPatrolNode::reset_node() {
	current_patrol_index = 0;
	current_target = NULL;
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


inline void BTPatrolNode::_correct_patrol_index() {
	current_patrol_index = current_patrol_index % patrol_targets.size();
}


int BTPatrolNode::_check_points() {

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


int BTPatrolNode::check_state() {
	if ( patrol_targets.size() > 0 ) {
		if ( current_target == NULL ) {
			current_target = patrol_targets[0];
			notify_target_changed(current_target);
			return RUNNING;
		}
		else {
			return _check_points();
		}
	}

	return SUCCESS;
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


int BTPatrolNode::get_target_count() const {
	return patrol_targets.size();
}


Array BTPatrolNode::get_targets() const {

	Array arr;
	int cc = get_target_count();
	arr.resize(cc);
	for(int i=0;i<cc;i++)
		arr[i]=get_target(i);

	return arr;
}


Node* BTPatrolNode::get_target(int p_index) const {

	ERR_FAIL_INDEX_V( p_index, patrol_targets.size(), NULL );

	return patrol_targets[p_index];
}


Node* BTPatrolNode::get_current_target() const {

	return patrol_targets[current_patrol_index];
}


int BTPatrolNode::get_current_target_index() const {

	return current_patrol_index;
}


void BTPatrolNode::set_current_target_index(int p_index) {

	current_patrol_index = p_index;

	_correct_patrol_index();
}
