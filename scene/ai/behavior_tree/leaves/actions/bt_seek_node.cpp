
#include "bt_seek_node.h"


BTSeekNode::BTSeekNode()
{
}


void BTSeekNode::_bind_methods() {
	/*ObjectTypeDB::bind_method(_MD("get_wait_time"),&BTWaitNode::get_wait_time);
	ObjectTypeDB::bind_method(_MD("set_wait_time", "duration"),&BTWaitNode::set_wait_time);
	ObjectTypeDB::bind_method(_MD("set_time_remaining"),&BTWaitNode::set_time_remaining);
	ObjectTypeDB::bind_method(_MD("get_time_remaining"),&BTWaitNode::get_time_remaining);
	ObjectTypeDB::bind_method(_MD("reset_timer"),&BTWaitNode::reset_timer);

	ADD_PROPERTY( PropertyInfo(Variant::REAL,"wait_time"), _SCS("set_wait_time"), _SCS("get_wait_time") );*/
}


void BTSeekNode::execute()
{
	state = RUNNING;
}
