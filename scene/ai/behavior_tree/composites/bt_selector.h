
#ifndef BTSELECTORNODE_H
#define BTSELECTORNODE_H

#include "bt_composite.h"


class BTSelector : public BTComposite
{

	OBJ_TYPE( BTSelector, BTComposite )
	OBJ_CATEGORY("AI")

public:

	static void _bind_methods();

	virtual void execute();

	int get_current_leaf_index();

};

#endif // BTSELECTORNODE_H
