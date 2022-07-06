#pragma once
#include <glm.hpp>
#include <snowflake/core/core.h>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

namespace boost {

	namespace serialization {

		//GLM
		template<class Archive>
		void serialize(Archive& archive, glm::vec2& vec, const unsigned int version) {

			archive& vec.x;
			archive& vec.y;

		}

		template<class Archive>
		void serialize(Archive& archive, glm::vec3& vec, const unsigned int version) {

			archive& vec.x;
			archive& vec.y;
			archive& vec.z;

		}

		template<class Archive>
		void serialize(Archive& archive, glm::vec4& vec, const unsigned int version) {

			archive& vec.x;
			archive& vec.y;
			archive& vec.z;
			archive& vec.w;

		}

		template<class Archive>
		void serialize(Archive& archive, glm::mat2& mat, const unsigned int version) {

			archive& mat[0];
			archive& mat[1];

		}

		template<class Archive>
		void serialize(Archive& archive, glm::mat3& mat, const unsigned int version) {

			archive& mat[0];
			archive& mat[1];
			archive& mat[2];

		}

		template<class Archive>
		void serialize(Archive& archive, glm::mat4& mat, const unsigned int version) {

			archive& mat[0];
			archive& mat[1];
			archive& mat[2];
			archive& mat[3];

		}

	}

}