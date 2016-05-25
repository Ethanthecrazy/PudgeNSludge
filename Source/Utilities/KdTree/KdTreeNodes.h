//////////////////////////////////////////////////////////////////////////////////////
// Filename:	KdTreeNodes.h
// Author:		Josh Fields
// Date:		5/24/12
// Purpose:		This files holds all the different Nodes that are needed for the Kd Tree
//////////////////////////////////////////////////////////////////////////////////////
#ifndef TREENODES_H
#define TREENODES_H

#include <list>
#include "../CollisionLib/CollisionShapes.h"

#define MAX_OVERLAPPED_LEAVES 10

enum emTreeNodeTypes { TREE_INTERNAL, TREE_LEAF };


class CKdTree;
class CTreeNode;
class CInternalNode;
class CLeafNode;
class CSceneObject;
struct tTraverseData;

typedef unsigned int (*SplitFunc) ( CInternalNode* pNode, tTraverseData* pData);
typedef bool (*LeafFunc) ( CLeafNode* pNode, tTraverseData* pData);
typedef void (*ObjectFunc) ( CSceneObject* pObject, tTraverseData* pData);
typedef void (*ObjectAdd) ( CSceneObject* pObject);

struct tTraverseData
{
	void* m_pVoidData;
	void* m_pVoidReturnFlags;
	void* m_pVoidBodyFlags;
	void* m_pVoidObjectFlags;
	SplitFunc m_SplitFunc;
	LeafFunc m_LeafFunc;
	ObjectFunc m_ObjectFunc;
	ObjectAdd m_AddObjectFunc;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// tTraverseData():	Default Constructor
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tTraverseData () : m_pVoidData (NULL), m_SplitFunc (NULL), m_LeafFunc (NULL), \
						m_ObjectFunc (NULL), m_AddObjectFunc (NULL) {}
};

///////////////////////////////////////////////////////////////////////////////////
// Function Name: 
// Purpose: DO NOT CALL THIS FUNCTION.
// Original Author: Josh Fields
// Creation Date: 2/14/2012
// Last Modification By:	
// Last Modification Date:	
///////////////////////////////////////////////////////////////////////////////////
class CTreeNode
{
private:
	CInternalNode* m_pParent;

public:
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CTreeNode():	Default Constructor
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CTreeNode () : m_pParent (NULL) {}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ~CTreeNode():	virtual Default Destructor
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual ~CTreeNode () {}

	/////////////////////////////
	//  Accessors
	/////////////////////////////
	virtual emTreeNodeTypes GetNodeType () = 0;

	CInternalNode* GetParent () { return m_pParent; }

	/////////////////////////////
	//  Accessors
	/////////////////////////////
	void SetParent ( CInternalNode* pParent ) { m_pParent = pParent; }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Traverse():	Takes in a TraverseData pointer (pData). A virtual Traverse function used to traverse the Tree
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void Traverse ( tTraverseData* pData ) = 0;
};

class CInternalNode : public CTreeNode
{
private:
	size_t m_unAxis;
	float m_fOffset;
	CTreeNode* m_pLeftChild;
	CTreeNode* m_pRightChild;

public:
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Traverse():	virtual Traverse function used to traverse the Tree
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CInternalNode () : m_unAxis (0), m_fOffset (0.0f), m_pLeftChild (NULL), m_pRightChild (NULL) {}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Traverse():	virtual Traverse function used to traverse the Tree
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	~CInternalNode ();

	/////////////////////////////
	//  Accessors
	/////////////////////////////
	emTreeNodeTypes GetNodeType () { return TREE_INTERNAL; }

	size_t GetAxis () { return m_unAxis; }

	float GetPlaneOffset () { return m_fOffset; }

	CTreeNode* GetLeftChild () { return m_pLeftChild; }

	CTreeNode* GetRightChild () { return m_pRightChild; }

	/////////////////////////////
	//  Mutators
	/////////////////////////////
	void SetAxis ( size_t unAxis ) { m_unAxis = unAxis; }

	void SetPlaneOffset ( float fOffset ) { m_fOffset = fOffset; }

	void SetLeftChild ( CTreeNode* pLeft ) { m_pLeftChild = pLeft; }

	void SetRightChild ( CTreeNode* pRight ) { m_pRightChild = pRight; }


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Traverse():	Takes in a TraverseData pointer (pData). This function traverse though the Kd Tree and splits it accordingly
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Traverse ( tTraverseData* pData);
};

class CLeafNode : public CTreeNode
{
private:
	AABB m_abBounds;
	std::list < CSceneObject* > m_lsOverLappingObjects;

public:
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Traverse():	Takes in a TraverseData pointer (pData). This function traverse though the Kd Tree and splits it accordingly
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CLeafNode () {}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Traverse():	Takes in a TraverseData pointer (pData). This function traverse though the Kd Tree and splits it accordingly
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	~CLeafNode () {}

	/////////////////////////////
	//  Accessors
	/////////////////////////////
	emTreeNodeTypes GetNodeType () { return TREE_LEAF; }

	AABB GetBounds () { return m_abBounds; }

	std::list < CSceneObject* >& GetOverLappingObjects () { return m_lsOverLappingObjects; }

	/////////////////////////////
	//  Mutators
	/////////////////////////////
	void SetBounds ( AABB abBounds ) { m_abBounds = abBounds; }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Traverse():	Takes in a TraverseData pointer (pData). This function calls the Kd Trees traverse function passing in
	//				this leaf and the passed in TraverseData.
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Traverse ( tTraverseData* pData );
};

class CSceneObject
{
private:
	CKdTree* m_pOwnerTree;
	CLeafNode* m_pOverLappedLeaves [MAX_OVERLAPPED_LEAVES];
	bool bAlreadyAdded;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// IsSphereContained():	Checks if the Sphere is contained within its over lapping leafs
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool IsSphereContained ( Sphere sphere );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// IsCapsuleContained():	Checks if the Capsule is contained within its over lapping leafs
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool IsCapsuleContained ( Capsule capsule );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// IsAABBContained():	Checks if the AABB is contained within its over lapping leafs.
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool IsAABBContained ( AABB aabb );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// IsBoxContained():	Checks if the Box is contained within its over lapping leafs.
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool IsBoxContained ( Box temp );

protected:
	CCollisionVolume* pCollisionVolume;	

public:
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CSceneObject():	Constructor
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CSceneObject ();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ~CSceneObject():	Destructor
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	~CSceneObject ();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// RemoveFromLeaves():	This function removes the this SceneObject from all its over lapping leafs.
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void RemoveFromLeaves ();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// IsContained():	Checks if the collision volume of this SceneObject is contained within the objects over lapped leafs
	//
	// Returns:		Void
	//
	// Mod. Name:
	// Mod. Date:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool IsContained ();

	/////////////////////////////
	//  Accessors
	/////////////////////////////
	CLeafNode** GetOverLappedLeaves () { return m_pOverLappedLeaves; }

	CCollisionVolume* GetCollidableObject () { return pCollisionVolume; }

	bool GetInReturnVec () { return bAlreadyAdded; }
	
	CKdTree* GetTree () { return m_pOwnerTree; }

	/////////////////////////////
	//  Mutators
	/////////////////////////////
	void SetCollidableObject ( CCollisionVolume* volume );

	void SetInReturnVec (bool bInVec) { bAlreadyAdded = bInVec; }

	void SetTree ( CKdTree* pTree ) { m_pOwnerTree = pTree; }

};
#endif