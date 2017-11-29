
#include "bt_patrol.h"


VARIANT_ENUM_CAST(BTPatrol::LoopEndMode)


BTPatrol::BTPatrol() {
	waypoint_threshold = 1.0;
	patrol_direction = 1;
	patrol_end_mode = LOOP;
	current_target = NULL;
	navigator = NULL;
}


void BTPatrol::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_navigator"),&BTPatrol::get_navigator);
	ClassDB::bind_method(D_METHOD("set_navigator","agent"),&BTPatrol::set_navigator);
	ClassDB::bind_method(D_METHOD("get_waypoint_threshold"),&BTPatrol::get_waypoint_threshold);
	ClassDB::bind_method(D_METHOD("set_waypoint_threshold","distance"),&BTPatrol::set_waypoint_threshold);
	ClassDB::bind_method(D_METHOD("add_target", "node"),&BTPatrol::add_target);
	ClassDB::bind_method(D_METHOD("remove_target"),&BTPatrol::remove_target);
	ClassDB::bind_method(D_METHOD("find_target"),&BTPatrol::find_target);
	ClassDB::bind_method(D_METHOD("get_target_count"),&BTPatrol::get_target_count);
	ClassDB::bind_method(D_METHOD("get_targets"),&BTPatrol::get_targets);
	ClassDB::bind_method(D_METHOD("get_target", "index"),&BTPatrol::get_target);
	ClassDB::bind_method(D_METHOD("get_current_target"),&BTPatrol::get_current_target);
	ClassDB::bind_method(D_METHOD("get_current_target_index"),&BTPatrol::get_current_target_index);
	ClassDB::bind_method(D_METHOD("set_current_target_index", "index"),&BTPatrol::set_current_target_index);
	ClassDB::bind_method(D_METHOD("get_patrol_end_mode"),&BTPatrol::get_patrol_end_mode);
	ClassDB::bind_method(D_METHOD("set_patrol_end_mode", "mode"),&BTPatrol::set_patrol_end_mode);

	BIND_CONSTANT( LOOP );
	BIND_CONSTANT( PING_PONG );

	ADD_PROPERTY( PropertyInfo(Variant::REAL,"waypoint_threshold"), "set_waypoint_threshold", "get_waypoint_threshold" );
	ADD_PROPERTYNZ( PropertyInfo(Variant::INT,"patrol_end_mode",PROPERTY_HINT_ENUM,"Loop,Ping Pong" ), "set_patrol_end_mode", "get_patrol_end_mode" );
}


void BTPatrol::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_READY: {
			_find_navigator();
		} break;
	}
}


void BTPatrol::reset_node() {
	current_patrol_index = 0;
	current_target = NULL;
	BehaviorTreeNode::reset_node();
}


void BTPatrol::_init_patrol_points() {
	if ( get_tree() != NULL ) {
		for ( int i = 0; i < get_child_count(); i++ ) {
			Node* node = get_child(i);

			if ( is_node_valid_patrol_point(node) ) {
				add_target(node);
			}
		}
	}
}


void BTPatrol::_find_navigator()
{
	Node* parent = this;

	while ( parent != NULL ) {
		if ( !is_correct_agent(parent) ) {
			parent = parent->get_parent();
		}
		else {
			navigator = parent;
			return;
		}
	}
}


inline void BTPatrol::_correct_patrol_index() {
	current_patrol_index = current_patrol_index % patrol_targets.size();
}


int BTPatrol::_check_points() {

	if ( navigator == NULL ) {
		return FAILURE;
	}

	if ( patrol_targets.size() > 0 ) {
		real_t check_dist = _get_distance_to_node(patrol_targets[current_patrol_index]);
		real_t sqr_distance = waypoint_threshold * waypoint_threshold;

		if ( check_dist <= sqr_distance ) {
			Node* new_target;
			bool patrol_ended;

			current_patrol_index += patrol_direction;

			if ( patrol_direction == 1 ) {
				patrol_ended = current_patrol_index >= patrol_targets.size();
			} else if ( patrol_direction == -1 ) {
				patrol_ended = current_patrol_index < 0;
			}

			if ( patrol_ended ) {
				if ( patrol_end_mode == LOOP ) {
				} else if ( patrol_end_mode == PING_PONG ) {
					current_patrol_index -= patrol_direction;
					patrol_direction*=-1;
				}
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