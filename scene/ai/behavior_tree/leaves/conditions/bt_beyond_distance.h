#ifndef BT_BEYONDDISTANCE_NODE_H
#define BT_BEYONDDISTANCE_NODE_H

#include "bt_distance.h"


class BTBeyondDistance : public BTDistance
{

	GDCLASS( BTBeyondDistance, BTDistance )
	OBJ_CATEGORY("AI")

protected:

	virtual bool _check_distance(real_t check_distance, real_t target_distance) { return check_distance >= target_distance; }

};

#endif // BT_BEYONDDISTANCE_NODE_H
