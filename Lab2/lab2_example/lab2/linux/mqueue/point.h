/**
 * @file:   os/lab1/mqueue/point.h
 * @brief:  header file for modeling a point in a 2D space
 * @author: ece254/mte241 lab staff
 * @date:   2012/09/20
 */
struct point {
	int x;	/* x coordinate */
	int y;	/* y coordinate */
};

inline void set_position(int x, int y, struct point *buf);
inline int get_x_coord (struct point p);
inline int get_y_coord (struct point p);
