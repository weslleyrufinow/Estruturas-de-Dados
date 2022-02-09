typedef struct Point2d Point2d;

Point2d *Point2d_create(float , float );
Point2d *Point2d_delete(Point2d *);

float Point2d_getX(Point2d *);
float Point2d_getY(Point2d *);

Point2d *Point2d_setX(Point2d *, float);
Point2d *Point2d_setY(Point2d *, float);

float Point2d_distance(Point2d *,Point2d *);
