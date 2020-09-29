#ifndef __ddVec__
#define __ddVec__

#include <math.h>

typedef struct ddVec2 ddVec2;
typedef struct ddVec3 ddVec3;



ddVec2 make_ddVec2(float _x, float _y);

void v2add(ddVec2* _d, const ddVec2 _s);
void v2sub(ddVec2* _d, const ddVec2 _s);
void v2mul(ddVec2* _d, const ddVec2 _s);
void v2div(ddVec2* _d, const ddVec2 _s);
void v2dot(ddVec2* _d, const ddVec2 _s);
float v2mag(ddVec2 _d);
ddVec2 v2norm(ddVec2 _d);



ddVec3 make_ddVec3(float _x, float _y, float _z);

void v3add(ddVec3* _d, const ddVec3 _s);
void v3sub(ddVec3* _d, const ddVec3 _s);
void v3mul(ddVec3* _d, const ddVec3 _s);
void v3div(ddVec3* _d, const ddVec3 _s);
void v3dot(ddVec3* _d, const ddVec3 _s);
float v3mag(ddVec3 _d);
ddVec3 v3norm(ddVec3 _d);




struct ddVec2
{
	float x;
	float y;
};

struct ddVec3
{
	float x;
	float y;
	float z;
};






ddVec2 make_ddVec2(float _x, float _y)
{
	ddVec2 _o;
	_o.x = _x;
	_o.y = _y;
	return _o;
}



void v2add(ddVec2* _d, const ddVec2 _s)
{
	_d->x += _s.x;
	_d->y += _s.y;
}
void v2sub(ddVec2* _d, const ddVec2 _s)
{
	_d->x -= _s.x;
	_d->y -= _s.y;
}
void v2mul(ddVec2* _d, const ddVec2 _s)
{
	_d->x *= _s.x;
	_d->y *= _s.y;
}
void v2div(ddVec2* _d, const ddVec2 _s)
{
	_d->x /= _s.x;
	_d->y /= _s.y;
}
void v2dot(ddVec2* _d, const ddVec2 _s)
{
	_d->x *= _s.x;
	_d->y *= _s.y;
}
float v2mag(ddVec2 _d)
{
	return (float)sqrt(pow(_d.x, 2) + pow(_d.y, 2));
}
ddVec2 v2norm(ddVec2 _d)
{
	ddVec2 _o;
	float mag = v2mag(_d);
	_o.x = _d.x / mag;
	_o.y = _d.y / mag;
	return _o;
}





ddVec3 make_ddVec3(float _x, float _y, float _z)
{
	ddVec3 _o;
	_o.x = _x;
	_o.y = _y;
	_o.z = _z;
	return _o;
}


void v3add(ddVec3* _d, const ddVec3 _s)
{
	_d->x += _s.x;
	_d->y += _s.y;
	_d->z += _s.z;
}
void v3sub(ddVec3* _d, const ddVec3 _s)
{
	_d->x -= _s.x;
	_d->y -= _s.y;
	_d->z -= _s.z;
}
void v3mul(ddVec3* _d, const ddVec3 _s)
{
	_d->x *= _s.x;
	_d->y *= _s.y;
	_d->z *= _s.z;
}
void v3div(ddVec3* _d, const ddVec3 _s)
{
	_d->x /= _s.x;
	_d->y /= _s.y;
	_d->z /= _s.z;
}
void v3dot(ddVec3* _d, const ddVec3 _s)
{
	_d->x *= _s.x;
	_d->y *= _s.y;
	_d->z *= _s.z;
}
float v3mag(ddVec3 _d)
{
	return (float)sqrt(pow(_d.x, 2) + pow(_d.y, 2) + pow(_d.z, 2));
}
ddVec3 v3norm(ddVec3 _d)
{
	ddVec3 _o;
	float mag = v3mag(_d);
	_o.x = _d.x / mag;
	_o.y = _d.y / mag;
	_o.z = _d.z / mag;
	return _o;
}


#endif
