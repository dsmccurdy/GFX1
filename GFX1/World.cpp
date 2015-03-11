#include "World.h"

#include <map>
#include <thread>

namespace World{


	struct WorldData{
		std::shared_ptr<Node> rootNode;

		std::map<std::string, std::shared_ptr<Node>> byName;
		std::map<NodeID, std::shared_ptr<Node>> byID;

		
	};

	World::World(){
		data = new WorldData();

		data->rootNode = std::shared_ptr<Node>(new Node());
		data->rootNode->setNodeName("World");
		data->byName["World"] = data->rootNode;
		data->byID[data->rootNode->getNodeID()] = data->rootNode;
	}//World::World()

	World::~World(){
		delete data;
	}//World::~World()

	void World::initalizeStage1(void){

	}//void World::initalizeStage1(void)

	void World::startWritePhase(void){

	}//void World::startWritePhase(void)

	std::shared_ptr<Node> World::getRootNode(void) const{
		return data->rootNode;
	}//std::shared_ptr<Node> World::getRootNode(void) const

	std::shared_ptr<Node> World::getNodeByName(std::string name) const{
		if (name.length()==0 || data->byName.find(name) == data->byName.end())
			return nullptr;
		return data->byName[name];
	}//std::shared_ptr<Node> World::getNodeByName(std::string name)

	std::shared_ptr<Node> World::getNodeByID(NodeID id) const{
		if (data->byID.find(id) == data->byID.end())
			return nullptr;
		return data->byID[id];
	}//std::shared_ptr<Node> World::getNodeByID(NodeID id) const

	

	std::shared_ptr<Node> World::createNewNode(void){
		std::shared_ptr<Node> node = std::shared_ptr<Node>(new Node());

		class cb : public System::ICallbackItem{
		public:
			std::shared_ptr<Node> node;
			WorldData*data;
			cb(WorldData*data,std::shared_ptr<Node> node) : ICallbackItem(){
				this->node = node;
				this->data = data;
			}
			virtual void callback(void){
				data->byID[node->getNodeID()] = node;
				if (node->getNodeName().length()>0)
					data->byName[node->getNodeName()] = node;
			}
		};
		addCallback(std::shared_ptr<cb>(new cb(data,node)));

		return node;
	}//std::shared_ptr<Node> World::createNewNode(void)

	std::shared_ptr<Node> World::createNewNode(std::string name){
		std::shared_ptr<Node> node = std::shared_ptr<Node>(new Node());
		node->setNodeName(name);

		class cb : public System::ICallbackItem{
		public:
			std::shared_ptr<Node> node;
			WorldData*data;
			cb(WorldData*data, std::shared_ptr<Node> node) : ICallbackItem(){
				this->node = node;
				this->data = data;
			}
			virtual void callback(void){
				data->byID[node->getNodeID()] = node;
				if (node->getNodeName().length()>0)
					data->byName[node->getNodeName()] = node;
			}
		};
		addCallback(std::shared_ptr<cb>(new cb(data, node)));

		return node;
	}//std::shared_ptr<Node> World::createNewNode(std::string name)

	std::shared_ptr<Entity> World::createNewEntity(void){
		std::shared_ptr<Entity> entity = std::shared_ptr<Entity>(new Entity());

		class cb : public System::ICallbackItem{
		public:
			std::shared_ptr<Node> node;
			WorldData*data;
			cb(WorldData*data, std::shared_ptr<Node> node) : ICallbackItem(){
				this->node = node;
				this->data = data;
			}
			virtual void callback(void){
				data->byID[node->getNodeID()] = node;
				if (node->getNodeName().length()>0)
					data->byName[node->getNodeName()] = node;
			}
		};
		addCallback(std::shared_ptr<cb>(new cb(data, entity)));


		return entity;
	}//std::shared_ptr<Entity> World::createNewEntity(void)

	std::shared_ptr<Entity> World::createNewEntity(std::string name){
		std::shared_ptr<Entity> entity = std::shared_ptr<Entity>(new Entity());
		entity->setNodeName(name);

		class cb : public System::ICallbackItem{
		public:
			std::shared_ptr<Node> node;
			WorldData*data;
			cb(WorldData*data, std::shared_ptr<Node> node) : ICallbackItem(){
				this->node = node;
				this->data = data;
			}
			virtual void callback(void){
				data->byID[node->getNodeID()] = node;
				if (node->getNodeName().length()>0)
					data->byName[node->getNodeName()] = node;
			}
		};
		addCallback(std::shared_ptr<cb>(new cb(data, entity)));

		return entity;
	}//std::shared_ptr<Entity> World::createNewEntity(std::string name)

}//namespace World