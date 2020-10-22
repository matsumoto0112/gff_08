#pragma once

namespace strix { namespace client { namespace ingame { namespace component {

class BaseComponent
{
public:
	BaseComponent() {}

	virtual ~BaseComponent() {}

	virtual void Tick();

	virtual void OnCreated();
};


} } } }