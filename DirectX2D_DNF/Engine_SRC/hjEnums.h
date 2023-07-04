#pragma once
namespace hj::enums
{
	enum class eComponentType
	{
		NOne,
		Transform,
		Mesh,
		Particle,
		MeshRenderer,
		Script,
		End,
	};

	enum class eLayerType
	{
		Player,
		Monster,
		UI,
		End,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		End,
	};
}