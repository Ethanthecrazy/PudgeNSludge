/////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Name: MainMenuState
// Purpose: This is the Main Menu State
// Original Author: Ethan Pendergraft
// Creation Date: 5/12/2012
// Last Modification By:
// Last Modification Date:
/////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CEndGameState_H
#define CEndGameState_H

#include "IGameState.h"
#include "../CGame.h"
#include "../../InputLib/InputManager.h"

__declspec(align(32))
class CEndGameState : public IGameState
{
private:
	CGame* m_pGame;
	CInputManager* m_pInput;

	static CEndGameState* m_pInstance;
	LPDIRECT3DTEXTURE9 m_nEndTextureHandle; 

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: CEndGameState
	// Purpose: Default Constructor.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	CEndGameState();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: ~CEndGameState
	// Purpose: Default Destructor.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	~CEndGameState();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: CEndGameState Copy Constructor
	// Purpose: Default copy constructor.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	CEndGameState( const CEndGameState& obj );

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: operator =
	// Purpose: Assignment Operator.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	CEndGameState& operator = ( const CEndGameState& obj);

public:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: GetInstance
	// Purpose: Returns the instance of the Main Menu.
	// Original Author: Ethan Pendergraft
	// Creation Date: 5/12/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static CEndGameState* GetInstance ();

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

#endif // CEndGameState_H