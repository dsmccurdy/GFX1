#ifndef ___ENTITY_H___
#define ___ENTITY_H___

#include "Node.h"

namespace World{

	namespace zzInternal{
		struct EntityData;
	}//namespace zzInternal

	typedef unsigned long AttributeID;

	class Entity:
		public Node{
	private:
		zzInternal::EntityData*data;
	public:

		Entity();
		virtual ~Entity();

		template<typename T>
		std::shared_ptr<T> getAttribute(AttributeID id);

		template<typename T>
		void setAttribute(AttributeID id, std::shared_ptr<T> attrib);

		bool hasAttribute(AttributeID id);

		static AttributeID getAttributeID(std::string name);
		static std::string getAttributeName(AttributeID id);

	};
}


#endif//___ENTITY_H___