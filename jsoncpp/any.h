#pragma once
#include <string>
class Any
{
public:
	Any() :m_data(nullptr) {}
	template <typename T>
	Any(const T& data) {
		m_data = new T(data);
	}
	template <typename T>
	Any(T&& data) {
		m_data = new T(std::move(data));
	}
	template <typename T>
	Any& operator=(const T& new_data) {
		if (m_data) delete m_data;
		m_data = new T(new_data);
		return *this;
	}
	using ccstr = const char*;
	using ccstr_ref = const ccstr&;
	template <>
	Any& operator=<ccstr_ref>(ccstr_ref new_data) {
		if (m_data) delete m_data;
		m_data = new std::string(new_data);
		return *this;
	}

	template <typename T>
	Any& operator=(T&& new_data) {
		if (m_data) delete m_data;
		m_data = new T(std::move(new_data));
		return *this;
	}
	~Any() {
		if (m_data) delete m_data;
	}

	template <typename T>
	T get() {
		return *((T*)m_data);
	}

private:
	void* m_data;
};