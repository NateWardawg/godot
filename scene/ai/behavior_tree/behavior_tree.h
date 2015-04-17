
#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H

#include "scene/main/node.h"
#include "scene/ai/ai.h"

#include "scene/3d/spatial.h"


class BehaviorTree : public AI {

	OBJ_TYPE( BehaviorTree, AI )
	OBJ_CATEGORY("AI")

protected:

	static void _bind_methods();
	void _notification(int p_what);

public:

	int value = 0;

	int get_value() { return value; }
	void set_value(int newValue) { value = newValue; }
};

#endif // BEHAVIOR_TREE_H
