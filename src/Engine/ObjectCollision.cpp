#include "ObjectCollision.hpp"
#include "ObjectManager.hpp"
#include "../math/Random.hpp"
#include <vector>
#include "../math/Functions.hpp"
#include <cmath>
#include <iostream>

namespace sgf
{
    bool ObjectCollision::Collided(int obj1ID, int obj2ID)
    {
        std::vector<math::Vertex>* obj1Vertices = &ObjectManager::objects.at(obj1ID);
        std::vector<math::Vertex>* obj2Vertices = &ObjectManager::objects.at(obj2ID);

		for (int shape = 0; shape < 2; shape++)
		{
			if (shape == 1)
			{
				obj1Vertices = &ObjectManager::objects.at(obj2ID);
				obj2Vertices = &ObjectManager::objects.at(obj1ID);
			}
		
			for (int a = 0; a < obj1Vertices->size(); a++)
			{
				int b = (a + 1) % obj1Vertices->size();
				math::Vertex &pa = obj1Vertices->at(a);
				math::Vertex &pb = obj1Vertices->at(b);
				
				math::Vertex dir = {pb.x - pa.x, pb.y - pa.y};
				math::Vertex n = {-dir.y, dir.x};
				float d = -(n.x*pa.x + n.y*pa.y);

				int p;

				for (p = 0; p < obj2Vertices->size(); p++)
				{
					const auto &pt = obj2Vertices->at(p);
					float dist = n.x * pt.x + n.y * pt.y + d;

					if (dist < 0)
						break;
				}

				if (p >= obj2Vertices->size())
					return false;			
			}
		}

		return true;
    }
}