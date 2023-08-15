#pragma once

#include<iostream>
#include<unordered_set>
#include<vector>
#include<array>

//����GridLocation, ������������xy
struct GridLocation {
	int x, y;
};

//����hash�����Ӷ����Խ�GridLocation������unordered_set��
namespace std {
	template<> struct hash<GridLocation> {
		std::size_t operator()(const GridLocation& id) const noexcept {
			return std::hash<int>()(id.x ^ (id.y << 16);
		}
	};
}

struct SquareGrid {
	SquareGrid(int width, int heighth):width_(width), heighth_(heighth){}

	static std::array<GridLocation, 4> DIRS; //�ɱ����ķ���
	int width_, heighth_;
	
	std::unordered_set<GridLocation> walls; //��ͼ���ϰ����λ��

	bool in_bounds(GridLocation& id) const {
		return 0 <= id.x && id.x < width_
			&& 0 <= id.y && id.y < heighth_;
	}

	bool passable(GridLocation& id) const {
		return walls.find(id) == walls.end();
	}

	std::vector<GridLocation> neighbors(GridLocation& id) const {
		std::vector<GridLocation> res;

		for (GridLocation dir : DIRS) {
			GridLocation next{ id.x + dir.x, id.y + dir.y };
			if (in_bounds(next) && passable(next)) {
				res.push_back(next);
			}
		}



		return res;
	}
};

std::array<GridLocation, 4> SquareGrid::DIRS = {
	GridLocation{1, 0}, GridLocation{-1, 0},
	GridLocation{0, 1}, GridLocation{0,-1}
};