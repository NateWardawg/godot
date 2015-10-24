
#include "bt_parallel_all.h"


VARIANT_ENUM_CAST(BTParallelAll::ExitCondition)


BTParallelAll::BTParallelAll() {
	success_condition = FIRST_CHILD;
	failure_condition = ANY_CHILD;
}


void BTParallelAll::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("get_success_condition"),&BTParallelAll::get_success_condition);
	ObjectTypeDB::bind_method(_MD("set_success_condition","mode"),&BTParallelAll::set_success_condition);
	ObjectTypeDB::bind_method(_MD("get_failure_condition"),&BTParallelAll::get_failure_condition);
	ObjectTypeDB::bind_method(_MD("set_failure_condition"),&BTParallelAll::set_failure_condition);

	BIND_CONSTANT( FIRST_CHILD );
	BIND_CONSTANT( ANY_CHILD );
	BIND_CONSTANT( ALL_CHILDREN );

	ADD_PROPERTYNZ( PropertyInfo( Variant::INT, "success_condition",PROPERTY_HINT_ENUM,"First Child,Any Child,All Children" ), _SCS("set_success_condition"),_SCS("get_success_condition" ) );
	ADD_PROPERTYNZ( PropertyInfo( Variant::INT, "failure_condition",PROPERTY_HINT_ENUM,"First Child,Any Child,All Children" ), _SCS("set_failure_condition"),_SCS("get_failure_condition" ) );
}


void BTParallelAll::set_success_condition(ExitCondition p_success_condition) {
	success_condition = p_success_condition;
}


BTParallelAll::ExitCondition BTParallelAll::get_success_condition() const {
	return success_condition;
}


void BTParallelAll::set_failure_condition(ExitCondition p_failure_condition) {
	failure_condition = p_failure_condition;
}


BTParallelAll::ExitCondition BTParallelAll::get_failure_condition() const {
	return failure_condition;
}


void BTParallelAll::comp_execute() {
	int successes = 0;
	int failures = 0;

	if ( get_success_condition() == FIRST_CHILD ) {
		if ( nodes[0]->get_status() == SUCCESS ) {
			status = SUCCESS;
			return;
		}
	}

	if ( get_failure_condition() == FIRST_CHILD ) {
		if ( nodes[0]->get_status() == FAILED ) {
			status = FAILED;
			return;
		}
	}

	for ( int i = 0; i < nodes.size(); i++ ) {
		int node_state = nodes[i]->get_status();

		if ( node_state == RUNNING ) {
			nodes[i]->process_logic();
		} else {
			if ( node_state == SUCCESS ) {
				if ( get_success_condition() == ANY_CHILD ) {
					status = SUCCESS;
					return;
				} else {
					successes++;
				}
			} else if ( node_state == FAILED ) {
				if ( get_failure_condition() == ANY_CHILD ) {
					status = FAILED;
					return;
				} else {
					failures++;
				}
			}
		}
	}

	if ( get_success_condition() == ALL_CHILDREN && successes == nodes.size() ) {
		status = SUCCESS;
	}

	if ( get_failure_condition() == ALL_CHILDREN && failures == nodes.size() ) {
		status = FAILED;
	}
}


void BTParallelAll::init_composite() {
	status = RUNNING;
}
