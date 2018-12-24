/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2018  Stefaan Himpe <stefaan.himpe@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CSEGMENT_H
#define CSEGMENT_H

#include "cpoint.h"
#include <boost/polygon/voronoi.hpp>
#include <cmath>

/**
 * @todo write docs
 */
class CSegment
{
public:
    /**
     * Default constructor
     */
    CSegment(int x1, int y1, int x2, int y2) : m_p0(x1, y1), m_p1(x2, y2) {}
    CSegment(const CPoint &p0, const CPoint &p1) : m_p0(p0), m_p1(p1) {}
    
    CPoint &p0() { return m_p0; }
    CPoint &p1() { return m_p1; }
    const CPoint &p0() const { return m_p0; }
    const CPoint &p1() const { return m_p1; }
    
    double len() const { return sqrt((p1().m_x - p0().m_x)*(p1().m_x - p0().m_x) + (p1().m_y - p0().m_y)*(p1().m_y - p0().m_y)); }
    
    CPoint m_p0;
    CPoint m_p1;
};

namespace boost {
    namespace polygon {
        template <>
        struct geometry_concept<CSegment> { typedef segment_concept type; };

        template <>
        struct point_traits<CSegment> {
            typedef int coordinate_type;
            typedef CPoint point_type;
                
            static inline point_type get(const CSegment& segment, direction_1d dir) {
                return dir.to_int() ? segment.m_p1 : segment.m_p0;
            }
        };
    }
}

#endif // CSEGMENT_H
