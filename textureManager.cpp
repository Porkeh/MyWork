#include "textureManager.h"


TextureManager::TextureManager()
{

}
void TextureManager::SetBaseDir(string baseDir)
{
	TextureManager::baseDir = baseDir;
}
void TextureManager::Load(vector<string> fileNames)
{

	for (int i = 0; i < fileNames.size(); i++)
	{
		string fileDir = baseDir + fileNames.at(i);

		sf::Texture temp;
		if (!temp.loadFromFile(fileDir))
		{

		}

		textures.push_back(temp);
	}

}


sf::Texture & TextureManager::GetTexture(int index)
{
	return textures.at(index);
}