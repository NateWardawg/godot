
#ifndef BT_TIMER_NODE_H
#define BT_TIMER_NODE_H

#include "../bt_action_node.h"


class BTWaitNode : public BTActionNode
{

	OBJ_TYPE( BTWaitNode, BTActionNode )
	OBJ_CATEGORY("AI")

	real_t wait_time;
	real_t time_remaining;

	float a_func() { return get_process_delta_time(); }

protected:

	virtual int check_state();

public:

	static void _bind_methods();

	virtual void reset_node() {
		reset_timer();
	}

	void set_wait_time(float p_time) { wait_time = p_time; }
	float get_wait_time() { return wait_time; }
	void set_time_remaining(float p_duration) { time_remaining = p_duration; }
	float get_time_remaining() { return time_remaining; }
	void reset_timer() { time_remaining = wait_time; }

	BTWaitNode();

};

#endif // BT_TIMER_NODE_H
