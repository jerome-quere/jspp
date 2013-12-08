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

#include <iostream>
#include <functional>


#include "JsObject.hh"
#include "JsEventEmitter.hh"
#include "JsFunction.hh"

using namespace std;
using namespace Js;

#include <unit++.h>

using namespace unitpp;

class Test : public suite
    {
	void empty()
	{
	    Object o1;
	    Object o2(o1);
	    Object o3;

	    o3 = o1;
	    o1 = o1;
	    assert_true("A1", o1 == o2);
	    assert_true("A2", !(o1 != o2));
	}

	void string()
	{
	    Object o1(std::string("string1"));
	    Object o2(o1);
	    Object o3;

	    o3 = o1;
	    assert_true("A1", o1 == "string1");
	    assert_true("A2", o1 == o2);
	    assert_true("A3", o1 == o3);
	    o3 = o1 + "toto42";
	    assert_true("A4", o3 == "string1toto42");
	    o3 += "42";
	    assert_true("A5", o3 == "string1toto4242");
	    assert_true("A6", o3 != 42);
	}

	void numeric()
	{
	    Object o1(10);
	    Object o2(o1);
	    Object o3;

	    o3 = o1;
	    assert_true("A1", o1 == o2);
	    assert_true("A2", o2 == o3);
	    assert_true("A3", o1 == 10);
	    assert_true("A4", (o1 + o2) == 20);
	    o1 += 32;
	    assert_true("A4", o1 == Object(42));
	}

	void object()
	{
	}


    public:
	Test() : suite("Object Test Suite")
	{
	    add("test1", testcase(this, "Empty", &Test::empty));
	    add("test2", testcase(this, "String", &Test::string));
	    add("test3", testcase(this, "Numeric", &Test::numeric));
	    suite::main().add("Object", this);
	}
    };
    Test* t = new Test();




int testObj()
{
    Js::Object obj1(1);
    Js::Object obj2("toto42");
    Js::Object obj3 = {{"test1", Object(45)}};

    std::cout << "OBJ1: " << obj1 << std::endl;
    std::cout << "OBJ2: " << obj2 << std::endl;
    std::cout << "OBJ3: " << obj3 << std::endl;

    obj3["key"] = {{"toto42", Object("Value42")}};
    std::cout << "OBJ3: " << obj3 << std::endl;


    return (0);
}

class A : public Js::EventEmitter
{
};


class T
{
public:
  T(){}
  T(const T&)
  {
    std::cout << "I AM COPY " << std::endl;
  }
};

void ploupi(T t)
{
  std::cout << "CALLBACK" << std::endl;
}


void testEventRef()
{
  T a;
  A obj;

  obj.on("test", Function(&ploupi));
  obj.emit("test", a);
}
