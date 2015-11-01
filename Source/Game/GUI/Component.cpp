#include "Component.h"
#include "../../Debug/Error.h"
#include "../../Utility/Singletons.h"
#include <assert.h>
using namespace Grim;

Component::Component()
	: m_Parent(nullptr)
{
}

void Component::setParent(Component::Pointer parent)
{
	assert(parent != nullptr);
	if (parent != nullptr)
	{
		m_Parent = parent;
	}
	else
	{
		Singletons::log.print(Singletons::resources.findString("GUI_COMPONENT_NULLPTR"));
		throw Error::Fatal;
	}
}