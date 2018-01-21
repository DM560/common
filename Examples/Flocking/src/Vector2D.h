#ifndef VECTOR2D_H
#define VECTOR2D_H


#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


namespace Flocking {


// error() simply disguises throws:
inline void error(const string& s)
{
        throw runtime_error(s);
}

inline void error(const string& s, const string& s2)
{
        error(s+s2);
}

inline void error(const string& s, int i)
{
        ostringstream os;
        os << s <<": " << i;
        error(os.str());
}

inline void error(const string& s, vector<double> myvec)
{
        ostringstream os;
        os <<"\n"<< s <<": ";
        for (double v : myvec) os<< v<<" ";
        error(os.str());
}



	struct Vector2D {
		double x;
		double y;
		Vector2D() {};
		Vector2D(double xx, double yy);
		inline double squareMagnitude() const {return x*x+y*y;};
		inline double Magnitude() const {return sqrt(x*x+y*y);};
		void Normalize();
		void clear() {x=0;y=0;};

        Vector2D& operator=(const Vector2D &b) {x=b.x; y=b.y; return *this;};

		Vector2D& operator+=(const Vector2D &b) {x+=b.x; y+=b.y; return *this;};
		Vector2D& operator*=(const double &b) {x*=b; y*=b; return *this;};
		Vector2D& operator-=(const Vector2D &b) {x-=b.x; y-=b.y; return *this;};
		friend Vector2D operator+(Vector2D lhs,        // passing lhs by value helps optimize chained a+b+c
			const Vector2D& rhs) // otherwise, both parameters may be const references
			{
				lhs += rhs; // reuse compound assignment
				return lhs; // return the result by value (uses move constructor)
			}
            friend Vector2D operator-(Vector2D lhs,        // passing lhs by value helps optimize chained a+b+c
			const Vector2D& rhs) // otherwise, both parameters may be const references
			{
				lhs -= rhs; // reuse compound assignment
				return lhs; // return the result by value (uses move constructor)
			}
			friend Vector2D operator*(Vector2D lhs,        // passing lhs by value helps optimize chained a+b+c
				const double& rhs) // otherwise, both parameters may be const references
				{
					lhs *= rhs; // reuse compound assignment
					return lhs; // return the result by value (uses move constructor)
				}
			};
			
			ostream& operator<<(ostream& os, const Vector2D &p);
        }

#endif