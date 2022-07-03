#pragma once
#include "sceneobjects/sceneObject.h"
#include "sceneobjects/renderableObject.h"
#include "sceneobjects/cameraObject.h"
#include <algorithm>
#include <list>
#include <iterator>

namespace SF {

	struct SceneIterator {
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = Ref<SceneObject>;
		using pointer = Ref<SceneObject>*;
		using reference = Ref<SceneObject>&;

		SceneIterator(std::list<Ref<SceneObject>>::iterator it) : it(it) {}

		reference operator*() const { return *it; }
		pointer operator->() { return &(*it); }

		SceneIterator& operator++() { it++; return *this; }

		SceneIterator operator++(int) { SceneIterator tmp = *this; ++(*this); return tmp; }

		friend bool operator== (const SceneIterator& a, const SceneIterator& b) { return a.it == b.it; };
		friend bool operator!= (const SceneIterator& a, const SceneIterator& b) { return a.it != b.it; };


	private:
		std::list<Ref<SceneObject>>::iterator it;
	};


	class Scene {
	private:


		std::list<Ref<SceneObject>> m_SceneObjects;
		Ref<CameraObject> m_CameraObject;

	public:
		Scene() {

		}
		~Scene() {}

		void update() {}

		void addObject(Ref<SceneObject> object) { m_SceneObjects.push_back(object); }
		void setCameraObject(Ref<CameraObject> cam) {
			bool found = (std::find(m_SceneObjects.begin(), m_SceneObjects.end(), cam) != m_SceneObjects.end());
			if (!found)
				addObject(cam);
			m_CameraObject = cam;
		}

		Ref<CameraObject>& getCamera() { return m_CameraObject; }

		SceneIterator begin() { return SceneIterator(m_SceneObjects.begin()); }
		SceneIterator end() { return SceneIterator(m_SceneObjects.end()); }

	};

}