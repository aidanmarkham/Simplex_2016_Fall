#include "MyOctant.h"

using namespace Simplex;

void Simplex::MyOctant::Display(int depth)
{

	if (depth < depth) {

		pMeshMngr->AddWireCubeToRenderList(glm::translate(pAABB->Center()) * glm::scale(pAABB->Size()), C_YELLOW);

		for (int i = 0; i < childCount; i++) {
			pChildren[i]->Display(depth + 1);
		}
	}

}

void Simplex::MyOctant::GenTree(int depth)
{

	if (depth < depth) {

		childCount = 8;
		for (int i = 0; i < 8; i++) {
			pChildren[i] = new MyOctant(depth, CreateSubdivision(i), pEntityMngr, pMeshMngr);
			pChildren[i]->pParent = this;

			pChildren[i]->MoveEntities();
			if (pChildren[i]->vEntityList.size() > MINIMUENTITIES) {
				pChildren[i]->GenTree(depth + 1);
			}
		}
	}
	else {
		childCount = 0;
		pParent = nullptr;
	}
}

void Simplex::MyOctant::CheckCollision(int depth)
{

	if (depth < depth) {


		if (vEntityList.size() > 0) {
			for (int i = 0; i < vEntityList.size() - 1; i++) {
				for (int j = i + 1; j < vEntityList.size(); j++) {
					vEntityList[i]->IsColliding(vEntityList[j]);
				}
			}
		}


		for (int k = 0; k < childCount; k++) {
			pChildren[k]->CheckCollision(depth + 1);
		}
	}
}

AABB * Simplex::MyOctant::CreateSubdivision(int index)
{

	vector3 min;
	vector3 max;
	vector3 half = pAABB->maximum - pAABB->minimum;
	half.x = half.x / 2;
	half.y = half.y / 2;
	half.z = half.z / 2;

	switch (index)
	{

	case 0:
		min = pAABB->minimum;
		max = vector3(pAABB->minimum.x + half.x,
			pAABB->minimum.y + half.y,
			pAABB->minimum.z + half.z);
		break;



	case 1:
		min = vector3(pAABB->minimum.x + half.x,
			pAABB->minimum.y,
			pAABB->minimum.z);
		max = vector3(pAABB->maximum.x,
			pAABB->minimum.y + half.y,
			pAABB->minimum.z + half.z);
		break;


	case 2:
		min = vector3(pAABB->minimum.x,
			pAABB->minimum.y + half.y,
			pAABB->minimum.z);
		max = vector3(pAABB->minimum.x + half.x,
			pAABB->maximum.y,
			pAABB->minimum.z + half.z);
		break;


	case 3:
		min = vector3(pAABB->minimum.x + half.x,
			pAABB->minimum.y + half.y,
			pAABB->minimum.z);
		max = vector3(pAABB->maximum.x,
			pAABB->maximum.y,
			pAABB->minimum.z + half.z);
		break;


	case 4:
		min = vector3(pAABB->minimum.x,
			pAABB->minimum.y,
			pAABB->minimum.z + half.z);
		max = vector3(pAABB->minimum.x + half.x,
			pAABB->minimum.y + half.y,
			pAABB->maximum.z);
		break;

	case 5:
		min = vector3(pAABB->minimum.x + half.x,
			pAABB->minimum.y,
			pAABB->minimum.z + half.z);
		max = vector3(pAABB->maximum.x,
			pAABB->minimum.y + half.y,
			pAABB->maximum.z);
		break;


	case 6:
		min = vector3(pAABB->minimum.x,
			pAABB->minimum.y + half.y,
			pAABB->minimum.z + half.z);
		max = vector3(pAABB->minimum.x + half.x,
			pAABB->maximum.y,
			pAABB->maximum.z);
		break;

	case 7:
		min = vector3(pAABB->minimum.x + half.x,
			pAABB->minimum.y + half.y,
			pAABB->minimum.z + half.z);
		max = pAABB->maximum;
		break;

	default:
		min = vector3(0, 0, 0);
		max = vector3(0, 0, 0);
		break;
	}

	return new AABB(min, max);
}

void Simplex::MyOctant::MoveEntities()
{

	AABB aabb = AABB();
	for (int i = 0; i < pParent->vEntityList.size(); i++) {

		aabb = AABB(pParent->vEntityList[i]->GetRigidBody()->GetMinGlobal(),
			pParent->vEntityList[i]->GetRigidBody()->GetMaxGlobal());

		if (pAABB->Contains(&aabb)) {
			vEntityList.push_back(pParent->vEntityList[i]);
			pParent->vEntityList.erase(pParent->vEntityList.begin() + i);
			i--;
		}
	}
}

Simplex::MyOctant::MyOctant(int depth, AABB * aabb, MyEntityManager * entityManager, MeshManager * meshManager)
{
	depth = depth;
	pEntityMngr = entityManager;
	pMeshMngr = meshManager;
	pAABB = aabb;
}

Simplex::MyOctant::~MyOctant()
{

	for (int i = 0; i < childCount; i++) {
		SafeDelete(pChildren[i]);
	}


	for (int j = 0; j < vEntityList.size(); j++) {
		SafeDelete(vEntityList[j]);
	}
}

void Simplex::MyOctant::Display()
{
	int depth = 1;

	if (depth < depth) {
		Display(depth);
	}
}

void Simplex::MyOctant::GenTree()
{
	int depth = 1;
	vEntityList = std::vector<MyEntity*>();
	for (int i = 0; i < pEntityMngr->GetEntityCount(); i++) {
		vEntityList.push_back(pEntityMngr->GetEntity(i));
	}

	if (depth < depth) {
		GenTree(depth);
	}
}

void Simplex::MyOctant::CheckCollision()
{
	int depth = 1;
	if (depth < depth) {
		CheckCollision(depth);
	}
}

Simplex::AABB::~AABB()
{
}
