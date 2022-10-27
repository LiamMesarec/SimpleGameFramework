#include "engine/ObjectCollision.hpp"
#include "engine/ObjectManager.hpp"
#include "math/Random.hpp"
#include <vector>
#include "math/Functions.hpp"
#include <cmath>
#include <iostream>

namespace sgf
{
    bool ObjectCollision::Collided(Polygon& polygon1, Polygon& polygon2)
    {
		if(polygon2.IsDeleted() || polygon1.IsDeleted())
		{
			return false;
		}
		
        std::vector<Vertex>* obj1Vertices = &polygon1.GetVertices();
        std::vector<Vertex>* obj2Vertices = &polygon2.GetVertices();

		for(int shape = 0; shape < 2; shape++)
		{
			if(shape == 1)
			{
				obj1Vertices = &polygon2.GetVertices();
				obj2Vertices = &polygon1.GetVertices();
			}

			for (std::size_t a = 0; a < (obj1Vertices->size() - 1); a++)
			{
				int b = (a + 1) % (obj1Vertices->size() - 1);
				Vertex axisProj = { -(obj1Vertices->at(b).y - obj1Vertices->at(a).y), obj1Vertices->at(b).x - obj1Vertices->at(a).x };
				float d = sqrtf(axisProj.x * axisProj.x + axisProj.y * axisProj.y);
				axisProj = { axisProj.x / d, axisProj.y / d };

				float min_r1 = INFINITY, max_r1 = -INFINITY;
				for (std::size_t p = 0; p < (obj1Vertices->size() - 1); p++)
				{
					float q = (obj1Vertices->at(p).x * axisProj.x + obj1Vertices->at(p).y * axisProj.y);
					min_r1 = std::min(min_r1, q);
					max_r1 = std::max(max_r1, q);
				}

				float min_r2 = INFINITY, max_r2 = -INFINITY;
				for (std::size_t p = 0; p < (obj2Vertices->size() - 1); p++)
				{
					float q = (obj2Vertices->at(p).x * axisProj.x + obj2Vertices->at(p).y * axisProj.y);
					min_r2 = std::min(min_r2, q);
					max_r2 = std::max(max_r2, q);
				}

				if(!(max_r2 >= min_r1 && max_r1 >= min_r2))
				{
					return false;
				}
			}
		}

		return true;
    }

	bool ObjectCollision::CollisionNotAllowed(Polygon& polygon1, Polygon& polygon2)
	{
		if(polygon2.IsDeleted() || polygon1.IsDeleted())
		{
			return false;
		}

        std::vector<Vertex>* obj1Vertices = &polygon1.GetVertices();
        std::vector<Vertex>* obj2Vertices = &polygon2.GetVertices();

		float overlap = INFINITY;
		
		for (int shape = 0; shape < 2; shape++)
		{
			if (shape == 1)
			{
				obj1Vertices = &polygon2.GetVertices();
				obj2Vertices = &polygon1.GetVertices();
			}

			for (std::size_t a = 0; a < (obj1Vertices->size() - 1); a++)
			{
				int b = (a + 1) % (obj1Vertices->size() - 1);
				Vertex axisProj = { -(obj1Vertices->at(b).y - obj1Vertices->at(a).y), obj1Vertices->at(b).x - obj1Vertices->at(a).x };
				
				float d = sqrtf(axisProj.x * axisProj.x + axisProj.y * axisProj.y);
				axisProj = { axisProj.x / d, axisProj.y / d };

				float min_r1 = INFINITY, max_r1 = -INFINITY;
				for (std::size_t p = 0; p < (obj1Vertices->size() - 1); p++)
				{
					float q = (obj1Vertices->at(p).x * axisProj.x + obj1Vertices->at(p).y * axisProj.y);
					min_r1 = std::min(min_r1, q);
					max_r1 = std::max(max_r1, q);
				}

				float min_r2 = INFINITY, max_r2 = -INFINITY;
				for (std::size_t p = 0; p < (obj2Vertices->size() - 1); p++)
				{
					float q = (obj2Vertices->at(p).x * axisProj.x + obj2Vertices->at(p).y * axisProj.y);
					min_r2 = std::min(min_r2, q);
					max_r2 = std::max(max_r2, q);
				}

				overlap = std::min(std::min(max_r1, max_r2) - std::max(min_r1, min_r2), overlap);

				if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
					return false;
			}
		}

		Vertex d = { polygon2.GetCenterCoords().x - polygon1.GetCenterCoords().x, polygon2.GetCenterCoords().y - polygon1.GetCenterCoords().y};
		float s = sqrtf(d.x*d.x + d.y*d.y);

		if((overlap * d.x / s) > 2.0f && (overlap * d.y / s) > 2.0f)
		{
			polygon1.Move(-(overlap * d.x / s), -(overlap * d.y / s));
		}
		else if ((overlap * d.x / s) <= 2.0f)
		{
			polygon1.Move(0, -(overlap * d.y / s));
		}
		else if((overlap * d.y / s) <= 2.0f)
		{
			polygon1.Move(-(overlap * d.x / s), 0);
		}

		return true;
	}
}
