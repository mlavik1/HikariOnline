#include "world.h"

#include "Core/Debug/st_assert.h"
#include "Core/Engine/game_engine.h"
#include "Core/Component/terrain_component.h"
#include "Core/Misc/ogre_utils.h"
#include "Core/Debug/debug_graphics.h"

namespace Hikari
{
	World::World(Ogre::SceneManager* arg_scenemanager)
	{
		__Assert(arg_scenemanager != nullptr);
		mSceneManager = arg_scenemanager;
		mTerrain = nullptr;
	}

	void World::AddActor(Actor* arg_actor)
	{
		mActors.push_back(arg_actor);
	}

	void World::LoadTerrain()
	{
		size_t gridWidth = mWorldSizeX / mGridUnitSize;
		size_t gridHeight = mWorldSizeZ / mGridUnitSize;
		size_t gridSize = (mWorldSizeX * mWorldSizeX) / mGridUnitSize;
		mTerrain = new Terrain();
		mTerrain->HeightMap = new float[gridSize];
		std::fill(mTerrain->HeightMap, mTerrain->HeightMap + gridSize, -1000000.0f);
		//std::vector<size_t>* triangleIndexArray = new std::vector<size_t>[gridSize];

		for (ObjectPtrBase<Actor>& actor : mActors)
		{
			TerrainComponent* terrainComp = actor->GetComponentOfType<TerrainComponent>();
			if (terrainComp != nullptr)
			{
				std::vector<Ogre::Vector3> vertices;
				std::vector<unsigned int> indices;
				OgreUtils::GetMeshInfo(actor.Get(), vertices, indices);

				size_t numVertices = vertices.size();
				size_t numIndices = indices.size();
				size_t numTriangles = indices.size() / 3;

				const int maxGridX = mWorldSizeX * mGridUnitSize;
				const int maxGridZ = mWorldSizeZ * mGridUnitSize;

				for (size_t i_index = 0; i_index < numIndices - 3; i_index += 3)
				{
					int minX = maxGridX + 1;
					int maxX = -1;
					int minZ = maxGridZ + 1;
					int maxZ = -1;
					int triangleIndices[3] = {indices[i_index], indices[i_index + 1] , indices[i_index + 2] };
					for (size_t i = 0; i < 3; i++)
					{
						size_t i_vertex = triangleIndices[i];
						const Ogre::Vector3& vertex = vertices[i_vertex];
						minX = std::min(minX, (int)(vertex.x / mGridUnitSize));
						maxX = std::max(maxX, (int)(vertex.x / mGridUnitSize));
						minZ = std::min(minZ, (int)(vertex.z / mGridUnitSize));
						maxZ = std::max(maxZ, (int)(vertex.z / mGridUnitSize));
					}

					minX = std::max(minX, 0);
					minZ = std::max(minZ, 0);
					maxX = std::min(maxX, maxGridX);
					maxZ = std::min(maxZ, maxGridZ);

					const Ogre::Vector3& p0 = vertices[triangleIndices[0]];
					const Ogre::Vector3& p1 = vertices[triangleIndices[1]];
					const Ogre::Vector3& p2 = vertices[triangleIndices[2]];
					const float& p0x = p0.x;
					const float& p0z = p0.z;
					const float& p1x = p1.x;
					const float& p1z = p1.z;
					const float& p2x = p2.x;
					const float& p2z = p2.z;

					float triangleSignedArea = 0.5 *(-p1z*p2x + p0z*(-p1x + p2x) + p0x*(p1z - p2z) + p1x*p2z);

					for (int x = minX; x <= maxX; x++)
					{
						for (int z = minZ; z <= maxZ; z++)
						{
							float px = x * mGridUnitSize;
							float pz = z * mGridUnitSize;

							float s = 1.0f / (2.0f * triangleSignedArea)*(p0z*p2x - p0x*p2z + (p2z - p0z)*px + (p0x - p2x)*pz);
							float t = 1.0f / (2.0f * triangleSignedArea)*(p0x*p1z - p0z*p1x + (p0z - p1z)*px + (p1x - p0x)*pz);
							if (s >= 0.0f && t >= 0.0f && (1.0f - s - t) >= 0.0f)
							{ // point is inside triangle
								Ogre::Vector3 u = p1 - p0;
								Ogre::Vector3 v = p2 - p0;
								Ogre::Vector3 p = p0 + u*s + v*t;
								const float& oldHeight = mTerrain->HeightMap[(size_t)x + (((size_t)z) * gridWidth)];
								if(p.y > oldHeight)
									mTerrain->HeightMap[(size_t)x + (((size_t)z) * gridWidth)] = p.y;
							}
						}
					}
				}
			}
		}

		LOG_INFO() << "Finished creating terrain height map";
		

		// TEMP TEST:

		std::vector<Ogre::Vector3> processedUnits;
		std::vector<Ogre::Vector3> unprocessedUnits;

		for (size_t grid_x = 0; grid_x < gridWidth; grid_x++)
		{
			for (size_t grid_z = 0; grid_z < gridHeight; grid_z++)
			{
				float x = grid_x * mGridUnitSize;
				float z = grid_z * mGridUnitSize;
				float height = mTerrain->HeightMap[grid_x + (grid_z * gridWidth)];
				if (height > -200.0f)
					processedUnits.push_back(Ogre::Vector3(x, height + 2.0f, z));
				else
					unprocessedUnits.push_back(Ogre::Vector3(x, 14.0f, z));
			}
		}
		//DebugGraphics::DrawDebugPoints(this, processedUnits, 5.0f, Ogre::ColourValue::Black, 10.0f);
		//DebugGraphics::DrawDebugPoints(this, unprocessedUnits, 5.0f, Ogre::ColourValue::Red, 10.0f);
	}


	float World::GetTerrainHeight(float arg_x, float arg_z)
	{
		float height = 0.0f;

		if (mTerrain != nullptr && arg_x >= 0.0f && arg_x < mWorldSizeX && arg_z >= 0.0f && arg_z < mWorldSizeZ)
		{
			const size_t gridWidth = mWorldSizeX / mGridUnitSize;
			size_t x = (size_t)arg_x;
			size_t z = (size_t)arg_z;
#ifdef Tullball
			height = mTerrain->HeightMap[x + (z * gridWidth)];
#else
			size_t x2 = x + 1;
			size_t z2 = z + 1;
			float s = arg_x - (float)x;
			float t = arg_z - (float)z;
			float height0 = mTerrain->HeightMap[x + (z * gridWidth)];
			float height1 = mTerrain->HeightMap[x2 + (z * gridWidth)];
			float height2 = mTerrain->HeightMap[x + (z2 * gridWidth)];
			float height3 = mTerrain->HeightMap[x2 + (z2 * gridWidth)];

			float heightA = height1*s + height0*(1.0f - s);
			float heightB = height3*s + height2*(1.0f - s);
			height = heightB * t + heightA * (1.0f - t);
#endif
		}

		return height;
	}

}
