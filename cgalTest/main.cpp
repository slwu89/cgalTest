//
//  main.cpp
//  cgalTest
//
//  Created by Sean Wu on 6/24/17.
//  Copyright © 2017 Sean Wu. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;
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


int main(){
    std::cout << "RUNNING POINTS AND SEGMENT! " << std::endl;
    pointsAndSegment();
    
    std::cout << "RUNNING EXACT KERNEL! " << std::endl;
    
    return(0);
    
}
