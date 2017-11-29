
#ifndef BTSELECTORNODE_H
#define BTSELECTORNODE_H

#include "bt_sequence.h"


class BTSelector : public BTSequence
{

	GDCLASS( BTSelector, BTSequence )
	OBJ_CATEGORY("AI")

protected:

	virtual BehaviorStatus get_continue_status() { return FAILURE; }
	virtual BehaviorStatus get_end_status() { return SUCCESS; }

};

#endif // BTSELECTORNODE_H
