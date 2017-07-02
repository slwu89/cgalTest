//
//  main.cpp
//  cgalTest
//
//  Created by Sean Wu on 6/24/17.
//  Copyright © 2017 Sean Wu. All rights reserved.
//

// header files

// for pointsAndSegment
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <random>


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>

#include <CGAL/MP_Float.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/Apollonius_graph_2.h>
#include <CGAL/Apollonius_graph_traits_2.h>
#include <CGAL/Apollonius_graph_adaptation_traits_2.h>
#include <CGAL/Apollonius_graph_adaptation_policies_2.h>

#include <CGAL/Voronoi_diagram_2.h>



#include <CGAL/Origin.h>
#include <CGAL/Point_2.h>
#include <CGAL/use.h>
//#include <CGAL/Weighted_point_2.h>

//try to weight points


// get data out



typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel_Exact;
typedef CGAL::Apollonius_graph_traits_2<Kernel_Exact>             APT;
typedef CGAL::Apollonius_site_2<Kernel_Exact>                   Site_2_Apo;
typedef Site_2_Apo::Point_2                                     Site_2_Point_2;
typedef Site_2_Apo::Weight                                      Site_2_Weight;

typedef CGAL::Apollonius_graph_traits_2<Kernel_Exact>                              AGT2_K;
typedef CGAL::Apollonius_graph_2<AGT2_K>                                            AG2;
typedef CGAL::Apollonius_graph_adaptation_traits_2<AG2>                            AG2_Trait;
typedef CGAL::Apollonius_graph_caching_degeneracy_removal_policy_2<AG2>            AG2_Policy;
typedef CGAL::Voronoi_diagram_2<AG2,AG2_Trait,AG2_Policy>                          VD_AG2;


// typedefs to get data out
typedef VD_AG2::Locate_result             Locate_result;
typedef VD_AG2::Vertex_handle             Vertex_handle;
typedef VD_AG2::Face_handle               Face_handle;
typedef VD_AG2::Halfedge_handle           Halfedge_handle;
typedef VD_AG2::Ccb_halfedge_circulator   Ccb_halfedge_circulator;



std::random_device seed;  //Will be used to obtain a seed for the random number engine
std::mt19937 RNG(seed()); //Standard mersenne_twister_engine seeded with rd()

std::uniform_real_distribution<> randomPoint(0, 30);
std::uniform_real_distribution<> randomWeight(0, 50);


void WeightedVoronoi(){

    std::cout << "got here 1" << std::endl;
    std::vector<Site_2_Apo> List_Nodes;
    
    for(int i = 0; i<= 100; i++){
        for(int j = 0; j <= 100;j++)
        {
            List_Nodes.push_back(Site_2_Apo(Site_2_Point_2(i+randomPoint(RNG),j+randomPoint(RNG)),Site_2_Weight(randomWeight(RNG))));
        }
    }

    VD_AG2 VDA;      //Voronoi Apol

    std::cout << "got here 2 " << std::endl;
    ///Voronoi Generation
    VDA.clear();
    VDA.insert(List_Nodes.begin(),List_Nodes.end());
    double xx = VDA.number_of_faces();

    std::cout << "made VDA object with faces: " << xx << std::endl;

//    VDA.bounded_faces_iterator f;
    VD_AG2::Bounded_faces_iterator f;
//    std::vector<CGAL::QPointF> poly;
    for(f = VDA.bounded_faces_begin(); f != VDA.bounded_faces_end(); f++)
    {
        std::cout << "iterating..." << std::endl;
        Ccb_halfedge_circulator ec_start = (f)->ccb();
        Ccb_halfedge_circulator ec = ec_start;
        do {
            double x = ((Halfedge_handle)ec)->source()->point().x();
            double y = ((Halfedge_handle)ec)->source()->point().y();
            std::cout << "x: " << x << " y: " << y << std::endl;
        } while ( ++ec != ec_start );
    }

}





#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iterator>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::FT Weight;
typedef K::Point_2 Point_2;
typedef K::Iso_rectangle_2 Iso_rectangle_2;
typedef K::Segment_2 Segment_2;
typedef K::Ray_2 Ray_2;
typedef K::Line_2 Line_2;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay_triangulation_2;
typedef Delaunay_triangulation_2::Edge_iterator Edge_iterator;


//A class to recover Voronoi diagram from stream.
//Rays, lines and segments are cropped to a rectangle
//so that only segments are stored
struct Cropped_voronoi_from_delaunay{
    std::list<Segment_2> m_cropped_vd;
    Iso_rectangle_2 m_bbox;
    Cropped_voronoi_from_delaunay(const Iso_rectangle_2& bbox):m_bbox(bbox){}
    template <class RSL>
    void crop_and_extract_segment(const RSL& rsl){
        CGAL::Object obj = CGAL::intersection(rsl,m_bbox);
        const Segment_2* s=CGAL::object_cast<Segment_2>(&obj);
        if (s) m_cropped_vd.push_back(*s);
    }
    void operator<<(const Ray_2& ray) { crop_and_extract_segment(ray); }
    void operator<<(const Line_2& line) { crop_and_extract_segment(line); }
    void operator<<(const Segment_2& seg){ crop_and_extract_segment(seg); }
};

void boundedTriangulation(){
    //consider some points
    std::vector<Point_2> points;
    points.push_back(Point_2(0,0));
    points.push_back(Point_2(1,1));
    points.push_back(Point_2(0,1));
    points.push_back(Point_2(1,0));
    Delaunay_triangulation_2 dt2;
    //insert points into the triangulation
    dt2.insert(points.begin(),points.end());
    //construct a rectangle
    Iso_rectangle_2 bbox(-1,-1,2,2);
    Cropped_voronoi_from_delaunay vor(bbox);
    //extract the cropped Voronoi diagram
    dt2.draw_dual(vor);
    
    //print the cropped Voronoi diagram as segments
    int size = vor.m_cropped_vd.size();
    
    // get the segments out
    std::vector<Segment_2> segmentOut(size);
    std::copy(vor.m_cropped_vd.begin(),vor.m_cropped_vd.end(),
              segmentOut.begin());
    for(auto it = segmentOut.begin(); it != segmentOut.end(); it++){
        std::cout << "thing inside of segmentOut: " << *it << std::endl;
        std::cout << "first point inside of segmentOut's x value: " << it->point(0).x()  << std::endl;
    }
    
    int ns = 0;
    int nr = 0;
    Edge_iterator eit =dt2.edges_begin();
    for ( ; eit !=dt2.edges_end(); ++eit) {
        CGAL::Object o = dt2.dual(eit);
        if (CGAL::object_cast<K::Segment_2>(&o)){
            ++ns;
        } else if (CGAL::object_cast<K::Ray_2>(&o)){
            
            const Ray_2 * ray = CGAL::object_cast<K::Ray_2>(&o);
            
            std::cout << "ray: " << *ray << std::endl;
            double oo = ray->point(0).x();
            std::cout << "point in the ray " << oo << std::endl;
            ++nr;
        }
    }
    std::cout << "The Voronoi diagram has " << ns << " finite edges " << " and " << nr << " rays" << std::endl;
    
}



int main(){

    std::cout << "RUNNING WEIGHTED VORONOI" << std::endl;
    WeightedVoronoi();
    
    std::cout << "RUNNING BOUNDED VORONOI" << std::endl;
    boundedTriangulation();

    return(0);

}
