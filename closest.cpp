#include<iostream>
#include<vector>
#include<cmath>
#include<limits>

struct Point
{
	double x,y;
	Point(double _x,double _y) : x(_x),y(_y){}
};

double distance(const Point& p1,const Point& p2)
{
	double dx = p1.x - p1.y;
	double dy = p2.x - p2.y;
	return std::sqrt(dx * dx,dy * dy);
}

double bruteForceClosestPair(const std::vector<Point>& points)
{
	double minDistance = std::numeric_limits<double>::max();
	int n = points.size();
	
	for(int i = 0;i < n;i++)
	{
		for(int j = i + 1;j < n;j++)
		{
			double dist = distance(points[i],points[j]);
			if(dist < minDistance)
			{
				minDistance = dist;
			}
		}
	}
	return minDistance;
}

int main()
{
	std::vector<Point> points = {{1.0,2.0},{3.0,4.0},{5.0,6.0},{7.0,8.0}};
	double closestDistance = bruteForceClosestPair(points);
	
	std::cout << "Closest pair distance: " << closestDistance << std::endl;
	return 0;
}
