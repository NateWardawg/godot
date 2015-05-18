
#include "bt_parallel_all.h"


BTParallelAll::BTParallelAll() {
	fail_on_child_failure = true;
	use_master_node = true;
}


void BTParallelAll::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_fail_on_child_failure"),&BTParallelAll::get_fail_on_child_failure);
	ObjectTypeDB::bind_method(_MD("set_fail_on_child_failure"),&BTParallelAll::set_fail_on_child_failure);
	ObjectTypeDB::bind_method(_MD("get_use_master_node"),&BTParallelAll::get_use_master_node);
	ObjectTypeDB::bind_method(_MD("set_use_master_node"),&BTParallelAll::set_use_master_node);

	ADD_PROPERTY( PropertyInfo(Variant::BOOL,"fail_on_child_failure"), _SCS("set_fail_on_child_failure"), _SCS("get_fail_on_child_failure") );
	ADD_PROPERTY( PropertyInfo(Variant::BOOL,"use_master_node"), _SCS("set_use_master_node"), _SCS("get_use_master_node") );
}


void BTParallelAll::execute() {
	int successes = 0;

	for ( int i = 0; i < nodes.size(); i++ ) {
		int node_state = nodes[i]->get_status();

		if ( node_state == RUNNING ) {
			nodes[i]->process_logic();
		} else {
			if ( node_state == SUCCESS ) {
				successes++;
			} else if ( node_state == FAILED ) {
				if ( fail_on_child_failure ) {
					status = FAILED;
					return;
				} else {
					successes++;
				}
			}
		}
	}

	if ( use_master_node ) {
		status = nodes[0]->get_status();
	} else {
		status = (successes == nodes.size()) ? SUCCESS : RUNNING;
	}
}


void BTParallelAll::init_composite() {
	status = RUNNING;
}
