#include <gbcpch.h>
#include "SceneSerializer.h"
#include <yaml-cpp/yaml.h>

#include "Entity.h"
#include "Components.h"

// Deserialization stuff
namespace YAML
{
	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& v)
		{
			Node node;
			node.push_back(v.x);
			node.push_back(v.y);
			node.push_back(v.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& v)
		{
			if (node.IsSequence() && node.size() == 3)
			{
				v.x = node[0].as<float>();
				v.y = node[1].as<float>();
				v.z = node[2].as<float>();
				return true;
			}
			return false;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& v)
		{
			Node node;
			node.push_back(v.x);
			node.push_back(v.y);
			node.push_back(v.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& v)
		{
			if (node.IsSequence() && node.size() == 4)
			{
				v.x = node[0].as<float>();
				v.y = node[1].as<float>();
				v.z = node[2].as<float>();
				v.w = node[3].as<float>();
				return true;
			}
			return false;
		}
	};
}

namespace gbc
{
	// Serialization stuff
	static YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		return out << YAML::Flow << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	}

	static YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		return out << YAML::Flow << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
	}

	static void serializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap
			<< YAML::Key << "Entity" << YAML::Value << "2345823456725098356"; // TODO: use unique entity id not this garbage

		if (entity.has<TagComponent>())
		{
			auto& component = entity.get<TagComponent>();
			out << YAML::Key << "TagComponent" << YAML::BeginMap;
			out << YAML::Key << "Tag" << YAML::Value << component.tag;
			out << YAML::EndMap;
		}

		if (entity.has<TransformComponent>())
		{
			auto& component = entity.get<TransformComponent>();
			out << YAML::Key << "TransformComponent" << YAML::BeginMap;
			out << YAML::Key << "Translation" << YAML::Value << component.translation;
			out << YAML::Key << "Rotation" << YAML::Value << component.rotation;
			out << YAML::Key << "Scale" << YAML::Value << component.scale;
			out << YAML::EndMap;
		}

		if (entity.has<CameraComponent>())
		{
			auto& component = entity.get<CameraComponent>();
			out << YAML::Key << "CameraComponent" << YAML::BeginMap;

			// Camera
			auto& camera = component.camera;
			out << YAML::Key << "Camera" << YAML::BeginMap;
			out << YAML::Key << "ProjectionType" << YAML::Value << static_cast<int>(camera.getProjectionType());
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.getPerspectiveFOV();
			out << YAML::Key << "PerspectiveNearClip" << YAML::Value << camera.getPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFarClip" << YAML::Value << camera.getPerspectiveFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.getOrthographicSize();
			out << YAML::Key << "OrthographicNearClip" << YAML::Value << camera.getOrthographicNearClip();
			out << YAML::Key << "OrthographicFarClip" << YAML::Value << camera.getOrthographicFarClip();
			out << YAML::EndMap;

			out << YAML::Key << "Primary" << YAML::Value << component.primary;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << component.fixedAspectRatio;

			out << YAML::EndMap;
		}

		if (entity.has<SpriteRendererComponent>())
		{
			auto& component = entity.get<SpriteRendererComponent>();
			out << YAML::Key << "SpriteRendererComponent" << YAML::BeginMap;
			out << YAML::Key << "Color" << YAML::Value << component.color;
			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: scene(scene) {}

	void SceneSerializer::serialize(const std::string& filePath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap
			<< YAML::Key << "Scene" << YAML::Value << "Untitled"
			<< YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		scene->registry.each([&](entt::entity entityID)
		{
			Entity entity = { entityID, scene.get() };
			if (entity)
				serializeEntity(out, entity);
		});

		out << YAML::EndSeq << YAML::EndMap;

		std::ofstream file(filePath);
		if (file.is_open())
		{
			file << out.c_str() << '\n';
			file.close();
		}
		else
			GBC_CORE_WARN("Failed to serialize scene!");
	}

	void SceneSerializer::serializeRuntime(const std::string& filePath)
	{

	}

	bool SceneSerializer::deserialize(const std::string& filePath)
	{
		std::ifstream file(filePath);
		if (file.is_open())
		{
			std::stringstream stream;
			stream << file.rdbuf();

			YAML::Node data = YAML::Load(stream.str());
			if (!data["Scene"])
			{
				GBC_CORE_WARN("Failed to deserialize scene: No scene in file \"{0}\"", filePath);
				return false;
			}

			std::string sceneName = data["Scene"].as<std::string>();
			GBC_CORE_TRACE("Deserializing scene \"{0}\"", sceneName);

			auto entities = data["Entities"];
			if (entities)
			{
				// This adds entities in reverse order
				for (auto entity : entities)
				{
					uint64_t uuid = entity["Entity"].as<uint64_t>(); // TODO: actual uuid

					std::string name;
					auto tagComponent = entity["TagComponent"];
					if (tagComponent)
						name = tagComponent["Tag"].as<std::string>();

					GBC_CORE_TRACE("Deserialized entity: uuid={0} name={1}", uuid, name);

					Entity deserializedEntity = scene->createEntity(name);

					auto transformComponent = entity["TransformComponent"];
					if (transformComponent)
					{
						auto& component = deserializedEntity.get<TransformComponent>();
						component.translation = transformComponent["Translation"].as<glm::vec3>();
						component.rotation = transformComponent["Rotation"].as<glm::vec3>();
						component.scale = transformComponent["Scale"].as<glm::vec3>();
					}

					auto cameraComponent = entity["CameraComponent"];
					if (cameraComponent)
					{
						auto& component = deserializedEntity.add<CameraComponent>();

						// Camera
						auto& camera = cameraComponent["Camera"];
						component.camera.setProjectionType(static_cast<SceneCamera::ProjectionType>(camera["ProjectionType"].as<int>()));
						component.camera.setPerspectiveFOV(camera["PerspectiveFOV"].as<float>());
						component.camera.setPerspectiveNearClip(camera["PerspectiveNearClip"].as<float>());
						component.camera.setPerspectiveFarClip(camera["PerspectiveFarClip"].as<float>());
						component.camera.setOrthographicSize(camera["OrthographicSize"].as<float>());
						component.camera.setOrthographicNearClip(camera["OrthographicNearClip"].as<float>());
						component.camera.setOrthographicFarClip(camera["OrthographicFarClip"].as<float>());

						component.primary = cameraComponent["Primary"].as<bool>();
						component.fixedAspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();
					}

					auto spriteRendererComponent = entity["SpriteRendererComponent"];
					if (spriteRendererComponent)
					{
						auto& component = deserializedEntity.add<SpriteRendererComponent>();
						component.color = spriteRendererComponent["Color"].as<glm::vec4>();
					}
				}
			}

			return true;
		}

		GBC_CORE_WARN("Failed to deserialize scene!");
		return false;
	}

	bool SceneSerializer::deserializeRuntime(const std::string& filePath)
	{
		return false;
	}
}
