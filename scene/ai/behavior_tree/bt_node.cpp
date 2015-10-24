#include "bt_node.h"


BehaviorTreeNode::BehaviorTreeNode() {
	status = RUNNING;
}


void BehaviorTreeNode::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_status"),&BehaviorTreeNode::get_status);
	ObjectTypeDB::bind_method(_MD("set_status", "status"),&BehaviorTreeNode::set_status);

	BIND_VMETHOD( MethodInfo("_success") );
	BIND_VMETHOD( MethodInfo("_running") );
	BIND_VMETHOD( MethodInfo("_failed") );

	BIND_CONSTANT( FAILED );
	BIND_CONSTANT( RUNNING );
	BIND_CONSTANT( SUCCESS );

	ADD_SIGNAL( MethodInfo("success") );
	ADD_SIGNAL( MethodInfo("running") );
	ADD_SIGNAL( MethodInfo("failed") );
}


void BehaviorTreeNode::reset_node() {
	status = RUNNING;
}


void BehaviorTreeNode::set_status(int p_status) {
	if ( p_status >= FAILED && p_status <= SUCCESS ) {
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
		call = "failed";
	}

	emit_signal(call);

	if (get_script_instance()) {
		get_script_instance()->call_multilevel_reversed(String("_") + call,NULL,0);
	}
}
