#include "AnimationIncludes.h"

LandIdleEffectState::~LandIdleEffectState(void)
{
}

// Access the state to set it in the state machine for each component.
LandIdleEffectState* LandIdleEffectState::GetState(void)
{
	static LandIdleEffectState state;
	return &state;
}

// This will set all variables needed for this animation.
void LandIdleEffectState::Enter( CComponent_Animation* pComponent )
{
	pComponent->GetInterpolator().SetAnimation( AnimationManager::GetInstance()->GetAnimation("JumpSteamStartMesh_JumpIdle") );
	pComponent->SetBindPose( const_cast<Animation*>(pComponent->GetInterpolator().GetAnimation())->GetBindPose() );

	m_fTimeInState = 0.0f;

		pComponent->GetInterpolator().SetTime( 0.0f );


}

// The actual processing of Animation KeyFrames.
void LandIdleEffectState::Execute( CComponent_Animation* pComponent, float fTime )
{
	m_fTimeInState += fTime;
	// Update the time of the Interpolator.
	pComponent->GetInterpolator().AddTime( fTime );

	// Determine if object is inside the Frustum otherwise dont process anything no need to skin.
	if( !pComponent->IsObjectInFrustum() )
		return;

	// Process The Animation
	pComponent->GetInterpolator().Process();
	// Resize the Frame to store all of the interpolated frames.
	pComponent->GetAnimationFrames().resize( pComponent->GetInterpolator().GetCurrentBoneFrames().size() );
	for( unsigned int i = 0; i < pComponent->GetAnimationFrames().size(); ++i)
		pComponent->GetAnimationFrames()[i].GetWorldMat() = (*(matrix4f*)&pComponent->GetBindPose()->GetHierarchyList()[i]->m_InverseLocalMatrix) *
		pComponent->GetInterpolator().GetCurrentBoneFrames()[i].GetWorldMat();

	// 	if( pComponent->GetInterpolator().IsAnimationDone() )
	// 	{
	// 		pComponent->GetAnimStateMachine()->ChangeState( PushEffectIdleState::GetState() );
	// 		//	LOG(LOG_INFO, "PushEffectState::Execute()", "Push changed to idle");
	// 	}
}

// Clean up of the Animation.
void LandIdleEffectState::Exit( CComponent_Animation* pComponent )
{

}