/* Variant classes.
 * @file
 * @date 2020-01-17
 * @author Serega
 */

#ifndef __VARIANT_HPP__
#define __VARIANT_HPP__

#include <map>
#include <memory>
#include <variant>
#include <vector>

#include <boost/variant.hpp>

//{ number
struct number : public std::variant<int, float>
{
    using variant::variant;
};
//}

//{ array
struct array : public std::vector <std::variant<int, float>>
{
    using vector::vector;
};
//}

//{ recursive_array
struct recursive_array : std::vector<std::variant<number, std::shared_ptr<recursive_array>>>
{
    using vector::vector;
};
//}

//{ recursive_array2
struct recursive_array2 : std::vector<std::variant<number, boost::recursive_wrapper<recursive_array2>>>
{
    using vector::vector;
};
//}

//{ variant_decorator
template<typename ...Ts>
struct variant_decorator : public std::variant<Ts...>
{
	variant_decorator() = default;
	template<typename Arg>
	variant_decorator(Arg arg) : std::variant<Ts...>(arg){}

    template<typename U>
	const U& as() const
	{
		if constexpr (std::disjunction_v<std::is_same<U, Ts>...>)
		{
			return std::get<U>(*this);
		}
		else 
		{
			return std::get<boost::recursive_wrapper<U>>(*this).get();
		}
	}

	template<typename U>
	U& as() 
	{
		return const_cast<U&>(static_cast<const variant_decorator<Ts...>&>(*this).as<U>());
	}
};
//}

//{ recursive_map
struct recursive_map : public std::map<std::string, variant_decorator<std::string, int, bool, boost::recursive_wrapper<recursive_map>>> 
{
    using map::map;
};
//}

#endif // __VARIANT_HPP__
