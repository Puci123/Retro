#include "Scean.h"
#include "DebugUtility.h"



Scean::Scean()
	:m_MapWidth(24), m_MapHeight(24)
{
	m_MapLayout =
	{
	  1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,
	  1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1,
	  1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};

	m_CameraMain = Camera(mu::vec2{22.0f, 12.f},mu::vec2{-0.1f, 0.f},mu::vec2{0.0f, 0.66f}, nullptr);
	//m_CameraMain.SetFOV(130);

	LOG("Created map with size: " << m_MapWidth << "x" << m_MapHeight);

	//=================================	INIT TEXTURE (TEST ONLY) =================================//


	

	AddMapTileTexture(Texture2D("Resources\\Textures\\bluestone.png",false), "Resources\\Textures\\bluestone.png");	//1
	AddMapTileTexture(Texture2D("Resources\\Textures\\redbrick.png", false), "Resources\\Textures\\redbrick.png");	//2
	AddMapTileTexture(Texture2D("Resources\\Textures\\greystone.png", false),"Resources\\Textures\\greystone.png");	//3
	AddMapTileTexture(Texture2D("Resources\\Textures\\mossy.png", false),	 "Resources\\Textures\\mossy.png");		//4
	AddMapTileTexture(Texture2D("Resources\\Textures\\eagle.png", false),	 "Resources\\Textures\\eagle.png");		//5
	AddMapTileTexture(Texture2D("Resources\\Textures\\barrel.png", false),   "Resources\\Textures\\barrel.png");	//6


	///================================= INIT SPRITES =================================//

	mu::vec2 scale = mu::vec2{ 1.f, 1.f };

	m_SceanSprites.push_back(Sprite(20.5f, 11.5f, scale, 6));
	m_SceanSprites.push_back(Sprite(10.0f, 12.5f, scale, 6));

}

Scean::Scean(int32_t width, int32_t height)
	: m_MapWidth(width), m_MapHeight(height)
{
	m_MapLayout.resize(width * height,0);
	m_CameraMain = Camera(mu::vec2{ 22.0f, 12.f }, mu::vec2{ -1.0f, 0.f }, mu::vec2{ 0.f, 0.66f }, nullptr);
}

Scean::Scean(int32_t width, int32_t height, const std::vector<uint8_t>& layout)
	: m_MapWidth(width), m_MapHeight(height)
{
	m_MapLayout.resize(width * height);

	for (int32_t i = 0; i < width * height; i++)
	{
		m_MapLayout[i] = layout[i];
	}


	m_CameraMain = Camera(mu::vec2{ 22.0f, 12.f }, mu::vec2{ -1.0f, 0.f }, mu::vec2{ 0.f, 0.66f }, nullptr);
}

Scean::~Scean(){}


uint8_t Scean::GetCellValue(int32_t x, int32_t y) const
{
	ASSERT(x < m_MapWidth);		    //Invalid map width
	ASSERT(y < m_MapHeight);		//Invalid map height

	return m_MapLayout[y * m_MapWidth + x];
}

const Texture2D& Scean::GetTexture(uint32_t texID) const
{
	ASSERT(--texID < m_SceanTextures.size()); //Invalid texture id
	return m_SceanTextures[texID];

}

bool const Scean::IsSprite(const mu::vec2& pos, float ep)
{
	for (int32_t i = 0; i < m_SceanSprites.size(); i++)
	{
		if (mu::Lenght(pos, m_SceanSprites[i].GetPos()) < ep) return true;
	}

	return false;
}

void Scean::MoveCam(mu::vec2 translation)
{
	m_CameraMain.MoveCamera(translation);
}

void Scean::RoteateCamera(float r)
{
	m_CameraMain.RotateCam(r);
}

void Scean::UpdateSprites()
{
	for (Sprite& sprite : m_SceanSprites)
	{
		sprite.UpdateAllModules();
	}
}

void Scean::InseretWall(mu::vec2Int pos, int32_t elemntID)
{
	if (pos.x >= m_MapWidth || pos.x < 0) 
	{
		LOG_ERROR("Invalid wall pose: " << pos.x  << " Map width is: " << m_MapWidth);
		return;
	}

	if (pos.y >= m_MapWidth || pos.y < 0)
	{
		LOG_ERROR("Invalid wall pose: " << pos.y << " Map width is: " << m_MapHeight);
		return;
	}

	m_MapLayout[pos.y * m_MapWidth + pos.x] = elemntID;

}

void Scean::InsertSpeite(mu::vec2 pos, int32_t elemntID)
{	


	if (!IsSprite(pos))
	{
		Sprite sprite(pos, mu::vec2{ 1,1 }, elemntID);

		m_SceanSprites.push_back(sprite);
		LOG("Sprite suscesfully created");
	}
	else
	{
		LOG("Place is arealedy ociupaed");
	}
}

bool Scean::DeleteSpriteWithID(int32_t id)
{
	if (id < m_SceanSprites.size())
	{
	
		for (int32_t i = id; i < m_SceanSprites.size() - 1; i++)
		{
			m_SceanSprites[i] = std::move( m_SceanSprites[i + 1]);
		}
		
		m_SceanSprites.pop_back();
		LOG("Delted sprite with id: " << id);
		return true;
	}

	LOG_ERROR("INVALID ID PASSED TO DELETE SPRITE! " << id);
	return false;

}

int32_t Scean::GetSpriteFromCeell(mu::vec2Int cell)
{
	for (size_t i = 0; i < m_SceanSprites.size(); i++)
	{
		mu::vec2Int temp = mu::vec2Int{ static_cast<int32_t>(m_SceanSprites[i].GetPos().x) , static_cast<int32_t>(m_SceanSprites[i].GetPos().y )};

		if (temp.x == cell.x && temp.y == cell.y) 
		{
			LOG("FOUND SPIRTE AT POS (sprite ID:" << i);
			return i;
		}
	}


	LOG("Do not found sprite (sprite ID: -1");
	return -1;
}

int32_t Scean::AddMapTileTexture(const Texture2D& asset, const std::string& name)
{
	if (m_NamesIDs.find(name) == m_NamesIDs.end()) 
	{
		LOG("Scean does not contain elemnt");
		LOG("Add: " << name << " with SID: " << m_IDcounter);
		m_NamesIDs[name] = m_IDcounter++;
		m_SceanTextures.push_back(asset);

		return (m_IDcounter - 1);
	}
	else
	{
		return m_NamesIDs[name];
	}


}
	
