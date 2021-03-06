/////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Name: CComponent_PlugCollision
//
// Purpose: Handle all collisions for the plug object
//
// Original Author: Rueben Massey
//
// Creation Date: 6/4/2012
//
// Last Modification By: 
// Last Modification Date: 
/////////////////////////////////////////////////////////////////////////////////////////////////////
#include "CComponent_PlugCollision.h"
#include "../ObjectLib/ObjectManager/CObjectManager.h"
#include "../Utilities/KdTree/KdTree.h"

CComponent_PlugCollision::CComponent_PlugCollision()
{
	m_bPlugged = false;
	m_bPlayed = false;
	m_fPlayDelay = 0.0f;
	m_tPrevPos = vec3f(0.0f, 0.0f, 0.0f);
	m_pSoundComponent = nullptr;
	this->CleanRemoveVelocity();
}

CComponent_PlugCollision::~CComponent_PlugCollision()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: Initialize()
// Purpose: Initialize all data members
// Original Author: Rueben Massey
// Creation Date: 6/4/2012
// Last Modification By: 
// Last Modification Date: 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CComponent_PlugCollision::Initialize( )
{
	CComponent_Collision::Initialize();
	m_bPlugged = false;
	m_bPlayed = false;
	m_fPlayDelay = 0.0f;
	m_tPrevPos = vec3f(0.0f, 0.0f, 0.0f);
	m_fTimeLeftToIgnorePlayer = 0.0f;
	this->CleanRemoveVelocity();

	m_pSoundComponent = (CComponent_Sound*)(m_pParent->GetComponent(ECOMP_SOUND));
	
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: Update()
// Purpose: Update all data members
// Original Author: Rueben Massey
// Creation Date: 6/4/2012
// Last Modification By: 
// Last Modification Date: 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CComponent_PlugCollision::Update( float fDT )
{
	if( m_fTimeLeftToIgnorePlayer > 0.0f )
	{
		m_fTimeLeftToIgnorePlayer -= fDT;
	}

	if( m_bPlugged )
	{
		return;
	}
	
	if( m_pParent )
	{
		if (m_pParent->GetCollidableObject()->GetVolumeType () != VMT_BOX)
		{
			return;
		}
	}

	m_bCollidingGroundLast = m_bCollidingGround;
	m_bCollidingGround = false;

	m_fPlayDelay += fDT;
	vec3f travelled = m_tPrevPos - m_pParent->GetWorldPos();
	float dist = travelled.magnitude();
	// Josh Morgan
	// Sound
	if(m_bPlayed && m_fPlayDelay > 0.1f && dist > 3.0)
	{
		m_bPlayed = false;
		m_fPlayDelay = 0.0f;
	}

	// Ethan Pendergraft
	// Physics
	///////////////////////////////////////////////////////////////////////
	vec3f fAverage;

	if( m_pPhysicsBox )
	{
		fAverage = m_pPhysicsBox->GetCentroid();
	}

	m_pParent->SetLocalPos( &fAverage );

	vec3f NewCenter = m_pParent->GetWorldPos();
	m_tPrevPos = m_pParent->GetWorldPos();
	/////////////////////////////////////////////////////////////////////////

	// create a return vector to hold all the objects the kd tree returns
	std::vector <CSceneObject*> NearestObjects;
	// create a unsigned int that will tell the kd tree what you want put in the return vector
	// this uses bit wise operations so you can have more then one object returned
	// use the return flags enum from the kd tree so you know what you can get back
	int ReturnParams = 0;
	int ReturnBody = 0;
	int ReturnObjects =  (1<<OBJ_CRATE) | (1<<OBJ_CORK) | (1<<OBJ_PLUG) | (1<<OBJ_WORLD_COLLISION);

	// call the kd tree and get the near objects
	CKdTree::GetNearObjects (m_pParent, PSFLAG_BOX, ReturnParams, NearestObjects, ReturnBody, ReturnObjects);

	// loop through all the return objects and check collision with them.
	for( unsigned int objindex = 0; objindex < NearestObjects.size(); ++objindex )
	{
		// get the collision component of the object
		CComponent_Collision* curCollision = (CComponent_Collision*)(((IBaseObject*)NearestObjects[objindex])->GetComponent( ECOMP_COLLISION ));
		IBaseObject* curObj = (IBaseObject*)NearestObjects[objindex];
		// get the collision volume of the object
		CCollisionVolume* curVolume = NearestObjects[objindex]->GetCollidableObject();
		// Safety Check
		if( curVolume )
		{
			vec2f contactpoints[2];
			unsigned int numPoints = 0;
			vec2f Direction;
			vec2f Contact;

			// Collision checks against
			// our moveable objects
			if( BT_DYNAMIC == curVolume->GetBodyType() )
			{
				CheckDynamicCollisions( curCollision, curVolume, fDT );
			}
			else if( BT_STATIC == curVolume->GetBodyType() )
			{
				CheckStaticCollisions( curCollision, curVolume, fDT );
			}
		}
	}

	// cap the objects z axis position and velocity
	m_fPos.z = 0.0f;
	m_fVel.z = 0.0f;

	m_bPrevInGoo = m_bInGoo;
	m_bInGoo = false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: Shutdown()
// Purpose: clean up memory
// Original Author: Rueben Massey
// Creation Date: 6/4/2012
// Last Modification By: 
// Last Modification Date: 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CComponent_PlugCollision::Shutdown(void)
{
	m_bPlugged = false;
	m_bPlayed = false;
	m_fPlayDelay = 0.0f;
	m_tPrevPos = vec3f(0.0f, 0.0f, 0.0f);
	m_fTimeLeftToIgnorePlayer = 0.0f;
	m_pSoundComponent = nullptr;
	this->CleanRemoveVelocity();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: CheckDynamicCollisions()
// Purpose: Check collisions with all dynamic objects
// Original Author: Ethan Pendergraft
// Creation Date: 6/13/2012
// Last Modification By: 
// Last Modification Date: 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CComponent_PlugCollision::CheckDynamicCollisions( CComponent_Collision* pCurCollision, CCollisionVolume* pCurVolume, float fDT )
{
	Box* BoxCollisionVolume = (Box*)m_pParent->GetCollidableObject();
	vec2f Contact;
	vec2f Direction;
	vec2f contactpoints[4];
	unsigned int numPoints;

	if( pCurCollision && pCurCollision != this )
	{
		// collision checks
		// based on volume type
		switch( pCurVolume->GetVolumeType() )
		{
		case VMT_BOX:
			{
				CComponent_Item* pThisItem = (CComponent_Item*)m_pParent->GetComponent( ECOMP_ITEM );
				if( pThisItem )
				{
					if( pThisItem->GetTarget() )
						return;
				}
				CComponent_Item* pThatItem = (CComponent_Item*)pCurCollision->GetParent()->GetComponent( ECOMP_ITEM );
				if( pThatItem )
				{
					if( pThatItem->GetTarget() )
						return;
				}

				if ( BoxCollisionVolume->BoxToBox( (Box*)pCurVolume, contactpoints, numPoints, Direction ) )
				{
					// Collision reaction with other boxes in the game
					vec3f MoveDirection = vec3f( Direction.x, Direction.y, 0.0f );
					vec3f fCross;
					cross_product( fCross, MoveDirection, vec3f( 0.0f, 0.0f, 1.0f ) );
					float3 fProj = prjPoint2Line( m_pPhysicsBox->m_pPoints[0]->m_CurrPos, m_pPhysicsBox->m_pPoints[0]->m_PrevPos, m_pPhysicsBox->m_pPoints[0]->m_PrevPos + fCross );
					float3 fPrevPush = fProj - m_pPhysicsBox->m_pPoints[0]->m_PrevPos;
					fPrevPush *= -0.1f;

					CleanForce( Direction * 0.1f );
					CleanOffset( Direction * 0.5f );
					Direction.negate();
					pCurCollision->CleanOffset( Direction * 0.5f );
					pCurCollision->CleanForce( Direction * 0.1f );

					vec3f NormalizedDirection = vec3f (Direction.x, Direction.y, 0.0f).normalize();
					float fDotProductUp = dot_product( NormalizedDirection, vec3f( 0.0f, 1.0f, 0.0f ) );
					if( fDotProductUp > 0.5f )
					{
						m_bCollidingGround = true;
					}
					if( fDotProductUp < -0.5f )
					{
						pCurCollision->SetCollidingGroundAlone( true );
					}
				}
				break;
			}
		}
		if( m_pPhysicsBox )
		{
			BoxCollisionVolume->SetWorld( m_pPhysicsBox->GetCentroid() );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: CheckStaticCollisions()
// Purpose: Check collisions with all static objects
// Original Author: Ethan Pendergraft
// Creation Date: 6/13/2012
// Last Modification By: 
// Last Modification Date: 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CComponent_PlugCollision::CheckStaticCollisions( CComponent_Collision* pCurCollision, CCollisionVolume* pCurVolume, float fDT )
{
	Box* BoxCollisionVolume = (Box*)m_pParent->GetCollidableObject();
	vec2f Contact;
	vec2f Direction;

	switch( pCurVolume->GetVolumeType() )
	{

	case VMT_AABB:
		{
			// handle crate collision
			// with world AABB
			if ( BoxCollisionVolume->BoxToAABBWorld( *(AABB*)pCurVolume, Contact, Direction ) )
			{
				// Create an offset vector.
				vec3f MoveDirection = vec3f (Direction.x, Direction.y, 0.0f);
				//Save the last offset for use elsewhere.
				m_fLastOffset = vec3f( Direction.x, Direction.y, 0.0f );

				////////// FRICTION
				vec3f fCross;
				cross_product( fCross, MoveDirection, vec3f( 0.0f, 0.0f, 1.0f ) );
				float3 fProj = prjPoint2Line( m_pPhysicsBox->m_pPoints[0]->m_CurrPos, m_pPhysicsBox->m_pPoints[0]->m_PrevPos, m_pPhysicsBox->m_pPoints[0]->m_PrevPos + fCross );
				float3 fPrevPush = fProj - m_pPhysicsBox->m_pPoints[0]->m_PrevPos;
				fPrevPush *= -0.1f;
				//////////

				//for (unsigned int physicIndex = 0; physicIndex < 3; physicIndex++)
				//{
				//	// Update its position to reflect the changes.
				//	m_pPhysicsBox->m_pPoints[physicIndex]->m_CurrPos += MoveDirection;
				//	// Apply friction to the objects previous position.
				//	m_pPhysicsBox->m_pPoints[physicIndex]->m_PrevPos += fPrevPush;
				//}

				vec3f NormalizedDirection = vec3f (Direction.x, Direction.y, 0.0f).normalize();
				float fDotProductUp = dot_product( NormalizedDirection, vec3f( 0.0f, 1.0f, 0.0f ) );
				float fDotProductSide = dot_product( NormalizedDirection, vec3f( 1.0f, 0.0f, 0.0f ) );
				if( fDotProductUp > 0.5f )
				{
					m_bCollidingGround = true;
				}
				if( abs( fDotProductSide ) > 0.5f )
				{
					fPrevPush = vec3f( 0.0f, 0.0f, 0.0f );
				}

				CleanOffset( vec2f( MoveDirection.x, MoveDirection.y ) );
				CleanForce( vec2f( fPrevPush.x, fPrevPush.y ) + vec2f( MoveDirection.x, MoveDirection.y ) * 0.1f );

				if( false == m_bCollidingGroundLast )
					CParticleManager::GetInstance()->CreateEffectOneShot( "ImpactSmoke", GetParent()->GetWorldPos() - NormalizedDirection * 40.0f , NormalizedDirection );


			}
			break;
		}
	default:
		break;
	}
}
