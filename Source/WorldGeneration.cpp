#include "WorldGeneration.hpp"

#include <algorithm>
#include <random>


void WorldForge::collapse()
{
	std::vector<Node> tmpNodes;
	tmpNodes.reserve(mNodeSet.size());

	for (size_t x = 0; x < xSize; ++x)
	{
		for (size_t y = 0; y < ySize; ++y)
		{
			const size_t index = (x * ySize) + y;
			const Node& currentNode = mNodeSet[mWorldNodes[index]];

			std::copy_if(mNodeSet.begin(), mNodeSet.end(), tmpNodes.begin(), [&](const Node& node)
			{
				return true; // TODO add a proper predicate.
			});

			const uint32_t randomIndex = rand() % tmpNodes.size();
			Node newNode = tmpNodes[randomIndex];

			//const auto it = std::find(mNodeSet.begin(), mNodeSet.end(), newNode);
			//const auto newIndex = std::distance(mNodeSet.begin(), it);

			//mWorldNodes[index] = newIndex;

		}
		tmpNodes.clear();
	}
}
