#pragma once
#include "sceneobjects/sceneObject.h"
#include "sceneobjects/renderableObject.h"
#include "sceneobjects/cameraObject.h"
#include <algorithm>
#include <list>
#include <iterator>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/list.hpp>

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

		//serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& archive, const unsigned int version)
		{
			archive& m_SceneObjects;
			archive& m_CameraObject;
		}

	public:
		Scene() {

		}
		~Scene() {}

		void update() {}

		void addObject(Ref<SceneObject> object) { m_SceneObjects.push_back(object); }
		void setCameraObject(Ref<CameraObject> cam) {
			std::list<Ref<SceneObject>>::iterator findIter = std::find(m_SceneObjects.begin(), m_SceneObjects.end(), cam);
			if (findIter == m_SceneObjects.end())
				addObject(cam);

			m_CameraObject = cam;

		}

		Ref<CameraObject> getCamera() { 

			return m_CameraObject;

		}

		SceneIterator begin() { return SceneIterator(m_SceneObjects.begin()); }
		SceneIterator end() { return SceneIterator(m_SceneObjects.end()); }

	};

}