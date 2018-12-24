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

#ifndef CPOINT_H
#define CPOINT_H

#include <boost/polygon/voronoi.hpp>

/**
 * @todo write docs
 */
class CPoint
{
public:
    /**
     * Default constructor
     */
    CPoint(int x, int y) : m_x(x), m_y(y) { }
    CPoint(const CPoint &other) : m_x(other.m_x), m_y(other.m_y) {}
    bool operator==(const CPoint &other) { return m_x == other.m_x && m_y == other.m_y; }
    int m_x;
    int m_y;
};


namespace boost {
    namespace polygon {
        template <>
        struct geometry_concept<CPoint> {
        typedef point_concept type;
        };

        template <>
        struct point_traits<CPoint> {
        typedef int coordinate_type;

        static inline coordinate_type get(
            const CPoint& point, orientation_2d orient) {
            return (orient == HORIZONTAL) ? point.m_x : point.m_y;
        }
        };
    }
}

#endif // CPOINT_H
