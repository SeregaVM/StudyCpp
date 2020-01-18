/* Type decorator for variant.
 * @file
 * @date 2018-08-15
 * @author Anonymous
 */

#ifndef __VARIANT_DECORATOR_HPP__
#define __VARIANT_DECORATOR_HPP__

#include <boost/spirit/home/x3/support/ast/variant.hpp>

namespace x3 = boost::spirit::x3;

//? How to inherit x3::variant constructor & ``operator=``?
//? Why I need inherited constructor & ``operator=``?
//? How many constructors did I inherit?
//? Do I need my own constructor & ``operator=``? Why?
//{
template<typename ...Ts>
struct variant_decorator: public x3::variant<Ts...>
{
    using variant_decorator::variant::variant;
    using variant_decorator::variant::operator=;
    variant_decorator(const variant_decorator& var) = default;
    variant_decorator& operator=(const variant_decorator& var) = default;
    //? Do I need a ``const``-version?
    template<class T>
    T& as()
    {
        return boost::get<T>(*this);
    }

    template<class T>
    const T& as() const
    {
        return boost::get<T>(*this);
    }
};
//}

#endif // __VARIANT_DECORATOR_HPP__
