#pragma once

#include "openGameEngine3D/Core/PlatformDetection.h"

#ifdef OGE_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
	#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <sstream>
#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "openGameEngine3D/Core/Base.h"

#include "openGameEngine3D/Core/Log.h"

#include "openGameEngine3D/Debug/Instrumentor.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

#ifdef OGE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
