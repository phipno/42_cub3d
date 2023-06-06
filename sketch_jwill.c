-------------------------------------------------------------------------------

<feature><minimap>

- functionality that scales var/values according to WIDTH & HEIGHT Macros
- concept on when to allocate / stack the minimap and points
	... what to do on a redraw (which var stay const/same
		... and which have to be recalculated)

General idea:
Loop through a certain amount of pixels (size of minimap)
	Loop through array
		For every thing in array put size amount of pixels and colour depending
		... on object (player, wall, floor / mb even fov)

-------------------------------------------------------------------------------

<general><structs>

-------------------------------------------------------------------------------
