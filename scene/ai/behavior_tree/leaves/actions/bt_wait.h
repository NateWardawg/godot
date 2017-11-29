
#ifndef BT_TIMER_NODE_H
#define BT_TIMER_NODE_H

#include "../bt_action.h"


class BTWait : public BTAction
{

	GDCLASS( BTWait, BTAction )
	OBJ_CATEGORY("AI")

	real_t wait_time;
	real_t time_remaining;

protected:

	virtual void execute();

public:

	static void _bind_methods();
	void _notification(int p_what);

	virtual void reset_node();

	void set_wait_time(float p_time) { wait_time = p_time; }
	float get_wait_time() { return wait_time; }
	void set_time_remaining(float p_duration) { time_remaining = p_duration; }
	float get_time_remaining() { return time_remaining; }
	void reset_timer();

};

#endif // BT_TIMER_NODE_H
