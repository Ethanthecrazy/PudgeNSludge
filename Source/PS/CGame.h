/////////////////////////////////////////////////////////////////////////////////////////////////////
// File Name: Game.h
// Purpose: This module will be responsible for updating and maintaining the game's state machiene and all associated functionality.
// Original Author: Josh Fields
// Creation Date: 3/30/2012
// Last Modification By:
// Last Modification Date:
/////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _CGAME_H
#define _CGAME_H

#include "config.h"
#include <queue>
#include <string>

#include "../Utilities/Timer/UTimer.h"
#include "../AudioLib/AudioManager.h"
#include "../Camera/Camera.h"
//#include "../EffectsLib/Effects.h"
#include "../HUD/Hud.h"
#include "../InputLib/InputManager.h"
#include "../AudioLib/AudioManager.h"
#include "../RenderEngine/RenderEngine.h"
#include "../Utilities/Utilit.h"
#include "../ComponentManager/ComponentManager.h"
#include "../HUD/CIcon.h"

#ifndef ECS
	#define ECS(s) EnterCriticalSection( &s );
#endif
#ifndef LCS
	#define LCS(s) LeaveCriticalSection( &s );
#endif

//FORWARD DECLARATIONS

class CFont;
class IGameState;
class CSettingsManager;
struct LoadedOptions;


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Name: CGame
// Purpose: This class is responsible for updating and maintaining the game's state machiene and all associated functionality.
// Original Author: Josh Fields
// Creation Date: 3/30/2012
// Last Modification By:	
// Last Modification Date:	
/////////////////////////////////////////////////////////////////////////////////////////////////////
__declspec(align(32))
class CGame
{
private:
	friend class CSplashScreenState;
	friend class CLoadingState;

	CTimer m_Timer;
	static CGame* mainGame;
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	std::vector<IGameState*> m_StateStack;
	//tPoint m_pntScreenSize;
	bool m_bFullScreen;
	bool m_bLoading;
	CCamera cam;
	RenderEngine renderEngine;
	CInputManager m_Input;
	CAudioManager m_Audio;
	bool m_Dontmovecamera;
	bool m_bInputInit;
	bool m_bAudioInit;
	bool m_bDeviceReset;
	int	 m_nReticle;
	float m_nSensitivity; 

	short m_nScreenWidth;
	short m_nScreenHeight;

	// Icon
	CIcon* m_pIcon;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Game
	// Purpose: Default constructor for the game.
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	CGame();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: ~Game
	// Purpose: Default destructor for the game.
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	~CGame();


	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Game(copy)
	// Purpose: Default copy constructor for the game.
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	CGame( const CGame& obj );

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: =
	// Purpose: Assignment Operator for the game.
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	CGame& operator = ( const CGame& obj);

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Update
	// Purpose: To Update all modules in the game through the state machiene
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void Update( float fDeltaTime );

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Render	
	// Purpose: Calls the current GameState's Render
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void Render();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Input
	// Purpose: Retrieves any user input, and passes it to the current GameState
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	bool Input();

public:
	IDirect3DDevice9* GetDevice(void) { return renderEngine.m_pD3Dev; }
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Main
	// Purpose: Maintains the game loop (Checks input, Updates, and Renders)
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	bool Main();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Init
	// Purpose: Initalizes all dependancies in CGame, and begins the main game loop.
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void Init(HWND hWnd, HINSTANCE m_hInstance);

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: GetInstance
	// Purpose: Returns a pointer to the current CGame
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static CGame* GetInstance();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: GetInstance
	// Purpose: Returns a pointer to the current CGame
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static void DeleteInstance();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: Shutdown
	// Purpose: Shuts down all modules in the game
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void Shutdown();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: PushState
	// Purpose: Pushes a new state on to the stacked states
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void PushState(IGameState* pState);

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: PopState
	// Purpose: Pops off the top state on the stacked states
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void PopState();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: ChangeState
	// Purpose: Pops off all states on the stacked states, and pushes on the state passed in
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void ChangeState(IGameState* pState);

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: GetState
	// Purpose: Returns a pointer to the top most state on the state stack
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	IGameState* GetState();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: GetHWND
	// Purpose: Returns a pointer to the state that is on top of the stacked states
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	HWND GetHWND() {return m_hWnd;}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: GetHINSTANCE
	// Purpose: Returns a pointer to the state that is on top of the stacked states
	// Original Author: JoshFields
	// Creation Date: 3/30/2012
	// Last Modification By:	
	// Last Modification Date:	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	HINSTANCE GetHINSTANCE() {return m_hInstance;}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: SetScreenSize
	// Purpose: Sets the size of the screen
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//void SetScreenSize( tPoint pntScreenSize );

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: GetScreenSize
	// Purpose: Returns the size of the Screen
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//tPoint GetScreenSize( ) { return m_pntScreenSize; }

	///////////////////////////////////////////////////////////////////////
	//GetInputManager():	Gets the input manager for other classes to
	//						use, mainly the components
	//
	//Returns:				CInputManager* - a pointer to the input manager
	//
	//Mod. Name:			JM
	//Mod. Date:			5/11/12
	///////////////////////////////////////////////////////////////////////
	CInputManager* GetInputManager(void) { return &m_Input; }

	///////////////////////////////////////////////////////////////////////
	//GetAudioManager():	Gets the audio manager for other classes to
	//						use, mainly the components
	//
	//Returns:				CAudioManager* - a pointer to the audio manager
	//
	//Mod. Name:			JM
	//Mod. Date:			5/17/12
	///////////////////////////////////////////////////////////////////////
	CAudioManager* GetAudioManager(void) { return &m_Audio; }

	///////////////////////////////////////////////////////////////////////
	//GetCam():				Gets the camera for other classes to
	//						use, mainly the components
	//
	//Returns:				CCamera* - a pointer to the camera
	//
	//Mod. Name:			JM
	//Mod. Date:			5/11/12
	///////////////////////////////////////////////////////////////////////
	CCamera* GetCamera(void) { return &cam; }

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: GetScreenSize
	// Purpose: Sets if we are FullScreen
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetFullScreen( bool FullScreen );

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: GetScreenSize
	// Purpose: Returns if we are in FullScreen
	// Original Author: Josh Fields
	// Creation Date: 3/30/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	bool GetFullScreen( ) { return m_bFullScreen; }

	bool GetDontMoveCamera(void) { return m_Dontmovecamera; }

	RenderEngine* GetRenderEngine(void) { return &renderEngine; }

	void MoveCamera(float fDT);

	void SwapLevels(char* szLevelName);

	void SetLoading(bool _loading) { m_bLoading = _loading; }
	bool GetLoading(void) { return m_bLoading; }

	LoadedOptions LoadAndSetOptions(void);
	void SaveOptions(void);

	CTimer& GetTimer () { return m_Timer; }
	void SetReticleTexture (int _nTextureId) {m_nReticle = _nTextureId;}

	int GetScreenWidth(void) { return (int)m_nScreenWidth; }
	int GetScreenHeight(void){ return (int)m_nScreenHeight;}

	void SetScreenWidth( int _screenWidth ) { m_nScreenWidth = (short)_screenWidth; }
	void SetScreenHeight( int _screenHeight){ m_nScreenHeight= (short)_screenHeight;}
};

#endif 