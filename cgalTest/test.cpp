//
//  test.cpp
//  cgalTest
//
//  Created by Sean Wu on 7/4/17.
//  Copyright © 2017 Sean Wu. All rights reserved.
//


//typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel_Exact;
//typedef CGAL::Apollonius_graph_traits_2<Kernel_Exact>             APT;
//typedef CGAL::Apollonius_site_2<Kernel_Exact>                   Site_2_Apo;
//typedef Site_2_Apo::Point_2                                     Site_2_Point_2;
//typedef Site_2_Apo::Weight

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <iterator>

// the number type
#include <CGAL/MP_Float.h>

// example that uses an exact number type

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
// #include <iterator>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Iso_rectangle_2 Iso_rectangle_2;
typedef K::Segment_2 Segment_2;
typedef K::Ray_2 Ray_2;
typedef K::Line_2 Line_2;

// typedefs for the traits and the algorithm

#include <CGAL/Apollonius_graph_2.h>
#include <CGAL/Apollonius_graph_traits_2.h>

typedef CGAL::Apollonius_graph_traits_2<K>   Traits;
typedef CGAL::Apollonius_graph_2<Traits>     Apollonius_graph;
typedef CGAL::Apollonius_site_2<K>           Site_2;
typedef Site_2::Point_2                      Apollonius_Point_2;
typedef Site_2::Weight                       Apollonius_Weight;


//A class to recover Voronoi diagram from stream.
struct Cropped_voronoi_from_apollonius{
    std::list<Segment_2> m_cropped_vd;
    Iso_rectangle_2 m_bbox;
    
    Cropped_voronoi_from_apollonius(const Iso_rectangle_2& bbox):m_bbox(bbox){}
    
    template <class RSL>
    void crop_and_extract_segment(const RSL& rsl){
        CGAL::Object obj = CGAL::intersection(rsl,m_bbox);
        const Segment_2* s=CGAL::object_cast<Segment_2>(&obj);
        if (s) m_cropped_vd.push_back(*s);
    }
    
    void operator<<(const Ray_2& ray)    { crop_and_extract_segment(ray); }
    void operator<<(const Line_2& line)  { crop_and_extract_segment(line); }
    void operator<<(const Segment_2& seg){ crop_and_extract_segment(seg); }
    
    void reset() {
        m_cropped_vd.erase(m_cropped_vd.begin(), m_cropped_vd.end());
    }
};


int voronoiTreeTest(){
    
    Apollonius_graph ag;
    
    ag.insert(Site_2(Apollonius_Point_2(1.2,3.2),Apollonius_Weight(1)));
    ag.insert(Site_2(Apollonius_Point_2(4.3,3.2),Apollonius_Weight(2)));
    ag.insert(Site_2(Apollonius_Point_2(3.2,3.2),Apollonius_Weight(1)));
    ag.insert(Site_2(Apollonius_Point_2(5.2,3.2),Apollonius_Weight(1.5)));
    ag.insert(Site_2(Apollonius_Point_2(3.7,3.2),Apollonius_Weight(1.8)));
    
    
    //construct a rectangle
    // This is set up to be well outside the range of the sites
    // This means that we should be able to just join up the end
    // points for any open cells, without fear of crossing the
    // area that contains the sites (EXCEPT for pretty pathological
    // cases, e.g., where there are only two sites)
    Iso_rectangle_2 bbox(-2000,-2000,2000,2000);
    
    Cropped_voronoi_from_apollonius vor(bbox);
    
    // iterate to extract Voronoi diagram edges around each vertex
    Apollonius_graph::Finite_vertices_iterator vit;
    for (vit = ag.finite_vertices_begin();
         vit != ag.finite_vertices_end();
         ++vit) {
        std::cout << "Vertex ";
        std::cout << vit->site().point();
        std::cout << "\n";
        Apollonius_graph::Edge_circulator ec = ag.incident_edges(vit), done(ec);
        if (ec != 0) {
            do {
                ag.draw_dual_edge(*ec, vor);
                // std::cout << "Edge\n";
            } while(++ec != done);
        }
        //print the cropped Voronoi diagram edges as segments
        std::copy(vor.m_cropped_vd.begin(),vor.m_cropped_vd.end(),
                  std::ostream_iterator<Segment_2>(std::cout,"\n"));
        vor.reset();
    }
    
    //extract the entire cropped Voronoi diagram
    // ag.draw_dual(vor);
    
    return 0;
}
