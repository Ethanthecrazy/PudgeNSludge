#ifndef CCOMPONENT_SLIME_MONSTER_COLLISION_H
#define CCOMPONENT_SLIME_MONSTER_COLLISION_H

#include "CComponent_Collision.h"

class CComponent_Slime_Monster_AI;
class CComponent_Sound;

class CComponent_SlimeMonsterCollision : public CComponent_Collision
{
private:
	float m_fElapsedTime;
	CComponent_Slime_Monster_AI* m_aiSlime;
	CComponent_Sound* m_pSoundCmp;
	bool m_bJump;

private:
	void StaticCollision ( IBaseObject* Collider, IBaseObject* Collide );
	void DynamicCollision ( IBaseObject* Collider, IBaseObject* Collide );
	void PushOut ( CComponent_Collision* _pObjectCollision, vec2f Direction );

public:
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CComponent_SlimeMonsterCollision():	Default constructor
	//
	// Returns:		Void
	//
	// Mod. Name: JF
	// Mod. Date: 6/2/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CComponent_SlimeMonsterCollision();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CComponent_SlimeMonsterCollision():	Default Destructor
	//
	// Returns:		Void
	//
	// Mod. Name: JF
	// Mod. Date: 6/2/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	~CComponent_SlimeMonsterCollision(void);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Initialize():	intis the little goo collision informtion
	//
	// Returns:		bool
	//
	// Mod. Name: JF
	// Mod. Date: 6/2/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool Initialize();

	/////////////////////////////
	//  Accessors
	/////////////////////////////
	bool GetJumping(void) { return m_bJump; }
	
	/////////////////////////////
	//  Mutators
	/////////////////////////////
	void SetJump(bool _bJumping) { m_bJump = _bJumping; }


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Update():	Updates the collison component, incrementing its physics and detecting collision with other objects.
	//
	// Returns:		Void
	//
	// Mod. Name:   Josh Fields
	// Mod. Date:   5/16/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Update( float fDT );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Shutdown():	shutdowns the little goo collision information
	//
	// Returns:		Void
	//
	// Mod. Name: JF
	// Mod. Date: 6/2/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Shutdown(void);

};
#endif