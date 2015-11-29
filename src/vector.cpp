#include "globals.h"

void vector_add1(VECTOR *v1, VECTOR *v2)
{
  v1->x += v2->x;
  v1->y += v2->y;
}

double vector_magnitude2(VECTOR *v)
{
  return (v->x * v->x + v->y * v->y);
}

double vector_magnitude(VECTOR *v)
{
  return sqrt(v->x * v->x + v->y * v->y);
}

VECTOR vector_sub(VECTOR *v1, VECTOR *v2)
{
  VECTOR v;
  v.x = v1->x - v2->x;
  v.y = v1->y - v2->y;
  return v;
}

VECTOR vector_mult(VECTOR *v1, double k)
{
  VECTOR v;
  v.x = v1->x * k;
  v.y = v1->y * k;
  return v;
}

void vector_mult1(VECTOR *v, double k)
{
  v->x = v->x * k;
  v->y = v->y * k;
}

void vector_limit1(VECTOR *v, double max)
{
  double m = vector_magnitude(v);
  if(m > max)
  {
    vector_mult1(v, max / vector_magnitude(v));
  }
}

VECTOR vector_limit(VECTOR *v, double max)
{
  VECTOR v1 = { v->x, v->y };
  vector_limit1(&v1, max);
  return v1;
}

void vector_normalize1(VECTOR *v)
{
  vector_limit1(v, 1);
}

VECTOR vector_normalize(VECTOR *v)
{
  VECTOR v1 = { v->x, v->y };
  vector_normalize1(&v1);
  return v1;
}

double determinant2d(VECTOR *v1, VECTOR *v2)
{
  return v1->x * v2->y - v2->x * v1->y;
}

double vector_dot_product(VECTOR *v1, VECTOR *v2)
{
  return v1->x * v2->x + v1->y * v2->y;
}