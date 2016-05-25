//////////////////////////////////////////////////////////////////////////////////////
// Filename: CParticleManager.h
// Author: Kevin Clouden
// Date: 5/14/12
// Purpose: The manager will load in all particles from files
//////////////////////////////////////////////////////////////////////////////////////

#ifndef PARTICLEMANAGER_H_
#define PARTICLEMANAGER_H_
#include <vector>
#include <fstream>
#include <string>
#include "../PS/config.h"
#include "../Utilities/MathLib/vec3.h"
class CEmitter;
class CCamera;
class CEffects;
class TextureManager;

class CParticleManager
{
private:
	LPDIRECT3DVERTEXBUFFER9 particleBuffer;
	LPDIRECT3DVERTEXDECLARATION9 particleDecl;
	LPD3DXEFFECT particleShaderEffect;
	LPDIRECT3DDEVICE9 device;
	std::vector<CEffects*> m_vParticleEffect;
	int indexForActiveparticle;
	CEmitter* m_pEmitter;
	CEffects* m_pEffects;
	char* m_szName;

	int m_nParticleIndex; //Particle Index is only there for changes some particle values 
	int m_nNumEmitters;
	static CParticleManager* m_pInstance;
	TextureManager* m_pTextureManager;
public:
	int GetIndexForActiveparticle() const { return indexForActiveparticle; }
	void SetIndexForActiveparticle(int val) { indexForActiveparticle = val; }
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Constructors: Default constructor, destructor
	// Returns: void
	// Mod. Name: KC
	// Mod. Date: 5/8/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CParticleManager(void);
	~CParticleManager(void);

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: GetInstance
	// Purpose: Returns the instance
	// Original Author: KC
	// Creation Date: 5/12/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static CParticleManager* GetInstance ();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function Name: DeleteInstance
	// Purpose: Deletes the instance
	// Original Author: KC
	// Creation Date: 5/12/2012
	// Last Modification By:
	// Last Modification Date:
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static void DeleteInstance ();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// LoadParticles: Loads the particles from binary files
	// Returns: void
	// Mod. Name: KC
	// Mod. Date: 5/8/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool LoadParticles(std::string szFilename);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Render: Renders the particles
	// Returns: void
	// Mod. Name: KC
	// Mod. Date: 5/8/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Render();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Update: Updates the particles
	// Returns: void
	// Mod. Name: KC
	// Mod. Date: 5/8/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Update(float elapsedTime);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CreateVertexBuffer: Creates a single buffer large enough for all particles in the game
	// Returns: void
	// Mod. Name: KC
	// Mod. Date: 5/8/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void CreateVertexBuffer(LPDIRECT3DDEVICE9 dev);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Accessors: Returns data 
	// Returns: void
	// Mod. Name: KC
	// Mod. Date: 5/8/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//std::vector<CEmitter*> GetParticleEffect() { return m_vParticleEffect; }
	std::vector<CEffects*> GetParticleEffect() { return m_vParticleEffect; }
	LPDIRECT3DVERTEXBUFFER9 GetParticleBuffer() const { return particleBuffer; }
	LPDIRECT3DVERTEXDECLARATION9 GetParticleDecl() const { return particleDecl; }
	LPD3DXEFFECT GetParticleShaderEffect() const { return particleShaderEffect; }
	LPDIRECT3DDEVICE9 GetDevice() const { return device; }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Mutators: Sets data 
	// Returns: void
	// Mod. Name: KC
	// Mod. Date: 5/8/12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetParticleEffect(std::vector<CEffects*> val) { m_vParticleEffect = val; }
	//void SetParticleEffect(std::vector<CEmitter*> val) { m_vParticleEffect = val; }
	void SetParticleBuffer(LPDIRECT3DVERTEXBUFFER9 val) { particleBuffer = val; }
	void SetParticleDecl(LPDIRECT3DVERTEXDECLARATION9 val) { particleDecl = val; }
	void SetParticleShaderEffect(LPD3DXEFFECT val) { particleShaderEffect = val; }
	void SetDevice(LPDIRECT3DDEVICE9 val) { device = val; }


};


#endif