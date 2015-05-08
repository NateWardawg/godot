
#include "bt_inverter.h"


void BTInverter::execute() {
	status = (leaf_node != NULL) ? -leaf_node->process_logic() : SUCCESS;
}
