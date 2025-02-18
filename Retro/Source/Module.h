#pragma once

#include "Sprite.h"


class Module
{
	public:
		Module(Sprite* target);
		~Module();

		virtual void Start();		//Called at beging of game
		virtual void Update();		//Called evry cycle
		virtual void OnDestroy();	//When object is destroyed
		
		virtual inline std::string ToString() { return m_NAME; }



	protected:
		Sprite* m_Target = nullptr;

	private:
		const std::string m_NAME = "BASE_MODULE";

};

