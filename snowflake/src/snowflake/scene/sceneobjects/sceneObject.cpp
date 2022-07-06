#include "sfpch.h"
#include "SceneObject.h"

void SF::SceneObject::addChild(Ref<SceneObject> child) {

	child->m_Parent = this;
	m_Childs.push_back(child);

}

void SF::SceneObject::removeChild(Ref<SceneObject> child) {

	m_Childs.remove(child);

}

SF::SceneObject::SceneObject() {
	m_Parent = nullptr;
	m_Childs = std::list<Ref<SceneObject>>();
	m_Type = SceneObjectType::EMPTY;
}

SF::SceneObject::~SceneObject() {
}
