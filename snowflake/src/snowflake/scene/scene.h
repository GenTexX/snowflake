#pragma once
#include "sceneobjects/sceneObject.h"
#include "sceneobjects/renderableObject.h"
#include "sceneobjects/cameraObject.h"
#include "sceneSerialization.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>

#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>

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
		std::string m_SceneFile;
		std::list<Ref<SceneObject>> m_SceneObjects;
		Ref<SceneObject> m_CameraObject;

		//serialization
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(m_SceneObjects));
			archive(CEREAL_NVP(m_CameraObject));
		}

	public:
		Scene(const std::string& sceneFile) {
			m_SceneFile = sceneFile;
		}
		~Scene() {}

		void save() {

			try {
				std::ofstream ofs(m_SceneFile, std::ios::binary);
				cereal::XMLOutputArchive oa(ofs);

				oa(*this);
			} catch (std::exception e) {
				SF_CORE_ERROR(e.what());
			}

		}
		void load() {

			try {
				{
					std::ifstream ifs(m_SceneFile, std::ios::binary);
					cereal::XMLInputArchive ia(ifs);
					ia(*this);
				}
			} catch (std::exception e) {
				SF_CORE_ERROR(e.what());
			}

		}

		void update() {
		
			for (auto object : m_SceneObjects)
			{
				object->update();
			}

		}

		void addObject(Ref<SceneObject> object) { m_SceneObjects.push_back(object); }
		void setCameraObject(Ref<CameraObject> cam) {
			std::list<Ref<SceneObject>>::iterator findIter = std::find(m_SceneObjects.begin(), m_SceneObjects.end(), cam);
			if (findIter == m_SceneObjects.end())
				addObject(cam);

			m_CameraObject = cam;

		}

		Ref<CameraObject> getCamera() { 

			return std::static_pointer_cast<CameraObject>(m_CameraObject);

		}

		SceneIterator begin() { return SceneIterator(m_SceneObjects.begin()); }
		SceneIterator end() { return SceneIterator(m_SceneObjects.end()); }

	};

}