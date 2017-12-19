#pragma once

#include "MyEntityManager.h"
#include <vector>

namespace Simplex
{
	struct AABB {
		vector3 minimum;
		vector3 maximum;

		AABB() {
			minimum = vector3(0, 0, 0);
			maximum = vector3(0, 0, 0);
		}

		AABB(vector3 min, vector3 max) {
			minimum = min;
			maximum = max;
		}

		~AABB();


		bool Contains(AABB* other) {
			bool contains = minimum.x < other->minimum.x && 
							minimum.y < other->minimum.y &&
							minimum.z < other->minimum.z &&
							maximum.x > other->maximum.x &&
							maximum.y > other->maximum.y &&
							maximum.z > other->maximum.z;
			return contains;
			
		}

		vector3 Center()
		{
			return vector3(minimum.x + (maximum.x - minimum.x) / 2,
				minimum.y + (maximum.y - minimum.y) / 2,
				minimum.z + (maximum.z - minimum.z) / 2);
		}

		vector3 Size()
		{
			return vector3((maximum.x - minimum.x) * 1,
				(maximum.y - minimum.y) * 1,
				(maximum.z - minimum.z) * 1);
		}

	};


	class MyOctant
	{
	private:
		const int MINIMUENTITIES = 4;
		int depth;
		int childCount = 0;
		AABB* pAABB = nullptr;
		MyOctant* pParent = nullptr;
		MyOctant* pChildren[8];
		MyEntityManager* pEntityMngr = nullptr;
		MeshManager* pMeshMngr = nullptr;
		std::vector<MyEntity*> vEntityList;

		void Display(int depth);
		void GenTree(int depth);
		void CheckCollision(int depth);
		AABB* CreateSubdivision(int index);
		void MoveEntities();

	public:
		MyOctant(int depth, AABB* aabb, MyEntityManager* entityManager, MeshManager* meshManager);
		~MyOctant();

		void Display();
		void GenTree();
		void CheckCollision();
	};
}