
#include "bt_wait.h"


void BTWait::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_READY: {
			reset_timer();
		} break;
	}
}


void BTWait::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_wait_time"),&BTWait::get_wait_time);
	ClassDB::bind_method(D_METHOD("set_wait_time", "duration"),&BTWait::set_wait_time);
	ClassDB::bind_method(D_METHOD("set_time_remaining"),&BTWait::set_time_remaining);
	ClassDB::bind_method(D_METHOD("get_time_remaining"),&BTWait::get_time_remaining);
	ClassDB::bind_method(D_METHOD("reset_timer"),&BTWait::reset_timer);

	ADD_PROPERTY( PropertyInfo(Variant::REAL,"wait_time"), "set_wait_time", "get_wait_time" );
}


void BTWait::reset_node() {
	reset_timer();
	BehaviorTreeNode::reset_node();
}


void BTWait::reset_timer() {
	time_remaining = wait_time;
}


void BTWait::execute()
{
	time_remaining -= get_process_delta_time();

	status = time_remaining <= 0 ? SUCCESS : RUNNING;
}
