#include "globals.h"

double collision_penetration(MOV *particle1, MOV *particle2)
{
  VECTOR v = vector_sub(&particle1->pos, &particle2->pos);
  double total_length = particle1->radius + particle2->radius;
  double l = vector_magnitude2(&v);
  if(l <= (total_length*total_length))
    return sqrt(l) - total_length;
  else
    return 1;
}

void resolve_penetration(MOV *particle1, MOV *particle2, double penetration, VECTOR *cn)
{
  // particle1 moves in the direction of contact normal and particle2 moves opposite to contact normal.
  double total_imass = particle1->imass + particle2->imass;
  double delta = penetration / total_imass;
  VECTOR p1 = vector_mult(cn, delta * particle1->imass);
  VECTOR p2 = vector_mult(cn, -1 * delta * particle2->imass);

  vector_add1(&particle1->pos, &p1);
  vector_add1(&particle2->pos, &p2);
}

void resolve_collision(MOV *particle1, MOV *particle2)
{
  double penetration = collision_penetration(particle1, particle2);
  if(penetration > 0)
    return;

  play_collision_sound(vector_magnitude2(&particle1->vel) +  vector_magnitude2(&particle2->vel));

  VECTOR cn; // contact normal
  cn = vector_sub(&particle1->pos, &particle2->pos);
  vector_normalize1(&cn);

  resolve_penetration(particle1, particle2, -1*penetration, &cn);

  VECTOR vs; // separating velocity
  vs = vector_sub(&particle1->vel, &particle2->vel);

  double s = vector_dot_product(&vs, &cn);
  if(s >= 0)
  {
    //     printf("%f %f %f %f %f\n", s, particle1->pos.x, particle1->pos.y, particle2->pos.x, particle2->pos.y);

    // printf("%f %f %f %f %f\n", s, particle1->vel.x, particle1->vel.y, particle2->vel.x, particle2->vel.y);
    return;
  }
  double ns = -s; // new separating velocity
  double delta_velocity = ns - s;
  double total_imass = particle1->imass + particle2->imass;
  double imp = delta_velocity / total_imass;
  VECTOR impulse = vector_mult(&cn, imp);
  VECTOR v1 = vector_mult(&impulse, particle1->imass);
  VECTOR v2 = vector_mult(&impulse, -1 * particle2->imass);

  vector_add1(&particle1->vel, &v1);
  vector_add1(&particle2->vel, &v2);
}

void resolve_collision_with_board(MOV *particle, BOARD *board)
{
  int i;
  for(i = 0; i < 4; i++)
  {
    resolve_penetration_with_side(&board->sides[i][0], &board->sides[i][1], particle);
  }
  // if(particle->pos.x - particle->radius <= board->sides[0][0].x)
  // {
  //   particle->pos.x = board->sides[0][0].x + particle->radius;
  //   particle->vel.x = -1 * particle->vel.x;
  // }

  // if(particle->pos.x + particle->radius >= board->sides[2][0].x)
  // {
  //   particle->pos.x = board->sides[2][0].x - particle->radius;
  //   particle->vel.x = -1 * particle->vel.x;
  // }

  // if(particle->pos.y + particle->radius >= board->sides[1][0].y)
  // {
  //   particle->pos.y = board->sides[1][0].y - particle->radius;
  //   particle->vel.y = -1 * particle->vel.y;
  // }

  // if(particle->pos.y - particle->radius <= board->sides[3][0].y)
  // {
  //   particle->pos.y = board->sides[3][0].y + particle->radius;
  //   particle->vel.y = -1 * particle->vel.y;
  // }
}

void move_to_hole(MOV *particle, int hole)
{
  if(particle->chip_type != NOT_CHIP_TYPE)
    chips_on_board--; // when particle is striker, this value should not be decreased.

  second_chance = 1;
  particle->in_hole = 1;
  particle->hole = hole;
  update_score_texture[current_player] = 1;
  if(particle->chip_type == BLACK)
    scores[current_player] += 10;
  else if(particle->chip_type == WHITE)
    scores[current_player] += 20;
}

