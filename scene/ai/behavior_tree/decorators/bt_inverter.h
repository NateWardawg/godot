#ifndef BT_INVERTER_NODE_H
#define BT_INVERTER_NODE_H

#include "bt_decorator.h"

class BTInverter : public BTDecorator
{

	OBJ_TYPE( BTInverter, BTDecorator )
	OBJ_CATEGORY("AI")

protected:

	virtual void execute();

};

#endif // BT_INVERTER_NODE_H
