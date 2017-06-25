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







// pointsAndSegment
//typedef CGAL::Simple_cartesian<double> Kernel;
//typedef Kernel::Point_2 Point_2;
//typedef Kernel::Segment_2 Segment_2;
// kernel
//typedef CGAL::Exact_predicates_exact_constructions_kernel KernelExact;
//typedef KernelExact::Point_2 Point_2_Exact;
////convexHullVector
//typedef CGAL::Exact_predicates_inexact_constructions_kernel KernelInexact;
//typedef KernelInexact::Point_2 Point_2_Inexact;
//typedef std::vector<Point_2_Inexact> PointsInexact;


//// pointsAndSegment
//
//void pointsAndSegment()
//{
//    Point_2 p(1,1), q(10,10);
//    std::cout << "p = " << p << std::endl;
//    std::cout << "q = " << q.x() << " " << q.y() << std::endl;
//    std::cout << "sqdist(p,q) = "
//    << CGAL::squared_distance(p,q) << std::endl;
//    
//    Segment_2 s(p,q);
//    Point_2 m(5, 9);
//    
//    std::cout << "m = " << m << std::endl;
//    std::cout << "sqdist(Segment_2(p,q), m) = "
//    << CGAL::squared_distance(s,m) << std::endl;
//    std::cout << "p, q, and m ";
//    switch (CGAL::orientation(p,q,m)){
//        case CGAL::COLLINEAR:
//            std::cout << "are collinear\n";
//            break;
//        case CGAL::LEFT_TURN:
//            std::cout << "make a left turn\n";
//            break;
//        case CGAL::RIGHT_TURN:
//            std::cout << "make a right turn\n";
//            break;
//    }
//    std::cout << " midpoint(p,q) = " << CGAL::midpoint(p,q) << std::endl;
//}
//
//
//// kernel
//typedef CGAL::Exact_predicates_exact_constructions_kernel KernelExact;
//typedef KernelExact::Point_2 Point_2_Exact;
//
//void kernel()
//{
//    Point_2_Exact p(double(0.0), 0.3), q, r(double(2.0), 0.9);
//    {
//        q  = Point_2_Exact(double(1.0), 0.6);
//        std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
//    }
//    
//    {
//        std::istringstream input("0 0.3   1 0.6   2 0.9");
//        input >> p >> q >> r;
//        std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
//    }
//    
//    {
//        q = CGAL::midpoint(p,r);
//        std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
//    }
//    
//}


//// we can also fill the "points" from a STL vector as shown below:
//// fill from a vector:
//typedef CGAL::Exact_predicates_inexact_constructions_kernel KernelInexact;
//typedef KernelInexact::Point_2 Point_2_Inexact;
//typedef std::vector<Point_2_Inexact> PointsInexact;
//
//void convexHullVector(){
//
//    PointsInexact points, result;
//    points.push_back(Point_2_Inexact(0,0));
//    points.push_back(Point_2_Inexact(10,0));
//    points.push_back(Point_2_Inexact(10,10));
//    points.push_back(Point_2_Inexact(6,5));
//    CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(result));
//    std::cout << result.size() << " points on the convex hull" << std::endl;
//    
//}


int main(){
//    std::cout << "RUNNING POINTS AND SEGMENT! " << std::endl;
//    std::cout << "" << std::endl;
//    pointsAndSegment();
//    std::cout << "" << std::endl;
//    
//    std::cout << "RUNNING EXACT KERNEL! " << std::endl;
//    std::cout << "" << std::endl;
//    kernel();
//    std::cout << "" << std::endl;
    
//    std::cout << "RUNNING CONVEX HULL VECTOR! " << std::endl;
//    std::cout << "" << std::endl;
//    convexHullVector();
//    std::cout << "" << std::endl;
    
    std::cout << "RUNNING WEIGHTED VORONOI" << std::endl;
    WeightedVoronoi();
    
    return(0);
    
}
