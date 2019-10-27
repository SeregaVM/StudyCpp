/* Custom manipulators.
 * @file
 * @date 2019-10-20
 * @author Serega
 */

#ifndef __IOMANIP_HPP__
#define __IOMANIP_HPP__

#include <iostream>

using namespace std;

//----------------endm-----------------------------//
ostream& endm(ostream& stream)
{
	stream << "[eol]\n";
	return stream;
}
//-------------------------------------------------//


//--------------squares----------------------------//

struct temp_sq {} squares;
streambuf* buff;

temp_sq& operator << (ostream& stream, temp_sq)
{
	buff = stream.rdbuf();
	return squares;
}
template <typename T>
ostream& operator << (temp_sq, T str)
{
	static ostream res(buff);
	res << "[" << str << "]";
	return res;
}
//-------------------------------------------------//

//-----------add-----------------------------------//
struct temp_add_1 {}add;

template <typename T>
struct temp_add_2 {
	T temp;
};
template <typename T>
temp_add_2<T> add_2;
 

 temp_add_1& operator << (ostream& stream, temp_add_1){
	 buff = stream.rdbuf();
	 return add;
 }

template <typename T>
temp_add_2<T>& operator << (temp_add_1,T temp){
	add_2<T>.temp = temp;
	return add_2<T>;
}

template <typename T>
ostream& operator << (temp_add_2<T> t_add, T temp ){
	static ostream str(buff);
	str.flush();
	str << (t_add.temp + temp);
	return str;
}
//-------------------------------------------------//

#endif // __IOMANIP_HPP__