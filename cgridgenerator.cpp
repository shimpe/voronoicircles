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

#include "cgridgenerator.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

boost::random::mt19937 GLOBALgen;

std::vector<CPoint> CGridGenerator::generate(int minx, int maxx, int miny, int maxy, int noOfPoints) const
{
  std::vector<CPoint> Result;
  Result.reserve(noOfPoints);
  for (int i=0; i<noOfPoints; ++i) 
  {
      int x = roll_die(minx, maxx);
      int y = roll_die(miny, maxy);
      Result.emplace_back(x, y);
  }
  return Result;
}

int CGridGenerator::roll_die(int min, int max) const
{
    boost::random::uniform_int_distribution<> dist(min, max);
    return dist(GLOBALgen);
}


