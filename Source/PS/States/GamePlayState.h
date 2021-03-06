/////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Name: MainMenuState
// Purpose: This is the Main Menu State
// Original Author: Ethan Pendergraft
// Creation Date: 5/12/2012
// Last Modification By:
// Last Modification Date:
/////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CGamePlayState_H
#define CGamePlayState_H

#include "IGameState.h"
#include "..//..//HUD/Hud.h"

class CInputManager;
class CAudioManager;
class CGame;

__declspec(align(32))
class CGamePlayState : public IGameState
{
private:
	CGame* m_pGame;
	CInputManager* m_pInput;
	CCamera* m_pCamera;
	CAudioManager* m_pAudio;
	bool m_bOnTop;
	CTimer m_cTimer;
	CHud m_cHUD;
	int m_nPrevLevel;

	// End Game Flag
	bool m_bEndGame;

	bool HasLevelBeenReset;

	// Win Game Flag
	bool m_bWinGame;
	bool m_bWinGameFade;
	float m_fWindGameFadeFactor;
	int m_pWinGameTexture;

	static CGamePlayState* m_pInstance;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: CGamePlayState
	// Purpose: Default Constructor.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	CGamePlayState();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: ~CGamePlayState
	// Purpose: Default Destructor.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	~CGamePlayState();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: CGamePlayState Copy Constructor
	// Purpose: Default copy constructor.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	CGamePlayState( const CGamePlayState& obj );

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: operator =
	// Purpose: Assignment Operator.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	CGamePlayState& operator = ( const CGamePlayState& obj);

public:

	CHud* GetHUD( void ) { return &m_cHUD; }

	//////////////////////////////////////////////////////////////////
	//	Mutators
	//////////////////////////////////////////////////////////////////
	void EndGame( void ) { m_bEndGame = true; }
	void WinGame( void ) { m_bWinGame = true; }
	void WinGameFade( void ) { m_bWinGameFade = true; }
	bool GetWinGameFace( void ) { return m_bWinGameFade; }
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: GetInstance
	// Purpose: Returns the instance of the Main Menu.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static CGamePlayState* GetInstance ();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: DeleteInstance
	// Purpose: Deletes the instance of the Main Menu.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static void DeleteInstance ();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Init
	// Purpose: Initializes the state.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void Init(void);

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Shutdown
	// Purpose: Shuts down the state.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void Shutdown();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Update
	// Purpose: Updates the state.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void Update(float fTime);

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Input
	// Purpose: Gets input to update the state.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	bool Input();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Render
	// Purpose: Render the state.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void Render();
};

#endif // CGamePlayState_H