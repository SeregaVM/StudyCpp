/* Json object.
 * @file
 * @date 2018-08-09
 * @author Anonymous
 */

#ifndef __JSON_HPP__
#define __JSON_HPP__

#include <map>
#include <string>
#include <vector>

#include <boost/spirit/home/x3.hpp>
//? Why I need ``std_pair`` header? Do I need one for std::map?
#include <boost/fusion/adapted/std_pair.hpp>

#include "parser.hpp"
#include "quoted_string.hpp"
#include "variant_decorator.hpp"

/* Json EBNF specification (https://www.json.org)
 *      string := \" ([^\"] | \\\")* \"
 *      number := [0-9]+(\.[0-9]*)?
 *      boolean := "true" | "false"
 *      nullable := "null"
 *      value := number | string | boolean | nullable | array | object
 *      array := '[' value (',' value)* ']'
 *      key_value := string ':' value
 *      object := '{' key_value (',' key_value)* '}'
 *      json := array | object
 */

namespace types
{
    namespace json
    {
        //{ describe json data types
        struct value;
        using array = std::vector<value>;
        using object = std::map<std::string, value>;

        using json = variant_decorator<array, object>;

        struct value : public variant_decorator<int, float, std::string, bool, std::nullptr_t, array, object>
        {
             using variant_decorator::variant_decorator;
             using variant_decorator::operator=;
        };
        //}
    }
}

namespace parser
{
    namespace json
    {
        //? Why I need ``sfloat_`` instead of just ``x3::float_``?
        //? What is the syntax ``class array_``? Is it wrong?
        const auto sfloat_ = x3::real_parser<float, x3::strict_real_policies<float>>();

        //{ describe json grammar
        auto number = sfloat_ | x3::int_;
        auto nullable = x3::rule<class nullable, std::nullptr_t>{} 
                      = "null" > x3::attr(nullptr);

        x3::rule<class array, types::json::array> const array = "array";
        x3::rule<class object, types::json::object> const object = "object";
        x3::rule<class json, types::json::json> json = "json";

        auto value = x3::rule<class value, types::json::value>{}
                   =  array | object | number | quoted_string | x3::bool_ | nullable;

        auto key_value = x3::rule<class key_value, std::pair<std::string, types::json::value>>{}
                       = quoted_string > ':' > value;

        auto const array_def  = '[' > -(value % ',') > ']';
        auto const object_def = '{' > -(key_value % ',') > '}';
        auto const json_def = array | object;
        //}

        BOOST_SPIRIT_DEFINE(array, object, json)
    }
}

namespace literals
{
    namespace json
    {
        //{ describe ``_json`` literal
        types::json::json operator ""_json(const char* str, long unsigned int)
        {   
            return parser::load_from_string<types::json::json>(str, parser::json::json);
        }
        //}
    }
}

#endif // __JSON_HPP__
