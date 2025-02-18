#include "DebugUtility.h"
#include "Module.h"



Module::Module(Sprite* target)
{

	m_Target = target;
}

Module::~Module()
{
	OnDestroy();
}

void Module::Start()
{
	LOG(m_NAME << " has been added to " << m_Target->GetName());
}

void Module::Update()
{
	LOG(m_NAME << " has been updated " << m_Target->GetName());

}

void Module::OnDestroy()
{
	LOG(m_NAME << " has been destoreyed " << m_Target->GetName());

}
