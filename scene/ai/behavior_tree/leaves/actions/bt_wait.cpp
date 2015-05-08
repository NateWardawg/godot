
#include "bt_wait.h"


void BTWait::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_READY: {
			reset_timer();
		} break;
	}
}


void BTWait::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_wait_time"),&BTWait::get_wait_time);
	ObjectTypeDB::bind_method(_MD("set_wait_time", "duration"),&BTWait::set_wait_time);
	ObjectTypeDB::bind_method(_MD("set_time_remaining"),&BTWait::set_time_remaining);
	ObjectTypeDB::bind_method(_MD("get_time_remaining"),&BTWait::get_time_remaining);
	ObjectTypeDB::bind_method(_MD("reset_timer"),&BTWait::reset_timer);

	ADD_PROPERTY( PropertyInfo(Variant::REAL,"wait_time"), _SCS("set_wait_time"), _SCS("get_wait_time") );
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
	print_line(String::num_real(time_remaining));
	print_line(String::num_real(get_process_delta_time()));

	time_remaining -= get_process_delta_time();

	status = time_remaining <= 0 ? SUCCESS : RUNNING;
}
