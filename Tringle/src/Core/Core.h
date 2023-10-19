#pragma once

#include <string>
#include <map>
#include <iostream>

#include "Mesh.h"
#include "Window.h"
#include "Component.h"
#include "Timer.h"

// Important typedefs
// TODO: these should probably go somewhere else or not exist at all
typedef std::map<std::string, Window*> WindowMap;
typedef std::map<int, Mesh*> MeshMap;
typedef std::map<std::string, Component*> ComponentMap;
typedef std::map<std::string, Timer*> TimeMap;