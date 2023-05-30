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

//	Floats/doubles instead of int??? 
//	--> allows for better / smoother calculation
//	-->could do both like point_f(loat) & point_i(nt) & point_d(ouble)

//	what about using smaller int type 
//	...for performance.. pixels will only be < 4k

//	Just a simple point/position on the map
typedef struct s_point
{
	int x;
	int y;
}			t_point;

void	point_set(t_point *a, int x, int y);
t_point	point_get_new(int x, int y);
t_point	point_get_dup(t_point b);
t_point	point_get_midpoint(t_point a, t_point b);
void	debug_print_point(t_point a, char *name);

//	A struct describing a start and an end point
//	which is basically a line
typedef struct s_vector
{
	t_point	start;
	t_point	end;
}			t_vector;

void		vector_set(t_vector *v, t_point start, t_point end);
t_vector	vector_get_new(t_point start, t_point end);
t_vector	vector_get_dup(t_vector v);
//			checks wether two vectors have a middle point / intersection
t_point		vector_get_intersection(t_vector v, t_vector w);
void		debug_print_vector(t_vector v, char *name);

//	A simple square (four corners) which would help for the grid / drawing the
//	minimap and/or blocks. 
typedef struct s_square
{
	t_point	top_left;
	t_point	top_right;
	t_point	bottom_left;
	t_point	bottom_right;
}			t_square;

//			i think these two are kind of unneccessary but could just be 
//			an alternative design choice ...
void		square_set_by_points(t_square *sq, t_point start, t_point end);
t_square	*square_get_new_by_points(t_point start, t_point end);

//			a vector is enough to calculate a square
void		square_set_by_vector(t_square *sq, t_vector *v);
t_square	*square_get_new_by_vector(t_vector *v);

//			or just calculate it with size (where size is actually 
//			length * width but for a square length & width are equal)
t_square	*square_get_new_by_size(t_point start, int size);

//			checks wether from a current pos (for e.g. player position) the 
//			square is hit by a ray ... prob need some struct / var for 
//			direction
t_point		*square_get_intersection(t_point pos, t_square sq);
void		debug_print_square(t_square sq, char *name);

-------------------------------------------------------------------------------
