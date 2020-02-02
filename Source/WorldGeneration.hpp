#ifndef WORLD_GENERATION_HPP
#define WORLD_GENERATION_HPP

#include <vector>

enum BoundryConditions : uint32_t
{
	Brick = 1,
	Empty = 1 << 1
};


struct Node
{
	BoundryConditions mConditions[6][4];
};


class WorldForge
{
public:

	WorldForge(const size_t x, const size_t y) :
		mNodeSet{},
		xSize{x},
		ySize{y},
		mWorldNodes(x * y) 
	{
	}

	void addNode(const Node& node)
	{
		mNodeSet.push_back(node);
	}

	void collapse();

private:

	std::vector<Node> mNodeSet;

	size_t xSize;
	size_t ySize;
	std::vector<uint32_t> mWorldNodes;
};


#endif