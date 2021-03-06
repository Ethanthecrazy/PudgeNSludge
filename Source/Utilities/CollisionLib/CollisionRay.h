//////////////////////////////////////////////////////////////////////////////////////
// Filename:	CollisionRay.h
// Author:		Josh Fields
// Date:		5/24/12
// Purpose:		This class holds on to the information for a Ray
//////////////////////////////////////////////////////////////////////////////////////
#ifndef CollisionRay_H
#define CollisionRay_H

#include "CollisionVolume.h"
#include "CollisionPoint.h"

class CCollisionPlane;
class CCollisionSphere;

class CCollisionRay : public CCollisionVolume
{
private:
	CCollisionPoint m_cptStart;
	CCollisionPoint m_cptDirection;

public:
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CCollisionRay():	Default Constructor
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CCollisionRay ();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CCollisionRay():	Default Destructor
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	~CCollisionRay ();

	/////////////////////////////
	//  Accessors
	/////////////////////////////
	CCollisionPoint GetStartPoint () { return m_cptStart; }
	CCollisionPoint GetDirection () { return m_cptDirection; }
	
	/////////////////////////////
	//  Mutators
	/////////////////////////////
	void SetStartPoint ( CCollisionPoint _cptStart ) { m_cptStart = _cptStart; }
	void SetDirection ( CCollisionPoint _cptDirection ) { m_cptDirection = _cptDirection; }


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ClosestPointOnRay():	Takes in a vec3f (vPoint) and an output vec3f (ptA). This will find the closest point on the
	//						ray using the point passed in and save the point on the ray in the output pramater.
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void ClosestPointOnRay( vec3f vpointa, vec3f& pta );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// RayToPlane():	Takes in a Plane (plA) and an output vec3f (ptA). This will find the closest point on the plane
	//					using the ray and save the point in the output pramater.
	//
	// Returns:		bool
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool RayToPlane ( CCollisionPlane pla, vec3f& pta);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// RayToSphere():	Takes in a Sphere (spA) and an output vec3f (ptA). This function will find the closest point on the
	//					sphere and put the point on the sphere in the output pramater.
	//
	// Returns:		bool
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool RayToSphere ( CCollisionSphere spa, vec3f& pta);
};
#endif