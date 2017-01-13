/********************************************************************************
 *                                                                              *
 * This file is part of IfcOpenShell.                                           *
 *                                                                              *
 * IfcOpenShell is free software: you can redistribute it and/or modify         *
 * it under the terms of the Lesser GNU General Public License as published by  *
 * the Free Software Foundation, either version 3.0 of the License, or          *
 * (at your option) any later version.                                          *
 *                                                                              *
 * IfcOpenShell is distributed in the hope that it will be useful,              *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                 *
 * Lesser GNU General Public License for more details.                          *
 *                                                                              *
 * You should have received a copy of the Lesser GNU General Public License     *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.         *
 *                                                                              *
 ********************************************************************************/

#ifndef STEPSERIALIZER_H
#define STEPSERIALIZER_H

#include <STEPControl_Writer.hxx>
#include <Interface_Static.hxx>

#include "../ifcgeom/IfcGeomIterator.h"

#include "../ifcconvert/OpenCascadeBasedSerializer.h"
#include "../ifcgeom/kernels/opencascade/OpenCascadeConversionResult.h"

class StepSerializer : public OpenCascadeBasedSerializer
{
private:
	STEPControl_Writer writer;	
public:
	explicit StepSerializer(const std::string& out_filename, const IfcGeom::IteratorSettings &settings)
		: OpenCascadeBasedSerializer(out_filename, settings)
	{}
	virtual ~StepSerializer() {}
	void writeShape(const IfcGeom::ConversionResultShape* shape) {
		std::stringstream ss;
		std::streambuf *sb = std::cout.rdbuf(ss.rdbuf());
		writer.Transfer(*(IfcGeom::OpenCascadeShape*)shape, STEPControl_AsIs);
		std::cout.rdbuf(sb);
	}
	void finalize() {
		std::stringstream ss;
		std::streambuf *sb = std::cout.rdbuf(ss.rdbuf());
		writer.Write(out_filename.c_str());
		std::cout.rdbuf(sb);
	}
	void setUnitNameAndMagnitude(const std::string& /*name*/, float magnitude) {
		const char* symbol = getSymbolForUnitMagnitude(magnitude);
		if (symbol) {
			Interface_Static::SetCVal("xstep.cascade.unit", symbol);
			Interface_Static::SetCVal("write.step.unit", symbol);
		}
	}
};

#endif