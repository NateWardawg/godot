
#ifndef BT_WITHINDISTANCE_NODE_H
#define BT_WITHINDISTANCE_NODE_H

#include "bt_distance.h"


class BTWithinDistance : public BTDistance
{

	GDCLASS( BTWithinDistance, BTDistance )
	OBJ_CATEGORY("AI")

protected:

	virtual bool _check_distance(real_t check_distance, real_t target_distance) { return check_distance <= target_distance; }

};

#endif // BT_WITHINDISTANCE_NODE_H
