##
# The MIT License (MIT)
#
# Copyright (c) 2013 Jerome Quere <contact@jeromequere.com>
#
# Permission is hereby granted, free  of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction,  including without limitation the rights
# to use,  copy,  modify,  merge, publish,  distribute, sublicense, and/or sell
# copies  of  the  Software,  and  to  permit  persons  to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The  above  copyright  notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED  "AS IS",  WITHOUT WARRANTY  OF ANY KIND, EXPRESS OR
# IMPLIED,  INCLUDING BUT NOT LIMITED  TO THE  WARRANTIES  OF  MERCHANTABILITY,
# FITNESS  FOR A  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT  OF  OR  IN  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
##

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (js++)


list(APPEND CMAKE_CXX_FLAGS "-std=c++0x -Wall")


SET (LIB_NAME "jspp")
SET (LIB_SRC_DIR "src")
SET (LIB_INCLUDES_DIR "includes")
LIST (APPEND LIB_SRC "${LIB_SRC_DIR}/EventApplication.cc")
LIST (APPEND LIB_SRC "${LIB_SRC_DIR}/JsApplication.cc")
LIST (APPEND LIB_SRC "${LIB_SRC_DIR}/JsEventEmitter.cc")
LIST (APPEND LIB_SRC "${LIB_SRC_DIR}/JsFunction.cc")
LIST (APPEND LIB_SRC "${LIB_SRC_DIR}/JsObject.cc")


ADD_LIBRARY (${LIB_NAME} STATIC ${LIB_SRC})
INCLUDE_DIRECTORIES (${LIB_INCLUDES_DIR})

FIND_LIBRARY (EVENT_LIB "event")
FIND_LIBRARY (CPPTEST_LIB "unit++")

SET (TEST1_NAME TEST1)
LIST (APPEND TEST1_SRC tests/test1.cc)
ADD_EXECUTABLE (${TEST1_NAME} ${TEST1_SRC})
TARGET_LINK_LIBRARIES(${TEST1_NAME} ${LIB_NAME} ${EVENT_LIB} ${CPPTEST_LIB})

SET (TEST2_NAME TEST2)
LIST (APPEND TEST2_SRC tests/test2.cc)
ADD_EXECUTABLE (${TEST2_NAME} ${TEST2_SRC})
TARGET_LINK_LIBRARIES(${TEST2_NAME} ${LIB_NAME})

ADD_TEST (${TEST1_NAME} ${TEST1_NAME})
