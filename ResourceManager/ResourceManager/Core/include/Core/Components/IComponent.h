#pragma once
#include <string>

namespace Core::Components
{
	class IComponent
	{
	public:
		virtual ~IComponent() = default;
		virtual const std::string GetType() const = 0;
		virtual void Update() = 0;
	};
}
