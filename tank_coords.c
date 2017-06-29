/*
 * tank_coords.c
 *
 * Prototype code to give an example of how to calculate four rectangle
 * vertex coordinates given the rectangle center coordinate and a rotation angle. The
 * purpose of all of this is to create a rectangle representing a tank for the x-inference
 * project.
 *
 * Copyright 2017 David Pointer <david.b.pointer@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */
#include <stdio.h>
#include <math.h>

// front, side, rear and left, right is determined from looking down at top of tank
// zero degrees is north on the battle map, degrees increment counter-clockwise

#define XC (3.0)        // x coord center of tank
#define YC (3.0)        // y coord center of tank
#define ROT (270.0)     // tank current center/front orientation relative to north, in degrees
#define FRONT (1.2)     // tank front (rear) dimension (inches)
#define SIDE (2.5)      // tank side dimension (inches)

struct Coords {         // calculated tank vertex coordinates
    float xfl;          // x front left coord
    float yfl;          // y front left coord
    float xfr;          // x front right coord
    float yfr;          // y front right coord
    float xrr;          // x rear right coord
    float yrr;          // y rear right coord
    float xrl;          // x rear left coord
    float yrl;          // y rear left coord
};

struct Position {       // current tank position data
    float xc;           // x coord center of tank
    float yc;           // y coord center of tank
    float rot;          // orientation of center/front of tank
};

void rotate(float xc, float yc, float *x, float *y, float rad_angle);
void print_coords(struct Coords *coords);

//--------------------------------------------------------------------------------------------------
//  Program to calculate the four bounding rectangle vertices from a given center point and
//  a rotation angle.
//--------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    struct Coords coords;       // calculated tank vertex coordinates
    struct Position position;   // current tank position data
    float front = FRONT;        // tank front (rear) dimension (inches)
    float side = SIDE;          // tank side dimension (inches)

    // init current tank position data
    position.xc = XC;
    position.yc = YC;
    position.rot = ROT;
    // create tank rectangle from center coords and dimensions
    coords.xfl = position.xc - front/2.0;
    coords.yfl = position.yc + side/2.0;
    coords.xfr = position.xc + front/2.0;
    coords.yfr = position.yc + side/2.0;
    coords.xrr = position.xc + front/2.0;
    coords.yrr = position.yc - side/2.0;
    coords.xrl = position.xc - front/2.0;
    coords.yrl = position.yc - side/2.0;

    // calc the current bounding rectangle, then rotate it properly
    printf("un-rotated tank bounding rectangle coords\n");
    print_coords(&coords);
    float rad_angle = position.rot * 0.01745329252;
    rotate(position.xc, position.yc, &coords.xfl, &coords.yfl, rad_angle);
    rotate(position.xc, position.yc, &coords.xfr, &coords.yfr, rad_angle);
    rotate(position.xc, position.yc, &coords.xrr, &coords.yrr, rad_angle);
    rotate(position.xc, position.yc, &coords.xrl, &coords.yrl, rad_angle);
    printf("rotated tank bounding rectangle coords\n");
    print_coords(&coords);

    return 0;
}

//----------------------------------------------------------------------
//  print_coords()
//
//  Utility function to print the bounding rectangle vertex coordinates.
//
//  Args:
//    coords: pointer to tank bounding rectangle vertex coordinates.
//  Returns:
//    none
//----------------------------------------------------------------------
void print_coords(struct Coords *coords)
{
    printf("front left  %0.3f %0.3f\n", coords->xfl, coords->yfl);
    printf("front right %0.3f %0.3f\n", coords->xfr, coords->yfr);
    printf("rear  right %0.3f %0.3f\n", coords->xrr, coords->yrr);
    printf("rear  left  %0.3f %0.3f\n", coords->xrl, coords->yrl);
}

//----------------------------------------------------------------------
//  rotate()
//
//  Utility to rotate a given x,y coordinate from a tank bounding
//  rectangle vertex by a given number of radians.
//
//  Args:
//    xc: center coord x of rectangle
//    yc: center coord y of rectangle
//    x: pointer to x coord to rotate
//    y: pointer to y coord to rotate
//    rad_angle: radians to rotate x,y
//  Returns:
//    none
//----------------------------------------------------------------------
void rotate(float xc, float yc, float *x, float *y, float rad_angle)
{
    float xo = *x - xc;
    float yo = *y - yc;
    float xp = xo * cosf(rad_angle) - yo * sinf(rad_angle);
    float yp = yo * cosf(rad_angle) + xo * sinf(rad_angle);
    *x = xp + xc;
    *y = yp + yc;
}

