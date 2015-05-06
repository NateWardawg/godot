
#include "bt_inverter_node.h"


void BTInverterNode::execute() {
	state = (leaf_node != NULL) ? -leaf_node->process_logic() : SUCCESS;
}
