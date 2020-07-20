//
//  main.cpp
//  MonteCarlo
//
//  Created by Luis Martinez on 12/26/19.
//  Copyright © 2019 UDevs. All rights reserved.
//

#include <iostream>
#include "Point.hpp"
#include <stdlib.h>
#include <math.h>
#include <thread>
#include <chrono>
#define SIZE 1000000

Point* getPoints() {
  Point* pts = new Point[SIZE];
  for (int i = 0; i < SIZE; i++) {
    pts[i].translate( (double) rand()/RAND_MAX, (double) rand()/RAND_MAX );
  }
  return pts;
}

double distance(Point pt1, Point pt2) {
  double first = pt2.getX() - pt1.getX();
  double second = pt2.getY() - pt1.getY();
  double result = pow(first, 2) + pow(second, 2);
  return sqrt(result);
}


double calculatePi(Point* pts) {
  Point origin(0.5, 0.5);
  double inside = 0;
  
  for (int i = 0; i < SIZE; i++) {
    if (distance(origin, pts[i]) <= 0.5) {
      inside++;
    }
  }
  
  double pi = 4 * (inside / SIZE);
  std::cout << pi << std::endl;
  return pi;
}

void inside(double* count, Point* pts, int start, int finish) {
  Point origin(0.5, 0.5);
  int inside = 0;
  
  for (int i = start; i < finish; i++) {
    if (distance(origin, pts[i]) <= 0.5) {
      inside++;
    }
  }
  *count = inside;
}

int main() {
  Point* pts = getPoints();
  double arr[5] = {0, 0, 0, 0, 0};
  
  //Measure how much time it takes to calculate using 3 threads
  auto start = std::chrono::high_resolution_clock::now();
  
  std::thread t0(inside, &arr[0], pts, 0, (SIZE/5));
  std::thread t1(inside, &arr[1], pts, (SIZE/5), 2*(SIZE/5));
  std::thread t2(inside, &arr[2], pts, 2*(SIZE/5), 3*(SIZE/5));
  std::thread t3(inside, &arr[3], pts, 3*(SIZE/5), 4*(SIZE/5));
  inside(&arr[4], pts, 4*(SIZE/5), SIZE );
  
  t0.join();
  t1.join();
  t2.join();
  t3.join();
  
  double sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += arr[i];
  }
  
  double pi = 4*(sum/SIZE);
  std::cout << pi << std::endl;
  
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time taken by threads: " << duration.count() << " microseconds" << std::endl;
  
  std::cout << std::endl;
  
  //Now measure how much time it takes for 1 thread
  auto start2 = std::chrono::high_resolution_clock::now();
  calculatePi(pts);
  auto stop2 = std::chrono::high_resolution_clock::now();
  auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
  std::cout << "Time taken by function calculatePi: " << duration2.count() << " microseconds" << std::endl;
  
  delete[] pts;
  return 0;
}
