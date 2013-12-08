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

#include "JsException.hh"

namespace Js
{
    template <typename T>
    struct FunctionTemplate : public FunctionTemplate<decltype(&T::operator())>
    {
	FunctionTemplate(const T& f) : FunctionTemplate<decltype(&T::operator())>(f) {};
    };

    template <typename R, typename C, typename ...A>
    struct FunctionTemplate<R (C::*)(A...) const> : public FunctionTemplate<R (A...)>
    {
	FunctionTemplate(const std::function<R (const A& ...)>&f) : FunctionTemplate<R (A...)>(f) {}
    };

    template <typename R, typename ...A>
    struct FunctionTemplate<R (*)(A...)>: public FunctionTemplate<R (A...)>
    {
	FunctionTemplate(const std::function<R (const A& ...)>& f) : FunctionTemplate<R (A...)>(f) {};
    };

    template<typename R, typename ... A>
    struct FunctionTemplate<R (A...)> : public Function::IFunction
    {
    public:

	FunctionTemplate(const std::function<R (const A& ...)>&f) : _f(f) {}

	R operator()(const A& ... args) const
	{
	    return _f(args...);
	}

    private:
	std::function<R(const A& ...)>    _f;
    };

    template <typename T>
    Function::Function(const T& f)
    {
	*this = f;
    }

    template <typename T>
    Function& Function::operator=(const T& obj)
    {
	_f.reset(new FunctionTemplate<T>(obj));
	return *this;
    }

    template <typename R, typename ...A>
    R Function::operator()(const A& ... args) const
    {
	auto ptr = dynamic_cast<FunctionTemplate<R(A ...)>*>(_f.get());
	if (ptr == nullptr) throw BadFunctionCallTypeException();
	return (*ptr)(args...);
    }

}
