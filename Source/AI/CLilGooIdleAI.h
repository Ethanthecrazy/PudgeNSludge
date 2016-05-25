////////////////////////////////////////////
// CLilGooIdleAI.h
// Author: Josh Morgan
// Date: 8/9/12
// Purpose: This is to handle the idle state of the
//			little goo.
////////////////////////////////////////////
#ifndef CLILGOOIDLEAI_H_
#define CLILGOOIDLEAI_H_

#include "IBaseAI.h"
#include "../Utilities/CollisionLib/CollisionShapes.h"
#include "../ComponentManager/CComponent_Sound.h"
#include "../ComponentManager/CComponent_Item.h"
#include "../ComponentManager/CComponent_Animation.h"

class CLilGooIdleAI : public IBaseAI
{
private:
	float m_fElapsedTime;
	std::vector <CSceneObject*> m_vCurNearObjects;
	CComponent_Animation* m_pAnimComponent;
	CComponent_Item* m_pItemCmp;

public:
	CLilGooIdleAI(IBaseObject* _pParent);
	~CLilGooIdleAI(void);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Init():	This function is a version of the virtual Init in the IBaseAI. The base ai Init() should be called in this.
	//
	// Returns:		bool
	//
	// Mod. Name: Josh Morgan
	// Mod. Date:8/9/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Init(void);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Update():	This function updates the actions that are expected to be observed in this state.
	//
	// Returns:		bool
	//
	// Mod. Name: Josh Morgan
	// Mod. Date:8/9/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Update(float _fDT);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SimulateMoveRight():	This function simulates the future movements of the enemy to see if the moves are safe to make.
	//
	// Returns:		bool
	//
	// Mod. Name: Josh Morgan
	// Mod. Date:8/9/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool SimulateMoveRight(void);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SimulateMoveLeft():	This function simulates the future movements of the enemy to see if the moves are safe to make.
	//
	// Returns:		bool
	//
	// Mod. Name: Josh Morgan
	// Mod. Date:8/9/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool SimulateMoveLeft(void);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Shutdown(): This will clean up any memory that has been created, and set all the pointers back to null.
	//
	// Returns:		bool
	//
	// Mod. Name: Josh Morgan
	// Mod. Date:8/9/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Shutdown(void);
};

#endif //CLILGOOIDLEAI_H_