//////////////////////////////////////////////////////////////////////////////////////
// Filename:	CollisionSphere.h
// Author:		Josh Fields
// Date:		5/24/12
// Purpose:		This class holds on to the information for a Sphere
//////////////////////////////////////////////////////////////////////////////////////
#ifndef CollisionSphere_H
#define CollisionSphere_H

#include "CollisionVolume.h"
#include "CollisionPoint.h"
//#include "CollisionCapsule.h"
//#include "CollisionAABB.h"
//#include "CollisionBox.h"

class CCollisionCapsule;
class CCollisionAABB;
class CCollisionBox;

class CCollisionSphere : public CCollisionVolume
{
protected:
	CCollisionPoint m_cptCenter;
	float m_fRadius;

public:
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CCollisionSphere():	Default Constructor
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CCollisionSphere ();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CCollisionSphere():	Copy Constructor. Thakes in a const reference to a Sphere and copies all the data over.
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CCollisionSphere ( const CCollisionSphere& _csSphere );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ~CCollisionSphere():	Default Destructor
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	~CCollisionSphere ();

	/////////////////////////////
	//  Accessors
	/////////////////////////////
	vec2f GetCenter2D () { return m_cptCenter.Get2DCentorid(); }
	vec3f GetCenter3D () { return m_cptCenter.Get3DCentorid(); }

	float GetRadius () { return m_fRadius; }

	/////////////////////////////
	//  Mutators
	/////////////////////////////
	void SetCenter ( vec2f _v2Center ) { m_cptCenter.Set2DCentorid (_v2Center); }
	void SetCenter ( vec3f _v3Center ) { m_cptCenter.Set3DCentorid (_v3Center); }

	void SetRadius ( float _fRadius ) { m_fRadius = _fRadius; }


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SphereToSphere():	Takes in a Sphere (spB). Checks collision between the passed in sphere and the calling sphere.
	//						Returns true if both spheres are over lapping.
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool SphereToSphere ( CCollisionSphere spB);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SphereToSphere():	Takes in a Sphere (spB) and an output vec3f (v3NewPosB). Checks collision between the passed in 
	//						sphere and the calling sphere. Returns true if both spheres are over lapping and puts the new 
	//						position for spB in the output vec3f.
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool SphereToSphere (CCollisionSphere spB, vec3f& v3NewPosB);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SphereToCapsule():	Takes in a Capsule (cpA) and an output vec3f (v3NewPos). Checks collision between the passed in 
	//						capsule and the calling sphere. Returns true if they are over lapping and puts the new 
	//						position for cpA in the output vec3f.
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool SphereToCapsule ( CCollisionCapsule cpA, vec3f& v3NewPos);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SphereToAABB():	Takes in a AABB (aabb) and an output vec2f (v3NewPos). Checks collision between the passed in 
	//					aabb and the calling sphere. Returns true if they are over lapping and puts the new 
	//					position for the aabb in the output vec2f.
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool SphereToAABB (CCollisionAABB aabb, vec2f& v3NewPos);

	bool SphereToAABB (CCollisionAABB aabb, vec2f& pushout, vec2f& CP);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SphereToBox():	Takes in a Box (box) and an output vec2f (v3NewPos). Checks collision between the passed in 
	//					box and the calling sphere. Returns true if they are over lapping and puts the new 
	//					position for the box in the output vec2f.
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool SphereToBox (CCollisionBox box, vec2f& v3NewPos);
};
#endif