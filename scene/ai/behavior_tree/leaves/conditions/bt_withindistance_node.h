
#ifndef BT_WITHINDISTANCE_NODE_H
#define BT_WITHINDISTANCE_NODE_H

#include "bt_distance_node.h"


class BTWithinDistanceNode : public BTDistanceNode
{

	OBJ_TYPE( BTWithinDistanceNode, BTDistanceNode )
	OBJ_CATEGORY("AI")

protected:

	virtual bool check_distance(real_t check_distance, real_t target_distance) { return check_distance <= target_distance; }

};

#endif // BT_WITHINDISTANCE_NODE_H
