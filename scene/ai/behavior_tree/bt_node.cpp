#include "bt_node.h"
#include "composites/bt_parallel_any.h"


BehaviorTreeNode::BehaviorTreeNode() {
	state = RUNNING;
}


void BehaviorTreeNode::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_result"),&BehaviorTreeNode::get_result);
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
	state = RUNNING;
}


int BehaviorTreeNode::process_logic() {
	int result;

	execute();

	result = get_result();

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
