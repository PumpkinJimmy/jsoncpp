#pragma once
#include <string>
#include <type_traits>

class Any
{
public:
	Any() :m_data(nullptr) {}
	template <typename T>
	Any(const T& data):is_array(false) {
		m_data = new T(data);
	}
	template <typename T>
	Any(T&& data):is_array(false) {
		m_data = new T(std::move(data));
	}

	template <typename T>
	Any& operator=(const T& new_data) {
		if (m_data) delete m_data;
		m_data = new T(new_data);
		is_array = false;
		return *this;
	}
	

	template <typename T>
	Any& operator=(T&& new_data) {
		if (m_data) delete m_data;
		m_data = new T(std::move(new_data));
		is_array = false;
		return *this;
	}

	template <typename T, size_t N>
	Any& operator=(T(&new_data)[N]) {
		if (m_data) delete m_data;
		m_data = new std::remove_cv_t<T>[N];
		memcpy(m_data, new_data, N);
		is_array = true;
		return *this;
	}

	~Any() {
		if (m_data) {
			if (is_array)
				delete[] m_data;
			else delete m_data;
		}
	}



	template <typename T>
	T get() {
		return *((T*)m_data);
	}

	template <typename T>
	std::enable_if_t<
		std::is_array_v<T>,
		std::remove_all_extents_t<T>*
	> get(){
		return (std::remove_all_extents_t<T>*)m_data;
	}

	template <>
	std::string get<std::string>() {
		return std::string((char*)m_data);
	}

private:
	void* m_data;
	bool is_array = false;
};