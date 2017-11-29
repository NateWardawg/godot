#ifndef BT_AGENT_2D_H
#define BT_AGENT_2D_H

#include "scene/2d/node_2d.h"
#include "../core/behavior_tree.h"


class BTAgent2D : public Node2D {

	GDCLASS( BTAgent2D, Node2D )
	OBJ_CATEGORY("AI")

private:
	BehaviorTree *behaviorTree;

protected:
	void _notification(int p_what);

public:

	BTAgent2D();
	~BTAgent2D(){}

};

#endif // BT_AGENT_2D_H
