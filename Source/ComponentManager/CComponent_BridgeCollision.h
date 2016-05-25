/////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Name: CComponent_BridgeCollision
//
// Purpose: Handle all collisions for the bridge object
//
// Original Author: Rueben Massey
//
// Creation Date: 6/4/2012
//
// Last Modification By: 
// Last Modification Date: 
/////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CCOMPONENT_BRIDGECOLLISION_H_
#define CCOMPONENT_BRIDGECOLLISION_H_

#include "CComponent_Collision.h"

#define BRIDGE_UNIT 50
#define BRIDGE_LENGTH 244
#define BRIDGE_OFFSET 122

// FORWARD DECLARATIONS
class IBaseObject;
class CComponent_Sound;
class CComponent_Emitter;
class CEffects;
class CComponent_Animation;

__declspec(align(32))
class CComponent_BridgeCollision : public CComponent_Collision
{

private:
	float m_fDropTimer;

	// Pointer to the collision volume
	AABB* m_pCollisionObject;

	// Attribs
	bool m_bIsActivated;
	int m_nChannel;
	bool m_bPlayed;
	int m_nRotationQuadrant;
	bool m_bRotateClockwise;

	// Sound
	CComponent_Sound* m_pSoundComponent;
	// Particles and effects
	CComponent_Emitter* m_pEmitterComponent;
	// Animation
	CComponent_Animation* m_pAnimationComponent;

public:

	/////////////////////////////
	//  Accessors
	/////////////////////////////
	bool GetIsActivated() const { return m_bIsActivated; }
	int GetChannel() const { return m_nChannel; }
	int GetRotationQuadrant() const { return m_nRotationQuadrant; }
	bool GetRotateClockwise() const { return m_bRotateClockwise; }

	/////////////////////////////
	//  Mutators
	/////////////////////////////
	void SetIsActivated(bool val) { m_bIsActivated = val; }
	void SetChannel(int val) { m_nChannel = val; }
	void SetRotationQuadrant(int val) { m_nRotationQuadrant = val; }
	void SetRotateClockwise(bool val) { m_bRotateClockwise = val; }

	CComponent_BridgeCollision();
	~CComponent_BridgeCollision();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Initialize()
	// Purpose: Initialize all data members
	// Original Author: Rueben Massey
	// Creation Date: 6/4/2012
	// Last Modification By: 
	// Last Modification Date: 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool Initialize( );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Update()
	// Purpose: Update all data members
	// Original Author: Rueben Massey
	// Creation Date: 6/4/2012
	// Last Modification By: 
	// Last Modification Date: 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Update( float fDT );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Shutdown()
	// Purpose: clean up memory
	// Original Author: Rueben Massey
	// Creation Date: 6/4/2012
	// Last Modification By: 
	// Last Modification Date: 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Shutdown(void);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: DropBridgeAABB()
	// Purpose: Remove the AABB so the player can pass
	// Original Author: Rueben Massey
	// Creation Date: 6/9/2012
	// Last Modification By: 
	// Last Modification Date: 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void DropBridgeAABB( float fDT );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: CheckCollisions()
	// Purpose: Check for collision	and react appropriately
	// Original Author: Rueben Massey
	// Creation Date: 6/13/2012
	// Last Modification By: 
	// Last Modification Date: 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void CheckCollisions( float fDT );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: CheckDynamicCollisions()
	// Purpose: Check collisions with all dynamic objects
	// Original Author: Rueben Massey
	// Creation Date: 6/11/2012
	// Last Modification By: 
	// Last Modification Date: 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void CheckDynamicCollisions( CComponent_Collision* pCurCollision, CCollisionVolume* pCurVolume, float fDT );
};
#endif //CCOMPONENT_BRIDGECOLLISION_H_