#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <assert.h>

///> zpublic！
#include "zpublic.hpp"

///> 标准容器
#include <string>
#include <vector>
#include <map>
#include <list>

///> 输入输出相关
#include <iomanip>
#include <iostream>
using std::cout;
using std::endl;

///> 智能指针
#include <memory>

///> 正则表达式
#include <regex>

///> 原子操作
#include <atomic>

///> 时间
#include <chrono>
#include <ratio>
#include <ctime>

///> 位操作
#include <bitset>

///> Conversion
///> Polymorphic and lexical casts.
#include <boost/cast.hpp>
#include <boost/lexical_cast.hpp>