/////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Name: CComponent_DoorCollision
//
// Purpose: Handle all collisions for the bridge object
//
// Original Author: Rueben Massey
//
// Creation Date: 6/15/2012
//
// Last Modification By: 
// Last Modification Date: 
/////////////////////////////////////////////////////////////////////////////////////////////////////
#include "CComponent_DoorCollision.h"
#include "Component_Emitter.h"
#include "CComponent_Animation.h"
#include "../ObjectLib/ObjectManager/CObjectManager.h"
#include "../EffectsLib/ParticleManager.h"
#include "../EffectsLib/Emitter.h"
#include "../EffectsLib/Effects.h"
#include "../Utilities/KdTree/KdTree.h"
#include "../AnimationLib/AnimationIncludes.h"

CComponent_DoorCollision::CComponent_DoorCollision()
{
	m_pSoundComponent = nullptr;
	m_pCollisionObject = nullptr;
	m_pEffects = nullptr;
	m_pEmitterComponent = nullptr;
	m_pCollisionObject = nullptr;
	m_pAnimationComponent = nullptr;
	this->CleanRemoveVelocity();
}

CComponent_DoorCollision::~CComponent_DoorCollision()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: Initialize()
// Purpose: Initialize all data members
// Original Author: Rueben Massey
// Creation Date: 6/15/2012
// Last Modification By: 
// Last Modification Date: 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CComponent_DoorCollision::Initialize( )
{
	CComponent_Collision::Initialize();
	m_pSoundComponent = nullptr;
	m_pCollisionObject = nullptr;
	m_pEffects = nullptr;
	m_pEmitterComponent = nullptr;
	m_pCollisionObject = nullptr;
	m_bIsOpen = false;
	this->CleanRemoveVelocity();

	// Create the AABB to trigger the door to open
	m_DoorOpenAABB.SetMaxPoint( vec2f( 400.0f, 122.0f ) );
	m_DoorOpenAABB.SetMinPoint( vec2f( -400.0f, -122.0f ) );
	m_DoorOpenAABB.SetBodyType( BT_DYNAMIC );
	m_DoorOpenAABB.SetVolumeType( VMT_AABB );

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: Update()
// Purpose: Update all data members
// Original Author: Rueben Massey
// Creation Date: 6/15/2012
// Last Modification By: RCM
// Last Modification Date: 6/9
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CComponent_DoorCollision::Update( float fDT )
{
	D3DXMATRIX mat;

	//Parent
	mat._41 = ((AABB*)m_pParent->GetCollidableObject())->GetMax2DTransformed().x;
	mat._42 = ((AABB*)m_pParent->GetCollidableObject())->GetMax2DTransformed().y;
	mat._43 = -600.0f;

	DebugShapes::RenderSphere (mat);

	mat._41 = ((AABB*)m_pParent->GetCollidableObject())->GetMin2DTransformed().x;
	mat._42 = ((AABB*)m_pParent->GetCollidableObject())->GetMin2DTransformed().y;
	mat._43 = -600.0f;

	DebugShapes::RenderSphere (mat);

	mat._41 = ((AABB*)m_pParent->GetCollidableObject())->GetMin2DTransformed().x;
	mat._42 = ((AABB*)m_pParent->GetCollidableObject())->GetMax2DTransformed().y;
	mat._43 = -600.0f;

	DebugShapes::RenderSphere (mat);
	
	mat._41 = ((AABB*)m_pParent->GetCollidableObject())->GetMax2DTransformed().x;
	mat._42 = ((AABB*)m_pParent->GetCollidableObject())->GetMin2DTransformed().y;
	mat._43 = -600.0f;

	DebugShapes::RenderSphere (mat);

	mat._41 = m_DoorOpenAABB.GetMax2DTransformed().x;
	mat._42 = m_DoorOpenAABB.GetMax2DTransformed().y;
	mat._43 = -600.0f;

	DebugShapes::RenderSphere (mat);

	mat._41 = m_DoorOpenAABB.GetMin2DTransformed().x;
	mat._42 = m_DoorOpenAABB.GetMin2DTransformed().y;
	mat._43 = -600.0f;

	DebugShapes::RenderSphere (mat);

	mat._41 = m_DoorOpenAABB.GetMin2DTransformed().x;
	mat._42 = m_DoorOpenAABB.GetMax2DTransformed().y;
	mat._43 = -600.0f;

	DebugShapes::RenderSphere (mat);

	mat._41 = m_DoorOpenAABB.GetMax2DTransformed().x;
	mat._42 = m_DoorOpenAABB.GetMin2DTransformed().y;
	mat._43 = -600.0f;

	DebugShapes::RenderSphere (mat);

	if( m_pParent )
	{
		if(!m_pSoundComponent)
		{
			m_pSoundComponent = (CComponent_Sound*)(m_pParent->GetComponent(ECOMP_SOUND));
		}

		if(!m_pEmitterComponent)
		{
			m_pEmitterComponent = (CComponent_Emitter*)m_pParent->GetComponent( ECOMP_EMITTER );
			D3DXVECTOR3 pos = *(D3DXVECTOR3*)(&(m_pParent->GetWorldPos()));
			
			// TODO
			// Set up Particles for the bridge

		}
		// Set the collision object 
		// to the parent's collision object 
		if( !m_pCollisionObject )
		{
			m_pCollisionObject = (AABB*)m_pParent->GetCollidableObject();
		}
		if( !m_pAnimationComponent )
		{
			m_pAnimationComponent = (CComponent_Animation*)m_pParent->GetComponent( ECOMP_ANIMATION );
		}

		((AABB*)m_pParent->GetCollidableObject())->SetMaxPoint( vec2f( 20.0f, 122.0f ) );
		((AABB*)m_pParent->GetCollidableObject())->SetMinPoint( vec2f( -20.0f, -122.0f ) );
	}

	vec3f NewCenter = m_pParent->GetWorldMat()->axis_pos;
	((AABB*)m_pParent->GetCollidableObject())->SetWorldPoint( NewCenter );
	m_DoorOpenAABB.SetWorldPoint( NewCenter );

	if( !m_bIsOpen )
	{
		CheckOpenCollision( fDT );
		CheckCollisions( fDT );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: Shutdown()
// Purpose: clean up memory
// Original Author: Rueben Massey
// Creation Date: 6/15/2012
// Last Modification By: 
// Last Modification Date: 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CComponent_DoorCollision::Shutdown(void)
{
	m_pSoundComponent = nullptr;
	m_pCollisionObject = nullptr;
	m_pEffects = nullptr;
	m_pEmitterComponent = nullptr;
	m_pCollisionObject = nullptr;
	m_bIsOpen = false;
	this->CleanRemoveVelocity();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: CheckCollisions()
// Purpose: Check for collision	and react appropriately
// Original Author: Rueben Massey
// Creation Date: 6/13/2012
// Last Modification By: 
// Last Modification Date: 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CComponent_DoorCollision::CheckCollisions( float fDT )
{
	// create a return vector to hold all the objects the kd tree returns
	std::vector <CSceneObject*> NearestObjects;
	// create a unsigned int that will tell the kd tree what you want put in the return vector
	// this uses bit wise operations so you can have more then one object returned
	// use the return flags enum from the kd tree so you know what you can get back
	int ReturnParams = 0;
	int ReturnBody = 0;
	int ReturnObjects = (1<<OBJ_CRATE) | (1<<OBJ_CORK) | (1<<OBJ_PLUG) | (1<<OBJ_PLAYER);

	// call the kd tree and get the near objects
	CKdTree::GetNearObjects ( m_pParent, PSFLAG_AABB, ReturnParams, NearestObjects, ReturnBody, ReturnObjects );

	for( unsigned int objindex = 0; objindex < NearestObjects.size(); ++objindex )
	{
		// get the collision component of the object
		CComponent_Collision* curCollision = (CComponent_Collision*)(((IBaseObject*)NearestObjects[objindex])->GetComponent( ECOMP_COLLISION ));
		// get the collision volume of the object
		CCollisionVolume* curVolume = NearestObjects[objindex]->GetCollidableObject();
		// Safety Check
		if( curVolume && curCollision && curCollision != this )
		{
			// Check if the body type is dynamic
			// meaning it's a moving object in the game
			if( BT_DYNAMIC == curVolume->GetBodyType() )
			{
				CheckDynamicCollisions( curCollision, curVolume, fDT );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: CheckOpenCollision()
// Purpose: Check for collision	with the player and open the door
// Original Author: Rueben Massey
// Creation Date: 6/15/2012
// Last Modification By: 
// Last Modification Date: 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CComponent_DoorCollision::CheckOpenCollision( float fDT )
{
	// Variables to catch returns
	vec2f Direction;

	// create a return vector to hold all the objects the kd tree returns
	std::vector <CSceneObject*> NearestObjects;
	// create a unsigned int that will tell the kd tree what you want put in the return vector
	// this uses bit wise operations so you can have more then one object returned
	// use the return flags enum from the kd tree so you know what you can get back
	int ReturnParams = 0;
	int ReturnBody = 0;
	int ReturnObjects = (1<<OBJ_PLAYER);

	CSceneObject _door;
	_door.SetCollidableObject( &m_DoorOpenAABB );

	// call the kd tree and get the near objects
	CKdTree::GetNearObjects ( &_door, PSFLAG_AABB, ReturnParams, NearestObjects, ReturnBody, ReturnObjects );

	for( unsigned int objindex = 0; objindex < NearestObjects.size(); ++objindex )
	{
		// get the collision component of the object
		CComponent_Collision* curCollision = (CComponent_Collision*)(((IBaseObject*)NearestObjects[objindex])->GetComponent( ECOMP_COLLISION ));
		// get the collision volume of the object
		CCollisionVolume* curVolume = NearestObjects[objindex]->GetCollidableObject();
		// Safety Check
		if( curVolume && curCollision && curCollision != this )
		{
			if( ((AABB*)curVolume)->AABBToAABB( m_DoorOpenAABB, Direction ) )
			{
				//Change animation state
#if _ANIMATIONS
				m_pAnimationComponent->GetAnimStateMachine()->ChangeState( DoorOpenState::GetState() );
#endif

				// Kill the AABB on the door
				m_bIsOpen = true;
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: CheckDynamicCollisions()
// Purpose: Check collisions with all dynamic objects
// Original Author: Rueben Massey
// Creation Date: 6/11/2012
// Last Modification By: 
// Last Modification Date: 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CComponent_DoorCollision::CheckDynamicCollisions( CComponent_Collision* pCurCollision, CCollisionVolume* pCurVolume, float fDT )
{
	// Variables to catch returns
	vec2f Direction;
	vec2f CP;

	// Check collisions
	// based on the current objects collision volume
	switch( pCurVolume->GetVolumeType() )
	{
	case VMT_AABB:
		{
			// Use the current volume to check against this collision volume
			// This returns the proper direction to push out the current object
			if( ((AABB*)pCurVolume)->AABBToAABB( *m_pCollisionObject, Direction ) )
			{
				// Apply push-out
				pCurCollision->CleanOffset( Direction );
				pCurCollision->CleanForce( Direction * 0.5f );
				// update the AABB
				((AABB*)pCurCollision->GetParent()->GetCollidableObject())->SetWorldPoint( pCurCollision->GetPos2DClean() );
				// set the player to grounded
				// if he is on top of us
				if( OBJ_PLAYER == pCurCollision->GetParent()->GetType() )
				{
					if( dot_product( Direction, vec2f( 0.0f, 1.0f ) ) > 0.5f )
					{
						((CComponent_PlayerCollision*)pCurCollision)->SetCollidingGroundAlone( true );
					}
				}
			}
			break;
		}
	case VMT_BOX:
		{
			// Use the current volume to check against this collision volume
			// This returns the proper direction to push out the current object
			if( ((Box*)pCurVolume)->BoxToAABB( *m_pCollisionObject, CP,Direction ) )
			{
				// Apply push-out
				pCurCollision->CleanOffset( Direction );
				pCurCollision->CleanForce( Direction * 0.5f );
			}
			break;
		}
	default:
		break;
	};
}