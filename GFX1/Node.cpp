#include "Node.h"

#include <atomic>


namespace World{

	struct NodeData{
		Math::Vector4f position = Math::Vector4f(0.0f,0.0f,0.0f,1.0f);
		Math::Vector3f rotation =  Math::Vector3f(0.0f,0.0f,0.0f);
		Math::Vector3f scale = Math::Vector3f(1.0f,1.0f,1.0f);

		NODE_TYPE nodeType = NODE_TYPE::NT_UNKNOWN;
		NodeID nodeID;
		std::string name = nullptr;

		std::vector<std::shared_ptr<Node>> children;
		std::shared_ptr<Node> parent = nullptr;
	};
	static std::atomic<NodeID> g_nodeID = 1;

	Node::Node(){
		data = new NodeData();
		data->nodeID = g_nodeID.fetch_add(1);
		data->nodeType = NODE_TYPE::NT_NODE;
	}//Node::Node()
	
	Node::~Node(){
		delete data;
	}//Node::~Node()

	Math::Matrix Node::getMatrix(void) const{
		return Math::Matrix();
	}

	Math::Vector3f Node::getPosition() const{
		return data->position;
	}//Math::Vector3f Node::getPosition() const

	void Node::setPosition(Math::Vector3f pos){
		data->position = pos;
	}//void Node::setPosition(Math::Vector3f pos)

	Math::Vector3f Node::getRotation() const{
		return data->rotation;
	}//Math::Vector3f Node::getRotation() const

	void Node::setRotation(Math::Vector3f rot){
		data->rotation = rot;
	}//void Node::setRotation(Math::Vector3f pos)

	Math::Vector3f Node::getScale() const{
		return data->scale;
	}//Math::Vector3f Node::getScale() const

	void Node::setScale(Math::Vector3f scale){
		data->scale = scale;
	}//void Node::setScale(Math::Vector3f pos)

	void Node::translate(Math::Vector3f trans){

	}//void Node::translate(Math::Vector3f trans)

	void Node::translate(float x, float y, float z){

	}//void Node::translate(float x, float y, float z)

	void Node::rotate(Math::Vector3f rot){

	}//void Node::rotate(Math::Vector3f rot)

	void Node::rotate(Math::Vector3f axis, float angle){

	}//void Node::rotate(Math::Vector3f axis, float angle)

	void Node::rotate(float x, float r, float z){

	}//void Node::rotate(float x, float r, float z)

	void Node::rotateX(float angle){

	}//void Node::rotateX(float angle)

	void Node::rotateY(float angle){

	}//void Node::rotateY(float angle)

	void Node::rotateZ(float angle){

	}//void Node::rotateZ(float angle)

	void Node::scale(Math::Vector3f scale){

	}//void Node::scale(Math::Vector3f scale)

	void Node::scale(float x, float y, float z){

	}//void Node::scale(float x, float y, float z)

	void Node::scaleX(float s){

	}//void Node::scaleX(float s)

	void Node::scaleY(float s){

	}//void Node::scaleY(float s)

	void Node::scaleZ(float s){

	}//void Node::scaleZ(float s)

	NODE_TYPE Node::getNodeType(void) const{
		return data->nodeType;
	}//NODE_TYPE Node::getNodeType(void) const

	void Node::setNodeType(NODE_TYPE nt){
		data->nodeType = nt;
	}//void Node::setNodeType(NODE_TYPE nt)

	NodeID Node::getNodeID(void) const{
		return data->nodeID;
	}//NodeID Node::getNodeID(void) const

	std::string Node::getNodeName(void) const{
		return data->name;
	}//std::string Node::getNodeName(void) const

	void Node::setNodeName(std::string name){
		data->name = name;
	}//void Node::setNodeName(std::string name)

	std::vector<std::shared_ptr<Node>> Node::getChildren(void) const{
		return std::vector<std::shared_ptr<Node>>(data->children);
	}//std::vector<std::shared_ptr<Node>> Node::getChildren(void) const

	void Node::addChild(std::shared_ptr <Node> child){
		data->children.push_back(child);
	}//void Node::addChild(std::shared_ptr <Node> child)

	void Node::removeChild(std::shared_ptr <Node> child){
		std::vector<std::shared_ptr<Node>>::iterator it;
		it = find(data->children.begin(), data->children.end(), child);
		if (it != data->children.end()){
			data->children.erase(it);
		}
	}//void Node::removeChild(std::shared_ptr <Node> child)

	bool Node::isChild(std::shared_ptr<Node> node){
		std::vector<std::shared_ptr<Node>>::iterator it;
		it = find(data->children.begin(), data->children.end(), node);
		return it != data->children.end();
	}//bool Node::isChild(std::shared_ptr<Node> node)

	std::shared_ptr<Node> Node::getParent(void) const{
		return data->parent;
	}//std::shared_ptr<Node> Node::getParent(void) const

	void Node::setParent(std::shared_ptr<Node> parent){
		data->parent = parent;
	}//void Node::setParent(std::shared_ptr<Node> parent)

};//namespace World