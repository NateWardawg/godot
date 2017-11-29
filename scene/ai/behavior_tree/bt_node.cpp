#include "bt_node.h"


BehaviorTreeNode::BehaviorTreeNode() {
	status = RUNNING;
}


void BehaviorTreeNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_agent"), &BehaviorTreeNode::get_agent);
	ClassDB::bind_method(D_METHOD("get_status"), &BehaviorTreeNode::get_status);
	ClassDB::bind_method(D_METHOD("set_status", "status"), &BehaviorTreeNode::set_status);

	BIND_VMETHOD( MethodInfo("_success") );
	BIND_VMETHOD( MethodInfo("_running") );
	BIND_VMETHOD( MethodInfo("_failure") );

	BIND_CONSTANT( FAILURE );
	BIND_CONSTANT( RUNNING );
	BIND_CONSTANT( SUCCESS );

	ADD_SIGNAL( MethodInfo("success") );
	ADD_SIGNAL( MethodInfo("running") );
	ADD_SIGNAL( MethodInfo("failure") );
}


Node* BehaviorTreeNode::get_agent() const {
	return behavior_tree->get_agent_node();
}


void BehaviorTreeNode::reset_node() {
	status = RUNNING;
}


void BehaviorTreeNode::set_status(int p_status) {
	if ( p_status >= FAILURE && p_status <= SUCCESS ) {
		status = p_status;
	}
}


int BehaviorTreeNode::process_logic() {
	int result;

	execute();

	result = get_status();

	_execute_calls(result);

	return result;
}


void BehaviorTreeNode::_execute_calls(int result) {
	String call;

	if ( result == SUCCESS ) {
		call = "success";
	}
	else if ( result == RUNNING ) {
		call = "running";
	}
	else /* FAILED */ {
		call = "failure";
	}

	emit_signal(call);

	if (get_script_instance()) {
		get_script_instance()->call_multilevel_reversed(String("_") + call,NULL,0);
	}
}
