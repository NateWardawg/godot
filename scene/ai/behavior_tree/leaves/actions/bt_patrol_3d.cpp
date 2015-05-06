#include "bt_patrol_3d.h"


BTPatrol3D::BTPatrol3D()
{
}


float BTPatrol3D::_get_distance_to_node(Node *p_patrol_node) {
	BTAgent3D* agent = (BTAgent3D*)navigator;
	Spatial* spatial_target = (Spatial*)p_patrol_node;

	return agent->get_translation().distance_squared_to(spatial_target->get_translation());
}


void BTPatrol3D::notify_target_changed(Node *new_target) {
	if ( navigator != NULL ) {
		BTAgent3D* navigator3D = dynamic_cast<BTAgent3D*>(navigator);
		navigator3D->notify_target_changed(new_target);
	}
}
