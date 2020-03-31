#pragma once

namespace SF {

	class Platform {

	private:
		static std::unique_ptr<Platform> s_Instance;

	protected:
		virtual float getTimeImpl() = 0;

	public:

		Platform() = default;

		Platform(const Platform&) = delete;
		Platform& operator=(const Platform&) = delete;

		~Platform();

		static std::unique_ptr<Platform> create();

		static float getTime() { return s_Instance->getTimeImpl(); };

	};
}