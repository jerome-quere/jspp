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

#include <sstream>

#include "JsException.hh"
#include "JsObject.hh"

namespace Js
{
    Object::Object()
    {
	_type = TYPE_UNDEFINED;
    }

    Object::~Object()
    {
    }

    Object::Object(int i) :
	Object(static_cast<long long>(i))
    {
    }

    Object::Object(const long long& i)
    {
	_type = TYPE_INTERGER;
	_integer = i;
    }

    Object::Object(const long double& d)
    {
	_type = TYPE_FLOAT;
	_float = d;
    }

    Object::Object(const std::string& str)
    {
	_type = TYPE_STRING;
	_string = str;
    }

    Object::Object(const std::initializer_list<std::pair<std::string, const Object&> >& obj)
    {
	_type = TYPE_OBJECT;
	_map.reset(new std::map<std::string, Object>());
	for (auto& it : obj)
	    {
		(*_map)[it.first] = it.second;
	    }
    }

    Object::Object(const Object& obj)
    {
	*this = obj;
    }

    Object::operator std::string() const
    {
	std::stringstream s;

	switch (_type)
	    {
	    case TYPE_UNDEFINED:
		s << "undefined"; break;
	    case TYPE_INTERGER:
		s << _integer; break;
	    case TYPE_FLOAT:
		s << _float; break;
	    case TYPE_STRING:
		s << '"' << _string << '"'; break;
	    case TYPE_BOOL:
		s << ((_bool) ? ("true") : ("false")); break;
	    case TYPE_FUNCTION:
		s << "Function"; break;
	    case TYPE_OBJECT:
		s << "{";
		bool f = false;
		for (auto& it : *(_map.get()))
		    {
			if (f) s << ',';
			s << '"' << it.first << "\":" << it.second;
			f = true;
		    }
		s << "}";
		break;
	    }
	return s.str();
    }

    const Object& Object::operator=(const Object& obj)
    {
	if (this != &obj)
	    {
		clear();
		_type = obj._type;
		switch (obj._type)
		    {
		    case TYPE_INTERGER:
			_integer = obj._integer; break;
		    case TYPE_FLOAT:
			_float = obj._float; break;
		    case TYPE_STRING:
			_string = obj._string; break;
		    case TYPE_BOOL:
			_bool = obj._bool; break;
		    case TYPE_FUNCTION:
			_function = obj._function; break;
		    case TYPE_OBJECT:
			_map = obj._map; break;
		    case TYPE_UNDEFINED:
			break;
		    }

	    }
	return *this;
    }

    const Object& Object::operator=(int i)
    {
	return Object::operator=(static_cast<long long>(i));
    }

    const Object& Object::operator=(const long long& i)
    {
	clear();
	_type = TYPE_INTERGER;
	_integer = i;
	return *this;
    }

    const Object& Object::operator=(const long double& f)
    {
	clear();
	_type = TYPE_FLOAT;
	_float = f;
	return *this;
    }

    const Object& Object::operator=(const std::string& str)
    {
	clear();
	_type = TYPE_STRING;
	_string = str;
	return *this;
    }

    const Object& Object::operator=(const std::initializer_list<std::pair<std::string, const Object&> >& obj)
    {
	clear();
	_type = TYPE_OBJECT;
	_map.reset(new std::map<std::string, Object>());
	for (auto& it : obj)
	    {
		(*_map)[it.first] = it.second;
	    }
	return *this;
    }

    Js::Object& Object::operator[](const std::string& key)
    {
	if (_type != TYPE_OBJECT)
	    throw NotAnObjectException();
	return (*_map)[key];
    }

    const Js::Object& Object::operator[](const std::string& key) const
    {
	if (_type != TYPE_OBJECT)
	    throw NotAnObjectException();

	auto it = _map->find(key);
	if (it == _map->end())
	    throw KeyDontExistException();
	return it->second;
    }

    Object Object::operator+(const Object& obj) const
    {
	switch (obj._type)
	    {
	    case TYPE_INTERGER:
		return operator+(obj._integer); break;
	    case TYPE_FLOAT:
		return operator+(obj._float); break;
	    case TYPE_STRING:
		return operator+(obj._string); break;
	    case TYPE_BOOL:
		return operator+(static_cast<int>(obj._bool)); break;
	    case TYPE_FUNCTION:
		throw OperationNotCompatibleWithThisType(); break;
	    case TYPE_OBJECT:
		throw OperationNotCompatibleWithThisType(); break;
	    case TYPE_UNDEFINED:
		throw OperationNotCompatibleWithThisType(); break;
	    }
	throw OperationNotCompatibleWithThisType();
    }

    Object Object::operator+(const std::string& s) const
    {
	if (_type != TYPE_STRING)
	    throw OperationNotCompatibleWithThisType();
	return (Object(_string + s));
    }

    Object Object::operator+(int i) const
    {
	return operator+(static_cast<long long>(i));
    }

    Object Object::operator+(const long long& i) const
    {
	if (_type == TYPE_INTERGER)
	    return Object(_integer + i);
	else if (_type == TYPE_FLOAT)
	    return Object(_float + i);
	throw OperationNotCompatibleWithThisType();
    }

    Object Object:: operator+(const long double& f) const
    {
	if (_type == TYPE_INTERGER)
	    return Object(_integer + f);
	else if (_type == TYPE_FLOAT)
	    return Object(_float + f);
	throw OperationNotCompatibleWithThisType();
    }

    bool Object::operator==(const Object& obj) const
    {
	switch (obj._type)
	    {
	    case TYPE_INTERGER:
		return operator==(obj._integer); break;
	    case TYPE_FLOAT:
		return _float == obj._float; break;
	    case TYPE_STRING:
		return operator==(obj._string); break;
	    case TYPE_BOOL:
		return _bool == obj._bool; break;
	    case TYPE_FUNCTION:
		return false; break;
	    case TYPE_OBJECT:
		return _map == obj._map; break;
	    case TYPE_UNDEFINED:
		return true; break;
	    }
	return false;
    }

    bool Object::operator==(const std::string& s) const
    {
	if (_type != TYPE_STRING) return false;
	return s == _string;
    }

    bool Object::operator==(int i) const
    {
	if (_type != TYPE_INTERGER)
	    return false;

	return _integer == i;
    }


    const Object& Object::clear()
    {
	_map.reset();
	_type = TYPE_UNDEFINED;
	return *this;
    }

}


std::ostream&	operator<<(std::ostream& s, const Js::Object& o)
{
  s << static_cast<std::string>(o);
  return s;
}
