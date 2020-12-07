#include "../../include/engine/ObjectCollision.hpp"
#include "../../include/engine/ObjectManager.hpp"
#include "../../include/math/Random.hpp"
#include <vector>
#include "../../include/math/Functions.hpp"
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
		
			for (std::size_t a = 0; a < obj1Vertices->size(); a++)
			{
				int b = (a + 1) % obj1Vertices->size();
				Vertex &pa = obj1Vertices->at(a);
				Vertex &pb = obj1Vertices->at(b);
				
				Vertex dir = {pb.x - pa.x, pb.y - pa.y};
				Vertex n = {-dir.y, dir.x};
				float d = -(n.x*pa.x + n.y*pa.y);

				std::size_t p;

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