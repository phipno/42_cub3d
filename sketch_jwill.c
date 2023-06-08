-------------------------------------------------------------------------------

<feature><minimap>

player pos:
	- get player_pos on minimap start/change
	- save the offset from original position to be able to redraw
	- prob need a formula to scale down

-------------------------------------------------------------------------------

<feature><raycasting>

typedef struct s_position
{
	double x;
	double y;
}		t_position;

t_position player, view_left, view_right, camera

-------------------------------------------------------------------------------
