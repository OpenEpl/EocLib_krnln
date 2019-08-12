#pragma once
#include <e/system/basic_type.h>
namespace e
{
	namespace lib
	{
		namespace krnln
		{
			int32_t ToInt32(const e::system::any &value);
			template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0> inline int32_t ToInt32(T value)
			{
				return static_cast<int32_t>(value);
			}
			inline int32_t ToInt32(bool value)
			{
				return value ? 1 : 0;
			}
			inline int32_t ToInt32(const e::system::string &value)
			{
				return atoi(value.c_str());
			}
			inline int32_t ToInt32(e::system::methodptr value)
			{
				return static_cast<int32_t>(reinterpret_cast<intptr_t>(value));
			}

			int16_t ToInt16(const e::system::any &value);
			template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0> inline int16_t ToInt16(T value)
			{
				return static_cast<int16_t>(value);
			}
			inline int16_t ToInt16(bool value)
			{
				return value ? 1 : 0;
			}
			inline int16_t ToInt16(const e::system::string &value)
			{
				return static_cast<int16_t>(atoi(value.c_str()));
			}
			inline int16_t ToInt16(e::system::methodptr value)
			{
				return static_cast<int16_t>(reinterpret_cast<intptr_t>(value));
			}

			int64_t ToInt64(const e::system::any &value);
			template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0> inline int64_t ToInt64(T value)
			{
				return static_cast<int64_t>(value);
			}
			inline int64_t ToInt64(bool value)
			{
				return value ? 1i64 : 0i64;
			}
			inline int64_t ToInt64(const e::system::string &value)
			{
				return atoll(value.c_str());
			}
			inline int64_t ToInt64(e::system::methodptr value)
			{
				return static_cast<int64_t>(reinterpret_cast<intptr_t>(value));
			}

			intptr_t ToIntPtr(const e::system::any &value);
			template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0> inline intptr_t ToIntPtr(T value)
			{
				return static_cast<intptr_t>(value);
			}
			inline intptr_t ToIntPtr(bool value)
			{
				return ToIntPtr(value ? 1 : 0);
			}
			inline intptr_t ToIntPtr(const e::system::string &value)
			{
				return ToIntPtr(atoll(value.c_str()));
			}
			inline intptr_t ToIntPtr(e::system::methodptr value)
			{
				return reinterpret_cast<intptr_t>(value);
			}

			uint8_t ToUInt8(const e::system::any &value);
			template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0> inline uint8_t ToUInt8(T value)
			{
				return static_cast<uint8_t>(value);
			}
			inline uint8_t ToUInt8(bool value)
			{
				return value ? 1 : 0;
			}
			inline uint8_t ToUInt8(const e::system::string &value)
			{
				return static_cast<uint8_t>(atoi(value.c_str()));
			}
			inline uint8_t ToUInt8(e::system::methodptr value)
			{
				return static_cast<uint8_t>(reinterpret_cast<intptr_t>(value));
			}

			double ToDouble(const e::system::any &value);
			template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0> inline double ToDouble(T value)
			{
				return static_cast<double>(value);
			}
			inline double ToDouble(bool value)
			{
				return value ? 1.0 : 0.0;
			}
			inline double ToDouble(const e::system::string &value)
			{
				return atof(value.c_str());
			}
			inline double ToDouble(e::system::methodptr value)
			{
				return static_cast<double>(reinterpret_cast<intptr_t>(value));
			}

			float ToFloat(const e::system::any &value);
			template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0> inline float ToFloat(T value)
			{
				return static_cast<float>(value);
			}
			inline float ToFloat(bool value)
			{
				return value ? 1.0f : 0.0f;
			}
			inline float ToFloat(const e::system::string &value)
			{
				return static_cast<float>(atof(value.c_str()));
			}
			inline float ToFloat(e::system::methodptr value)
			{
				return static_cast<float>(reinterpret_cast<intptr_t>(value));
			}
			template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0> inline e::system::bin ToBin(T value)
			{
				return e::system::make_bin(&value, sizeof(value));
			}
			e::system::bin ToBin(const e::system::any &value);
			e::system::bin ToBin(const e::system::bin& value);
			e::system::bin ToBin(bool value);
			e::system::bin ToBin(e::system::datetime value);
			e::system::bin ToBin(const e::system::string &value);
			e::system::bin ToBin(e::system::methodptr value);

			e::system::string ToString(uint8_t value);
			e::system::string ToString(int16_t value);
			e::system::string ToString(int32_t value);
			e::system::string ToString(int64_t value);
			e::system::string ToString(float value);
			e::system::string ToString(double value);
			e::system::string ToString(bool value);
			e::system::string ToString(e::system::datetime value);
			e::system::string ToString(uint8_t value);
			template <typename TElem>
			e::system::string ToString(const e::system::basic_array<TElem> &value)
			{
				auto length = value.GetSize() * sizeof(TElem);
				if (length == 0)
					return nullptr;
				e::system::string result(length);
				std::memcpy(result.c_str(), value.GetElemPtr(), length);
				result.c_str()[length] = '\0';
				return result;
			}
			inline e::system::string ToString(const e::system::string &value)
			{
				return value;
			}
			e::system::string ToString(const e::system::any &value);
		}
	}
}