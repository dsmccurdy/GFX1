#include "Entity.h"

#include <map>
#include <atomic>
#include <mutex>

namespace World{

	namespace zzInternal{
		struct EntityData{
			std::map<AttributeID, std::shared_ptr<void>> attributes;

		};
	}//namespace zzInternal

	Entity::Entity(){
		data = new zzInternal::EntityData();
		setNodeType(NODE_TYPE::NT_ENTITY);
	}//Entity::Entity()

	Entity::~Entity(){
		delete data;
	}//Entity::~Entity()

	template<typename T>
	std::shared_ptr<T> Entity::getAttribute(AttributeID id){
		return std::static_pointer_cast<T>(data->attributes[id]);
	}//T Entity::getAttribute(AttributeID id)

	template<typename T>
	void Entity::setAttribute(AttributeID id, std::shared_ptr<T> attrib){
		data->attributes[id] = std::static_pointer_cast<void>(attrib)
	}//void Entity::setAttribute(AttributeID id,T attrib)


	bool Entity::hasAttribute(AttributeID id){
		return data->attributes.find(id) != data->attributes.end();
	}//bool Entity::hasAttribute(AttributeID id)



	static std::mutex entityAttributeMapLock;
	static std::map<AttributeID, std::string> entityAttributeIdToName;
	static std::map<std::string, AttributeID> entityAttributeNameToId;
	static std::atomic<AttributeID> entityAttributeId = 0;

	AttributeID Entity::getAttributeID(std::string name){
		std::lock_guard<std::mutex> lock(entityAttributeMapLock);

		if (entityAttributeNameToId.find(name) != entityAttributeNameToId.end())
			return entityAttributeNameToId[name];
		entityAttributeNameToId[name]=entityAttributeId.fetch_add(1);
		entityAttributeIdToName[entityAttributeNameToId[name]] = name;
		return entityAttributeNameToId[name];
	}//AttributeID Entity::getAttributeID(std::string name)


	std::string Entity::getAttributeName(AttributeID id){
		std::lock_guard<std::mutex> lock(entityAttributeMapLock);

		if (entityAttributeIdToName.find(id) != entityAttributeIdToName.end())
			return entityAttributeIdToName[id];
		return nullptr;
	}//std::string Entity::getAttributeName(AttributeID id)

}//namepsace World