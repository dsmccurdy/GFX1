#ifndef ___INODE_H___
#define ___INODE_H___

#include <vector>
#include <memory>

#include "Vector4f.h"
#include "Vector3f.h"
#include "Matrix.h"

namespace World{

	struct NodeData;

	enum NODE_TYPE{
		NT_UNKNOWN = 0,
		NT_NODE = 1,
		NT_ENTITY = 2,
		NT_OTHER = 0xFFFFFFFF
	};

	typedef unsigned long NodeID;

	class Node{
	private:

		NodeData*data;
		
	protected:

		void setNodeType(NODE_TYPE nt);

	public:

		Node();
		virtual ~Node();

		Math::Matrix getMatrix(void) const;

		Math::Vector3f getPosition() const;
		void setPosition(Math::Vector3f pos);

		Math::Vector3f getRotation() const;
		void setRotation(Math::Vector3f rot);

		Math::Vector3f getScale() const;
		void setScale(Math::Vector3f scale);

		void translate(Math::Vector3f trans);
		void translate(float x, float y, float z);

		void rotate(Math::Vector3f rot);
		void rotate(Math::Vector3f axis, float angle);
		void rotate(float x, float r, float z);
		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle);

		void scale(Math::Vector3f scale);
		void scale(float x, float y, float z);
		void scaleX(float s);
		void scaleY(float s);
		void scaleZ(float s);
		
		NODE_TYPE getNodeType(void) const;
		NodeID getNodeID(void) const;

		std::string getNodeName(void) const;
		void setNodeName(std::string name);

		std::vector<std::shared_ptr<Node>> getChildren(void) const;
		void addChild(std::shared_ptr <Node> child);
		void removeChild(std::shared_ptr <Node> child);
		bool isChild(std::shared_ptr<Node> node);

		std::shared_ptr<Node> getParent(void) const;
		void setParent(std::shared_ptr<Node> parent);

	};


}//namespace World


#endif//___INODE_H___