//
//  Point.cpp
//  MonteCarlo
//
//  Created by Luis Martinez on 12/26/19.
//  Copyright © 2019 UDevs. All rights reserved.
//

#include "Point.hpp"

Point::Point(double x, double y) {
  this->x = x;
  this->y = y;
}

Point::Point() {
  this->x = 0.0;
  this->y = 0.0;
}

void Point::translate(double x_shift, double y_shift) {
  x += x_shift;
  y += y_shift;
}

double Point::getX() {
  return x;
}

double Point::getY() {
  return y;
}
