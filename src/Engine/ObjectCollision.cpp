#include "ObjectCollision.hpp"
#include "ObjectManager.hpp"
#include "../math/Random.hpp"
#include <vector>
#include "../math/Functions.hpp"
#include <cmath>
#include <iostream>

namespace sgf
{
    bool ObjectCollision::Collided(Polygon& polygon1, Polygon& polygon2)
    {
        std::vector<Vertex>* obj1Vertices = &polygon1.GetVertices();
        std::vector<Vertex>* obj2Vertices = &polygon2.GetVertices();

		for (int shape = 0; shape < 2; shape++)
		{
			if (shape == 1)
			{
				obj1Vertices = &polygon2.GetVertices();
				obj2Vertices = &polygon1.GetVertices();
			}
		
			for (unsigned long long int a = 0; a < obj1Vertices->size(); a++)
			{
				int b = (a + 1) % obj1Vertices->size();
				Vertex &pa = obj1Vertices->at(a);
				Vertex &pb = obj1Vertices->at(b);
				
				Vertex dir = {pb.x - pa.x, pb.y - pa.y};
				Vertex n = {-dir.y, dir.x};
				float d = -(n.x*pa.x + n.y*pa.y);

				unsigned long long int p;

				for (p = 0; p < obj2Vertices->size(); p++)
				{
					Vertex &pt = obj2Vertices->at(p);
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