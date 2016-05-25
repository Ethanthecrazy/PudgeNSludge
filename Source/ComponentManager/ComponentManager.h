#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

//////////////////////////////////////////////////////////////////////////////////////
// Filename:			ComponentManager.h
// Author:				Ethan Pendergraft
// Date:				5/8/12
// Purpose:				To manage components and update them.
//////////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <list>

class IComponent;

__declspec(align(32))
class CComponentManager
{
private:

	// The contained for all of the componets, sorted into lists based on type.
	std::map< unsigned int, std::list< IComponent* > > m_cpActiveComponents;


public:

	bool m_bDunskies;
	CComponentManager() : m_bDunskies(true){}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Update():	.	Update the component system.
	//
	// Returns:			Void                              
	//
	// Mod. Name:       EP
	// Mod. Date:       5/9/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Update( float fDT );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Render():	.	Renders the component system. This function was made so any components that have 
	// particles can be rendered.
	//
	// Returns:			Void                              
	//
	// Mod. Name:       KC
	// Mod. Date:       5/30/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Render();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// AddComponent():	Adds a component to the active component system.
	//
	// Returns:			Void                              
	//
	// Mod. Name:       EP
	// Mod. Date:       5/9/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void AddComponent( IComponent* _pToAdd );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// RemoveComponent():	Removes a component from the active component system. 
	//						Note: This does not clean up any memory.
	//
	// Returns:				Void                              
	//	
	// Mod. Name:			EP
	// Mod. Date:			5/9/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void RemoveComponent( IComponent* _pToRemove );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Clear():			Clears all components from the active system.
	//
	// Returns:			Void                              
	//
	// Mod. Name:       EP
	// Mod. Date:       5/9/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Clear();

};

#endif