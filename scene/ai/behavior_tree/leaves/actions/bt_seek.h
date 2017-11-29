#ifndef BT_SEEK_NODE_H
#define BT_SEEK_NODE_H

#include "../bt_action.h"


class BTSeek : public BTAction
{

	GDCLASS( BTSeek, BTAction )
	OBJ_CATEGORY("AI")

protected:

	virtual void execute();

public:

	static void _bind_methods();

	BTSeek();

};

#endif // BT_SEEK_NODE_H
