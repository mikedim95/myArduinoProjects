
#pragma once

#include <string>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/algorithm/string.hpp>


namespace boost {

namespace detail{

struct is_base64_char {
  bool operator()(char x) { return boost::is_any_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+/=")(x);}
};

}


typedef	archive::iterators::transform_width< 
			archive::iterators::binary_from_base64<filter_iterator<detail::is_base64_char, std::string::iterator> >, 8, 6, char>
				base64decodeIterator;

// BASE64 解码.
template<typename Char>
std::basic_string<Char> base64_decode(std::basic_string<Char> str)
{
	// convert base64 characters to binary values
	std::basic_string<Char> result(base64decodeIterator(str.begin()) , base64decodeIterator(str.end()));
	return result.c_str();
}

}
