/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
/*================================================================
 *
 * Project : libHel
 * Object  : CollisionObject
 * Comments: Was missing from SourceForge!
 *
 *-- History ------------------------------------------------
 *
 * 2013.12.27:
 * xythobuz - Created as stub, was missing
 ================================================================*/


#ifndef GUARD__LIBHEL_MONGOOSE_COLLISIONOBJECT_H_
#define GUARD__LIBHEL_MONGOOSE_COLLISIONOBJECT_H_

#include <hel/Vector3d.h>

class CollisionObject
{
 public:

	////////////////////////////////////////////////////////////
	// Constructors
	////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////
	// Public Accessors
	////////////////////////////////////////////////////////////

    bool intersectPoint(Vector3d p);

	////////////////////////////////////////////////////////////
	// Public Mutators
	////////////////////////////////////////////////////////////

    Vector3d mIntersection;


 private:

	////////////////////////////////////////////////////////////
	// Private Accessors
	////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////
	// Private Mutators
	////////////////////////////////////////////////////////////


	/* */
};

class HeightCollisionObject : public CollisionObject {
public:
    HeightCollisionObject(int a, int b);
};

#endif
