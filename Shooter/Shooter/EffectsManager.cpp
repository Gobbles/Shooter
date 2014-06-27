#include "Entity.h"

EffectsManager::EffectsManager()
{}

void EffectsManager::CheckCollisions(Entity& entity)
{
	for(int i = 0; i < effectList.size(); ++i)
	{
		Effect& effect = *effectList[i];
		if(effect.mBaseQuad.getGlobalBounds().intersects(entity.baseQuad.getGlobalBounds()))
		{
			//if the bases collide, then we check offensive vs defensive
			if(effect.mOffensiveQuad.getGlobalBounds().intersects(entity.defensiveQuad.getGlobalBounds()))
			{
				//we move defenitely have a collision
				std::cout << "WE HAVE A HIT";
			}
		}
	}
}

void EffectsManager::Update(float timePassed)
{
	for(int i = 0; i < effectList.size(); ++i)
	{
		IUpdateable* updateable = dynamic_cast<IUpdateable*>(effectList[i].get());
		if(updateable != nullptr)
		{
			updateable->Update(timePassed);
		}
	}
}

void EffectsManager::Draw(sf::RenderWindow& window)
{
	for(int i = 0; i < effectList.size(); ++i)
	{
		IDrawable* drawable = dynamic_cast<IDrawable*>(effectList[i].get());
		if(drawable != nullptr)
		{
			drawable->Draw(window);
		}
	}
}

void EffectsManager::AddEffect(int id, sf::Vector2f position, bool flip)
{
	effectList.push_back(std::shared_ptr<ShotLevelOne>(new ShotLevelOne(this, position, flip)));
}

void EffectsManager::RemoveEffect(Effect* effect)
{
	//effectList.erase(std::remove(effectList.begin(), effectList.end(), effect), effectList.end());
}