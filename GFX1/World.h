#ifndef ___WORLD_H___
#define ___WORLD_H___

#include "ISubSystem.h"
#include "Node.h"
#include "Entity.h"
#include "CallbackQueue.h"

namespace World{

	struct WorldData;

	class World :
		//public System::ISubSystem,
		public System::CallbackQueue{
	private:
		WorldData*data;
	public:

		World();
		virtual ~World();

		virtual void initalizeStage1(void);
		virtual void startWritePhase(void);

		std::shared_ptr<Node> getRootNode(void) const;

		std::shared_ptr<Node> getNodeByName(std::string name) const;
		std::shared_ptr<Node> getNodeByID(NodeID id) const;

		std::shared_ptr<Node> createNewNode(void);
		std::shared_ptr<Node> createNewNode(std::string name);

		std::shared_ptr<Entity> createNewEntity(void);
		std::shared_ptr<Entity> createNewEntity(std::string name);


	};


}//namespace World

#endif//___WORLD_H___