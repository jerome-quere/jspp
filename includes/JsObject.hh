/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Jerome Quere <contact@jeromequere.com>
 *
 * Permission is hereby granted, free  of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction,  including without limitation the rights
 * to use,  copy,  modify,  merge, publish,  distribute, sublicense, and/or sell
 * copies  of  the  Software,  and  to  permit  persons  to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The  above  copyright  notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED  "AS IS",  WITHOUT WARRANTY  OF ANY KIND, EXPRESS OR
 * IMPLIED,  INCLUDING BUT NOT LIMITED  TO THE  WARRANTIES  OF  MERCHANTABILITY,
 * FITNESS  FOR A  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT  OF  OR  IN  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _JS_OBJECT_HH_
#define _JS_OBJECT_HH_

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "JsException.hh"
#include "JsFunction.hh"

namespace Js
{
    class Object
    {

    public:

	Object();
	explicit Object(int);
	explicit Object(const long long&);
	explicit Object(const long double&);
	explicit Object(const std::string&);
	Object(const std::initializer_list<std::pair<std::string, const Object&> >&);
	explicit Object(const Function&);
        Object(const Object&);

	virtual ~Object();
	operator std::string() const;

	const Object& operator=(int);
	const Object& operator=(const long long&);
	const Object& operator=(const long double&);
	const Object& operator=(const std::string&);
	const Object& operator=(const std::initializer_list<std::pair<std::string, const Object&> >&);
	const Object& operator=(const Function&);
	const Object& operator=(const Object&);


	template <typename R, typename ...A>
	R operator()(const A& ... args) const;


	Object operator+(const Object&) const;
	Object operator+(const std::string&) const;
	Object operator+(int) const;
	Object operator+(const long long&) const;
	Object operator+(const long double&) const;

	bool operator==(const Object&) const;
	bool operator==(const std::string&) const;
	bool operator==(int) const;

	template<typename T>
	bool operator!=(const T&) const;

	template<typename T>
	Object& operator+=(const T&);


	const Object& clear();

	Object&		operator[](const std::string&);
	const Object&	operator[](const std::string&) const;

    private:

	enum Type
	    {
		TYPE_UNDEFINED,
		TYPE_STRING,
		TYPE_INTERGER,
		TYPE_FLOAT,
		TYPE_OBJECT,
		TYPE_FUNCTION,
		TYPE_BOOL
	    };

	Type		_type;

	std::string	_string;
	bool		_bool;
	long long	_integer;
	long double	_float;
	Function	_function;
	std::shared_ptr<std::map<std::string, Js::Object> > _map;
    };
}

std::ostream& operator<<(std::ostream&, const Js::Object&);

#include "JsObject.hpp"

#endif
