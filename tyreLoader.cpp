using namespace std;
#include "tyreLoader.h"



TyreLoader::TyreLoader()
{

}


void TyreLoader::ReadFile(vector<Vector<float>> &position)
{
	string line;
	fstream modelFile(".\\resources\\tyrePos.txt", ios_base::in);
	if (modelFile.is_open())
	{
		while (getline(modelFile, line))
		{
			float i = 0;
			float j = 0;
			float k = 0;
			float l = 0;
			float m = 0;
			string s;
			istringstream iss(line);

			iss >> s;
			if (s == "l")
			{


				iss >> i >> j >> k >> l;
				position.push_back(Vector<float>(i, j));
				//position.push_back(Vector<float>(k, l));
				GenerateTyreLine(position, i, j, k, l);
				

			}

			if (s == "a")
			{
				iss >> i >> j >> k >> l >> m;
				position.push_back(Vector<float>(i, j));
				GenerateTyreArc(position, i, j, k, l, 105, m);
			}

			if (s == "t")
			{
				iss >> i >> j;
				position.push_back(Vector<float>(i, j));
			}

			

		}
	}

};

void TyreLoader::GenerateTyreLine(vector<Vector<float>> &position, float startX, float startY, float endX, float endY)
{

	float tyreRadius = 32;

	while (startX < endX  || startY < endY)
	{
		if (startX < endX)
		{
			startX += tyreRadius;
		}
		if (startY < endY)
		{
			startY += tyreRadius;
		}
		position.push_back(Vector<float>(startX, startY));
	}

	


}

void TyreLoader::GenerateTyreArc(vector<Vector<float>> &position, float startX, float startY, float rotationAmount, float numberOfIntervals, float radius, float offset)
{
	float angleIncrement = rotationAmount / numberOfIntervals ;
	float radInc = angleIncrement * 3.14 / 180;
	float radOffset = offset * 3.14 / 180;
	for (int i = 0; i < numberOfIntervals+1; i++)
	{
		float x = cos((radInc*i) + (radOffset));
		x = x*radius + startX;
		float y = sin((radInc*i) + (radOffset));
		y = y*radius + startY;
		position.push_back(Vector<float>(x, y));
	}

}