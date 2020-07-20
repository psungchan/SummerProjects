//
//  Point.hpp
//  MonteCarlo
//
//  Created by Luis Martinez on 12/26/19.
//  Copyright © 2019 UDevs. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

class Point {
    
  public:
    Point(double x, double y);
    Point();
    void translate(double x_shift, double y_shift);
    double getX();
    double getY();
    
  private:
    double x;
    double y;
    
};

#endif /* Point_hpp */
