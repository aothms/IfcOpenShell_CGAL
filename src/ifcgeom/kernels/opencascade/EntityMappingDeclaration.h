﻿#include "EntityMappingUndefine.h"
#define CLASS(T,V) bool convert(const IfcSchema::T* L, V& r);
#define SHAPES(T) CLASS(T,ConversionResults)
#define SHAPE(T) CLASS(T,TopoDS_Shape)
#define WIRE(T) CLASS(T,TopoDS_Wire)
#define FACE(T) CLASS(T,TopoDS_Shape)
#define CURVE(T) CLASS(T,Handle(Geom_Curve))
#include "EntityMappingDefine.h"

#include "EntityMapping.h"