void check_if_in_hole(MOV *particle, BOARD *board)
{
  if(!particle->in_hole)
  {
    VECTOR v = { 0, 0 };
    int i;
    for(i = 0; i < 4; i++)
    {
      v = vector_sub(&board->holes[i].pos, &particle->pos);
      if(vector_magnitude(&v) < board->holes[i].radius)
      {
        move_to_hole(particle, i);
        break;
      }
    }
  }
}

void resolve_collision_with_hole(MOV *particle, BOARD *board)
{
  check_if_in_hole(particle, board);
  if(particle->in_hole)
  { 
    VECTOR v;
    int i = particle->hole;
    v = vector_sub(&board->holes[i].pos, &particle->pos);
    if(vector_magnitude(&v) > board->holes[i].radius - particle->radius)
    {
      play_collision_sound(vector_magnitude2(&particle->vel));

      // resolve penetration in hole
      v = vector_normalize(&particle->vel);
      vector_mult1(&v, board->holes[i].radius - particle->radius);
      vector_add1(&v, &board->holes[i].pos);
      particle->pos = v;

      //set velocity after collision with hole boundary
      vector_mult1(&particle->vel, -0.9);
    }
  }
}

void integrate(MOV *particle)
{
  VECTOR v = { 0, 0 };
  v = vector_mult(&particle->acc, elapsed_time);

  vector_add1(&particle->vel, &v);

  vector_mult1(&particle->vel, 0.98);

  if(vector_magnitude(&particle->vel) < 1)
  {
    particle->vel = { 0, 0 };
    particle->state = STOPPED;

    if(particle->in_hole)
      particle->state = OUT_OF_GAME;
  } else
  {
    particle->state = MOVING;
  }

  v = vector_mult(&particle->vel, elapsed_time);
  vector_add1(&particle->pos, &v);

  vector_mult1(&particle->acc, 0);
}


double cross_product(VECTOR *s0, VECTOR *s1, VECTOR *p)
{
  VECTOR p1 = vector_sub(p, s0);
  VECTOR p2 = vector_sub(s1, s0);
  return determinant2d(&p1, &p2);
}


VECTOR perpendicular(VECTOR *s0, VECTOR *s1)
{
  VECTOR v = vector_sub(s1, s0);
  vector_normalize1(&v);
  VECTOR t = { v.y, -1 * v.x }; // perpendicular is clockwise from side
  return t;
}

VECTOR collision_point(VECTOR *s0, VECTOR *s1, MOV *particle)
{
  VECTOR perp = perpendicular(s0, s1);
  vector_mult1(&perp, -1 * particle->radius); // collision point should be calculated by reversing the perpendicular
  VECTOR v = particle->pos;
  vector_add1(&v, &perp);
  return v;
}

void resolve_penetration_with_side(VECTOR *s0, VECTOR *s1, MOV *particle)
{
  VECTOR cp = collision_point(s0, s1, particle);
  if(cross_product(s0, s1, &cp) >= 0)
    return; // no need to resolve penetration since particle is lying on the other side.

 if (!particle->is_silent)
   play_collision_sound(vector_magnitude2(&particle->vel)); 

  VECTOR v = particle->vel;
  vector_mult1(&v, -1); // reversing particle's velocity since it needs to be moved in other direction to resolve penetration
  vector_normalize1(&v);

  VECTOR p1 = vector_sub(&cp, s0);
  VECTOR p2 = vector_sub(s1, s0);

  double d1 = determinant2d(&p1, &p2);
  double d2 = determinant2d(&p2, &v);


  double t = d1/d2;
  vector_mult1(&v, t);
  vector_add1(&cp, &v); // move cp to side's boundary
  v = perpendicular(s0, s1);
  vector_mult1(&v, particle->radius);
  vector_add1(&cp, &v);
  particle->pos = cp;


  vector_normalize1(&p2);
  VECTOR v1 = vector_mult(&p2, 2 * vector_dot_product(&particle->vel, &p2));
  particle->vel = vector_sub(&v1, &particle->vel); // set particle's velocity to its reflection along give side.
}