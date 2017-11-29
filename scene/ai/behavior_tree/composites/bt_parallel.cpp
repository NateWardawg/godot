
#include "bt_parallel.h"


VARIANT_ENUM_CAST(BTParallel::ExitCondition)


BTParallel::BTParallel() {
	success_condition = FIRST_CHILD;
	failure_condition = ANY_CHILD;
}


void BTParallel::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_success_condition"),&BTParallel::get_success_condition);
	ClassDB::bind_method(D_METHOD("set_success_condition","condition"),&BTParallel::set_success_condition);
	ClassDB::bind_method(D_METHOD("get_failure_condition"),&BTParallel::get_failure_condition);
	ClassDB::bind_method(D_METHOD("set_failure_condition","condition"),&BTParallel::set_failure_condition);

	BIND_CONSTANT( FIRST_CHILD );
	BIND_CONSTANT( ANY_CHILD );
	BIND_CONSTANT( ALL_CHILDREN );

	ADD_PROPERTYNZ( PropertyInfo( Variant::INT, "success_condition",PROPERTY_HINT_ENUM,"First Child,Any Child,All Children" ), "set_success_condition", "get_success_condition" );
	ADD_PROPERTYNZ( PropertyInfo( Variant::INT, "failure_condition",PROPERTY_HINT_ENUM,"First Child,Any Child,All Children" ), "set_failure_condition", "get_failure_condition" );
}


void BTParallel::set_success_condition(ExitCondition p_success_condition) {
	success_condition = p_success_condition;
}


BTParallel::ExitCondition BTParallel::get_success_condition() const {
	return success_condition;
}


void BTParallel::set_failure_condition(ExitCondition p_failure_condition) {
	failure_condition = p_failure_condition;
}


BTParallel::ExitCondition BTParallel::get_failure_condition() const {
	return failure_condition;
}


void BTParallel::comp_execute() {
	int successes = 0;
	int failures = 0;

	if ( get_success_condition() == FIRST_CHILD ) {
		if ( nodes[0]->get_status() == SUCCESS ) {
			status = SUCCESS;
			return;
		}
	}

	if ( get_failure_condition() == FIRST_CHILD ) {
		if ( nodes[0]->get_status() == FAILURE ) {
			status = FAILURE;
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
			} else if ( node_state == FAILURE ) {
				if ( get_failure_condition() == ANY_CHILD ) {
					status = FAILURE;
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
		status = FAILURE;
	}
}


void BTParallel::init_composite() {
	status = RUNNING;
}
