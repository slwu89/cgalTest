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
#include <CGAL/Simple_cartesian.h>

// for kernel
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <sstream>

// typedefs

// for pointsAndSegment
typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;

// for kernel
typedef CGAL::Exact_predicates_exact_constructions_kernel KernelExact;
typedef KernelExact::Point_2 Point_2_Exact;

// pointsAndSegment
void pointsAndSegment()
{
    Point_2 p(1,1), q(10,10);
    std::cout << "p = " << p << std::endl;
    std::cout << "q = " << q.x() << " " << q.y() << std::endl;
    std::cout << "sqdist(p,q) = "
    << CGAL::squared_distance(p,q) << std::endl;
    
    Segment_2 s(p,q);
    Point_2 m(5, 9);
    
    std::cout << "m = " << m << std::endl;
    std::cout << "sqdist(Segment_2(p,q), m) = "
    << CGAL::squared_distance(s,m) << std::endl;
    std::cout << "p, q, and m ";
    switch (CGAL::orientation(p,q,m)){
        case CGAL::COLLINEAR:
            std::cout << "are collinear\n";
            break;
        case CGAL::LEFT_TURN:
            std::cout << "make a left turn\n";
            break;
        case CGAL::RIGHT_TURN:
            std::cout << "make a right turn\n";
            break;
    }
    std::cout << " midpoint(p,q) = " << CGAL::midpoint(p,q) << std::endl;
}

// kernel
void kernel()
{
    Point_2_Exact p(double(0.0), 0.3), q, r(double(2.0), 0.9);
    {
        q  = Point_2_Exact(double(1.0), 0.6);
        std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
    }
    
    {
        std::istringstream input("0 0.3   1 0.6   2 0.9");
        input >> p >> q >> r;
        std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
    }
    
    {
        q = CGAL::midpoint(p,r);
        std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
    }
    
}


int main(){
    std::cout << "RUNNING POINTS AND SEGMENT! " << std::endl;
    std::cout << "" << std::endl;
    pointsAndSegment();
    std::cout << "" << std::endl;
    
    std::cout << "RUNNING EXACT KERNEL! " << std::endl;
    std::cout << "" << std::endl;
    kernel();
    std::cout << "" << std::endl;
    
    return(0);
    
}
