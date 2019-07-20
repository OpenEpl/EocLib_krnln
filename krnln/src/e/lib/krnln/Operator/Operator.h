#pragma once
//这是一个只有上帝能看懂的文件
//计划重写中......
#include <e/system/basic_type.h>
#pragma push_macro("ProcessObjectOperator")
#pragma push_macro("DefineOperator_ProcessNumber_L")
#pragma push_macro("DefineOperator_ProcessNumber_R")
#pragma push_macro("DefineOperator_ProcessNumber_A")
#pragma push_macro("DefineOperator")
#pragma push_macro("DefineComparisonOperator")
#pragma push_macro("DefineEqualOperator")
#pragma push_macro("DefineMulitOperandOperator")
#pragma push_macro("DefineOperator_BetweenAny")
#undef ProcessObjectOperator
#undef DefineOperator_ProcessNumber_L
#undef DefineOperator_ProcessNumber_R
#undef DefineOperator_ProcessNumber_A
#undef DefineOperator
#undef DefineComparisonOperator
#undef DefineEqualOperator
#undef DefineMulitOperandOperator
#undef DefineOperator_BetweenAny
namespace e
{
	namespace lib
	{
		namespace krnln
		{

#define ProcessObjectOperator(PT, op) if (a.type() == typeid(PT)) return a.cast<PT>() op b.cast<PT>()

#define DefineOperator_ProcessNumber_L(PT, name) if (a.type() == typeid(PT)) return name(a.cast<PT>(), b)
#define DefineOperator_ProcessNumber_R(PT, name) if (b.type() == typeid(PT)) return name(a, b.cast<PT>())
#define DefineOperator_ProcessNumber_A(PT, name) if (a.type() == typeid(PT)) return name<PT>(a.cast<PT>(), b)
#define DefineOperator_BetweenAny(name, nameForAnyNumber, isBoolResult)\
	template<class R, \
		std::enable_if_t<std::is_arithmetic_v<R>, int> = 0> \
		static auto name(const e::system::any & a, R b)\
		-> std::conditional_t<isBoolResult, bool, e::system::any>\
	{\
		DefineOperator_ProcessNumber_L(int32_t, name);\
		DefineOperator_ProcessNumber_L(double, name);\
		DefineOperator_ProcessNumber_L(uint8_t, name);\
		DefineOperator_ProcessNumber_L(int16_t, name);\
		DefineOperator_ProcessNumber_L(int64_t, name);\
		DefineOperator_ProcessNumber_L(float, name);\
		throw std::exception{};\
	}\
	template<class L, \
		std::enable_if_t<std::is_arithmetic_v<L>, int> = 0> \
		static auto name(L a, const e::system::any & b)\
		-> std::conditional_t<isBoolResult, bool, e::system::any>\
	{\
		DefineOperator_ProcessNumber_R(int32_t, name);\
		DefineOperator_ProcessNumber_R(double, name);\
		DefineOperator_ProcessNumber_R(uint8_t, name);\
		DefineOperator_ProcessNumber_R(int16_t, name);\
		DefineOperator_ProcessNumber_R(int64_t, name);\
		DefineOperator_ProcessNumber_R(float, name);\
		throw std::exception{};\
	}\
	template<class R, \
		std::enable_if_t<!std::is_arithmetic_v<R>, int> = 0> \
		static auto name(const e::system::any & a, R b)\
	{\
		return name(a.cast<R>(), b);\
	}\
	template<class L, \
		std::enable_if_t<!std::is_arithmetic_v<L>, int> = 0> \
		static auto name(L a, const e::system::any & b)\
	{\
		return name(a, b.cast<L>());\
	}\
	static auto nameForAnyNumber(const e::system::any & a, const e::system::any & b)\
		-> std::conditional_t<isBoolResult, bool, e::system::any>\
	{\
		DefineOperator_ProcessNumber_A(int32_t, name); \
		DefineOperator_ProcessNumber_A(double, name); \
		DefineOperator_ProcessNumber_A(uint8_t, name); \
		DefineOperator_ProcessNumber_A(int16_t, name); \
		DefineOperator_ProcessNumber_A(int16_t, name); \
		DefineOperator_ProcessNumber_A(int64_t, name); \
		DefineOperator_ProcessNumber_A(float, name); \
		throw std::exception{}; \
	}

#define DefineOperator(name, op, nameForAnyNumber, isBoolResult)\
	template<class L, class R, \
		std::enable_if_t<!std::is_same_v<L, e::system::any> && !std::is_same_v<R, e::system::any>, int> = 0> \
		static auto name(L a, R b)\
	{\
		return a op b;\
	}\
	DefineOperator_BetweenAny(name, nameForAnyNumber, isBoolResult)

#define DefineComparisonOperator(name, op)\
	DefineOperator(name, op, Number##name, true);\
	bool static name(const e::system::any& a, const e::system::any& b)\
	{\
		ProcessObjectOperator(e::system::string, op);\
		ProcessObjectOperator(e::system::datetime, op);\
		ProcessObjectOperator(bool, op);\
		return Number##name(a, b);\
	}

#define DefineEqualOperator(name, op)\
	DefineOperator(name, op, Number##name, true);\
	bool static name(const e::system::any& a, const e::system::any& b)\
	{\
		ProcessObjectOperator(e::system::string, op);\
		ProcessObjectOperator(e::system::datetime, op);\
		ProcessObjectOperator(bool, op);\
		ProcessObjectOperator(e::system::methodptr, op);\
		ProcessObjectOperator(e::system::bin, op); \
		return Number##name(a, b);\
	}


#define DefineMulitOperandOperator(name)\
	template<typename T>\
		static e::system::any name(T a)\
	{\
		return a; \
	}\
		template<typename TA, typename TB, typename TC, typename... TX>\
		static e::system::any name(TA a, TB b, TC c, TX... x)\
	{\
		e::system::any r = name(a, b); \
		r = name(r, c); \
		r = name(r, x...); \
		return r; \
	}


			DefineOperator(Add, +, NumberAdd, false);
			DefineOperator(Sub, -, NumberSub, false);
			DefineOperator(Mul, *, Mul, false);

			DefineComparisonOperator(GreaterThan, > );
			DefineComparisonOperator(GreaterThanOrEqual, >= );
			DefineComparisonOperator(LessThan, < );
			DefineComparisonOperator(LessThanOrEqual, <= );

			DefineEqualOperator(Equal, == );
			DefineEqualOperator(Unequal, != );
			static e::system::any Add(const e::system::any & a, const e::system::any & b)
			{
				ProcessObjectOperator(e::system::string, +);
				ProcessObjectOperator(e::system::datetime, +);
				ProcessObjectOperator(e::system::bin, +);
				return NumberAdd(a, b);
			}
			static e::system::any Sub(const e::system::any & a, const e::system::any & b)
			{
				ProcessObjectOperator(e::system::datetime, -);
				return NumberSub(a, b);
			}

			template<class L, class R,
				std::enable_if_t<std::is_integral_v<L> && std::is_integral_v<R>, int> = 0>
				static auto Mod(L a, R b)
			{
				return a % b;
			}
			template<class L, class R,
				std::enable_if_t<std::is_arithmetic_v<L> && std::is_arithmetic_v<R> && (std::is_floating_point_v<L> || std::is_floating_point_v<R>), int> = 0>
				static auto Mod(L a, R b)
			{
				return std::fmod(a, b);
			}
			DefineOperator_BetweenAny(Mod, Mod, true);

			template<class L, class R,
				std::enable_if_t<std::is_integral_v<L> && std::is_integral_v<R>, int> = 0>
				static auto IDiv(L a, R b)
			{
				return a / b;
			}
			template<class L, class R,
				std::enable_if_t<std::is_arithmetic_v<L> && std::is_arithmetic_v<R> && (std::is_floating_point_v<L> || std::is_floating_point_v<R>), int> = 0>
				static auto IDiv(L a, R b)
			{
				auto r = a / b;
				decltype(r) intpart;
				std::modf(r, &intpart);
				return intpart;
			}
			DefineOperator_BetweenAny(IDiv, IDiv, true);

			template<class L, class R,
				std::enable_if_t<std::is_integral_v<L> && std::is_integral_v<R>, int> = 0>
				static auto Div(L a, R b)
			{
				return (double)a / b;
			}
			template<class L, class R,
				std::enable_if_t<std::is_arithmetic_v<L> && std::is_arithmetic_v<R> && (std::is_floating_point_v<L> || std::is_floating_point_v<R>), int> = 0>
				static auto Div(L a, R b)
			{
				return a / b;
			}
			DefineOperator_BetweenAny(Div, Div, true);

			DefineMulitOperandOperator(Add);
			DefineMulitOperandOperator(Sub);
			DefineMulitOperandOperator(Mul);
			DefineMulitOperandOperator(Mod);
			DefineMulitOperandOperator(IDiv);
			DefineMulitOperandOperator(Div);

			template<class T,
				std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
				static T Neg(T value)
			{
				return -value;
			}

			static e::system::any Neg(const e::system::any &value)
			{
				if (value.type() == typeid(uint8_t))
				{
					return Neg(value.cast<uint8_t>());
				}
				if (value.type() == typeid(int16_t))
				{
					return Neg(value.cast<int16_t>());
				}
				if (value.type() == typeid(int32_t))
				{
					return Neg(value.cast<int32_t>());
				}
				if (value.type() == typeid(int64_t))
				{
					return Neg(value.cast<int64_t>());
				}
				if (value.type() == typeid(double))
				{
					return Neg(value.cast<double>());
				}
				if (value.type() == typeid(float))
				{
					return Neg(value.cast<float>());
				}
			}
		}
	}
}
#pragma pop_macro("DefineOperator_BetweenAny")
#pragma pop_macro("DefineMulitOperandOperator")
#pragma pop_macro("DefineEqualOperator")
#pragma pop_macro("DefineComparisonOperator")
#pragma pop_macro("DefineOperator")
#pragma pop_macro("DefineOperator_ProcessNumber_A")
#pragma pop_macro("DefineOperator_ProcessNumber_R")
#pragma pop_macro("DefineOperator_ProcessNumber_L")
#pragma pop_macro("ProcessObjectOperator")
