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

#include "EventApplication.hh"

namespace Event
{
  Application::Application()
  {
    _base = event_base_new();
  }

  Application::~Application()
  {
    event_base_free(_base);
  }

  int	Application::run()
  {
    return event_base_loop(_base, 0);
  }


  bool	Application::addTimer(long long millisecond, const std::function<void ()>&f)
  {
    struct event** event = new struct event*;
    struct timeval timeout = {millisecond / 1000,millisecond % 1000};

    *event = event_new(_base, -1, 0, Application::eventCallback, new std::function<void ()>([event, f] ()
      {
	f();

	event_free(*event);
	delete event;
      }
));
    event_add(*event, &timeout);
    return true;
  }

  void Application::eventCallback(evutil_socket_t , short , void *arg)
  {
    std::function<void()>* f = reinterpret_cast<std::function<void()>* >(arg);
    (*f)();
    delete f;
  }

}
