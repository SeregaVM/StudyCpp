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
ostream& endm(ostream& stream){ return stream << "[eol]\n"; }


//--------------squares----------------------------//
struct temp_sq_1{} squares;
struct temp_sq_2{ ostream& stream;};

temp_sq_2 operator<<(ostream& stream, temp_sq_1){ return {stream};}
template <typename T>
ostream& operator<<(temp_sq_2 temp, T data){ return temp.stream << '[' << data << ']'; }


//-----------add-----------------------------------//
struct temp_add {} add;
struct temp_add_1 {ostream& stream; };
template<typename T> 
struct temp_add_2 {ostream& stream; T data; };

temp_add_1 operator<< (ostream& stream, temp_add){return {stream}; }
template<typename T> 
temp_add_2<T> operator<< (temp_add_1 temp, T data){ return{temp.stream, data}; }
template<typename T>
ostream& operator<< (temp_add_2<T> temp, T data){ return temp.stream << temp.data + data; }

#endif // __IOMANIP_HPP__