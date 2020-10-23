#pragma once

#include "Scene.h"

namespace gbc
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void serialize(const std::string& filePath);
		void serializeRuntime(const std::string& filePath);

		bool deserialize(const std::string& filePath);
		bool deserializeRuntime(const std::string& filePath);
	private:
		Ref<Scene> scene;
	};
}
