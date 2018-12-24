#include <iostream>
#include <sstream>
#include <iomanip>
#include "cgridgenerator.h"
#include "CImg/CImg.h"
#include <boost/polygon/voronoi.hpp>
#include "cpoint.h"
#include "csegment.h"
#include <cassert>

const unsigned char red[] = { 255,0,0 };
const unsigned char black[] = { 0,0,0 };
const unsigned char blue[] = {0,0,255};

int main()
{
    std::string dir("/home/shimpe/development/c++/voronoicircles/build/voronoi_circles");
    CGridGenerator g;
    auto points = g.generate ( 0, 1200, 0, 600, 5000 );
    std::vector<CPoint> History;

    for ( const auto &p: points ) {
        History.push_back ( p );
        cimg_library::CImg<unsigned char> Image ( 1200,600,1,3,255 );
        Image = Image.draw_circle(p.m_x, p.m_y, 3, red);

        boost::polygon::voronoi_diagram<double> vd;
        boost::polygon::construct_voronoi ( History.begin(), History.end(), &vd );

        for ( const auto& vertex: vd.vertices() ) {
            std::vector<CPoint> Triangle;
            auto edge = vertex.incident_edge();
            do {
                auto cell = edge->cell();
                assert ( cell->contains_point() );

                Triangle.push_back ( History[cell->source_index()] );
                if ( Triangle.size() == 3 ) {
                    // process output triangles

                    Image = Image.draw_line(Triangle[0].m_x, Triangle[0].m_y, Triangle[1].m_x, Triangle[1].m_y, black);
                    Image = Image.draw_line(Triangle[1].m_x, Triangle[1].m_y, Triangle[2].m_x, Triangle[2].m_y, black);
                    Image = Image.draw_line(Triangle[2].m_x, Triangle[2].m_y, Triangle[0].m_x, Triangle[0].m_y, black);
                    double A = CSegment ( Triangle[1], Triangle[2] ).len();
                    double B = CSegment ( Triangle[0], Triangle[2] ).len();
                    double C = CSegment ( Triangle[0], Triangle[1] ).len();
                    double PERIMETER = A+B+C;
                    double x_center = ( A*Triangle[0].m_x + B*Triangle[1].m_x + C*Triangle[2].m_x ) /PERIMETER;
                    double y_center = ( A*Triangle[0].m_y + B*Triangle[1].m_y + C*Triangle[2].m_y ) /PERIMETER;
                    double S = PERIMETER/2;
                    double radius = sqrt ( S* ( S-A ) * ( S-B ) * ( S-C )) / S;
                    Image = Image.draw_circle ( x_center, y_center, 1, blue );
                    Image = Image.draw_circle ( x_center, y_center, radius, blue );
                    Triangle.erase ( Triangle.begin() + 1 );
                }

                edge = edge->rot_next();
            } while ( edge != vertex.incident_edge() );
        }

        std::ostringstream flname;
        flname << "Img_" << std::setfill('0') << std::setw(6) << History.size() << ".png";
        std::string fullname = (dir + "/" + flname.str()).c_str();
        std::cout << "saving " << fullname; 
        Image.save_png(fullname.c_str());
        //cimg_library::CImgDisplay MainDisp ( Image, "Circles" );
        //while ( !MainDisp.is_closed() ) {
        //    MainDisp.wait();
        //}
    }

    return 0;
}
