#include "bt_node.h"

void BehaviorTreeNode::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_result"),&BehaviorTreeNode::get_result);
	BIND_VMETHOD( MethodInfo("_success") );
	BIND_VMETHOD( MethodInfo("_running") );
	BIND_VMETHOD( MethodInfo("_failed") );
}


int BehaviorTreeNode::process_logic() {
	int result = get_result();

	if (get_script_instance()) {
		if ( result == SUCCESS ) {
			get_script_instance()->call_multilevel_reversed("_success",NULL,0);
		}
		else if ( RUNNING ) {
			get_script_instance()->call_multilevel_reversed("_running",NULL,0);
		}
		else /* FAILED */ {
			get_script_instance()->call_multilevel_reversed("_failed",NULL,0);
		}
	}

	return result;
}
