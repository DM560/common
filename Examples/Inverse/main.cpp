#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<cassert>
//#include<new>
//#include<cfloat>
#include<chrono>
#include<cmath>
#include<random>

#include "Matrix.h"
#include "MatrixIO.h"


using namespace std;
using Numeric_lib::Index;




typedef Numeric_lib::Matrix<double, 2> Matrix;
typedef Numeric_lib::Matrix<double, 1> Vector;



struct Elim_failure : runtime_error {
        Elim_failure(Index j): runtime_error("Exit") {}
};


struct Back_subst_failure : runtime_error {
  Back_subst_failure(Index i) : runtime_error("back") {};
};

// error() simply disguises throws:
inline void error(const string& s)
{
        throw runtime_error(s);
}



void classical_elimination(Matrix& A, Vector& b)
{
  const Index n = A.dim1();
  // traverse from 1st column to the next-to-last
  // filling zeros into all elements under the diagonal:
  for (Index j = 0; j<n-1; ++j) {
    const double pivot = A(j,j);
      if (pivot == 0) throw Elim_failure(j);
    // fill zeros into each element under the diagonal of the ith row:
    for (Index i = j+1; i<n; ++i) {
      const double mult = A(i,j)/pivot;
      A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
      b(i) -= mult*b(j);
      // make the corresponding change to b
    }
  }
}



Matrix identityMatrix(int size ) {
  Matrix I(size,size);
  for (Index i=0;i<size;i++)
	I(i,i)=1;
  return I;
}


Matrix inverse_by_gauss(Matrix A)
{
  const Index n = A.dim1();
  const Index m = A.dim2();
  if (n!=m)
	{
	  cerr<<"Trying to invert a non square matrix!"<<endl;
	  throw Elim_failure(n);
	}

  Matrix I = identityMatrix(n);
  
  // traverse from 1st column to the next-to-last
  // filling zeros into all elements under the diagonal:
  for (Index j = 0; j<n; ++j) {
    const double pivot = A(j,j);
	A[j].slice(j) /= pivot;
	I[j] /= pivot;
	if (pivot == 0) throw Elim_failure(j);
    // fill zeros into each element under the diagonal of the ith row:
    for (Index i = j+1; i<n; ++i) {
      const double mult = A(i,j); ///pivot;
      A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
	  I[i] = scale_and_add(I[j], -mult, I[i]);
      // make the corresponding change to b
    }
  }

  for (Index j = n-1; j>=0; --j) {
    // fill zeros into each element above the diagonal of the ith row:
    for (Index i = j-1; i>=0; --i) {
      const double mult = A(i,j);
      A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
	  I[i] = scale_and_add(I[j], -mult, I[i]);
      // make the corresponding change to b
    }
  }
 
  return I;
}


Vector back_substitution(const Matrix& A, const Vector& b)
{
  const Index n = A.dim1();
  Vector x(n);
  for (Index i = n-1; i>= 0; --i) {
    double s = b(i)-dot_product(A[i].slice(i+1),x.slice(i+1));
    if (double m = A(i,i))
      x(i) = s/m;
    else
      throw Back_subst_failure(i);
  }
  return x;
}

/*
void elim_with_partial_pivot(Matrix& A, Vector& b)
{
  const Index n = A.dim1();
  for (Index j = 0; j<n; ++j) {
    Index pivot_row = j;
    // look for a suitable pivot:
    for (Index k = j+1; k<n; ++k)
      if (abs(A(k,j)) > abs(A(pivot_row,j))) pivot_row = k;
    // swap the rows if we found a better pivot:
    if (pivot_row!=j) {
      A.swap_rows(j,pivot_row);
      std::swap(b(j), b(pivot_row));
    }
    // elimination:
    for (Index i = j+1; i<n; ++i) {
      const double pivot = A(j,j);
      if (pivot==0) error("can't solve: pivot==0");
      const double mult = A(i,j)/pivot;
      A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
      b(i) -= mult*b(j);
    }
  }
}
*/


Vector classical_gaussian_elimination(Matrix A, Vector b)
{
  classical_elimination(A, b);
  return back_substitution(A, b);
}


int randint(int min, int max) {
  auto t1 = std::chrono::system_clock::now();
  auto time_point_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(t1);
  unsigned seed = static_cast<unsigned>(time_point_ns.time_since_epoch().count());
  seed = 1;
  static default_random_engine ran{seed};
  return uniform_int_distribution<>{min,max}(ran);
}


int randint(int max) {
  return randint(0,max);
}


Matrix random_matrix(Index n) {
  Matrix m(n,n);
  for (Index i = 0; i<n; i++)
	for (Index j = 0; j<n; j++)
	  m(i,j) = randint(10);
  return m;
}

Vector random_vector(Index n) {
  Vector v(n);
  //default_random_engine ran{}; // generates integers
  // alternatives:  linear_congurential_engine, mersenne_twister_engine, and random_device.
  //uniform_real_distribution<> ureal{0,max}; // maps ints into doubles // in [0:max)
  for (Index i = 0; i < n; ++i)
	v(i) = randint(10); //ureal(ran);
  return v; 
}


Vector operator*(const Matrix& m, const Vector& u)
{
  const Index n = m.dim1();
  Vector v(n);
  for (Index i = 0; i<n; ++i) v(i) = dot_product(m[i],u);
  return v;
}

Matrix operator*(const Matrix& A, const Matrix &B) {
  if (A.dim2()!=B.dim1())
	{
	  cerr<<"Multiplication not defined for these dimensions"<<endl;
	  throw Elim_failure(1);
	}
  const Index n = A.dim1();
  const Index m = B.dim2();
  const Index K = B.dim1();
  Matrix R(n,m);

  // inefficient procedure, must be improved
  for (Index i=0;i<n;++i)
	for (Index j=0;j<m;++j)	{
	  //R(i,j)=0; 
	  for (Index k=0;k<K;++k)		
		R(i,j) += A(i,k)*B(k,j);
	}
  return R;
  
}


bool AllClose(const Matrix& A, const Matrix& B, double rtol=1e-05, double atol=1e-08) {
  if (A.dim1()!=B.dim1() || A.dim2()!=B.dim2())
	{
	  cerr<<"Matrix dimensions differ"<<endl;
	  return false;
	}
  for (Index i =0;i<A.dim1();++i)
	for (Index j =0;j<A.dim1();++j)
	  if (abs(A(i,j)-B(i,j)) > atol + rtol * abs(B(i,j)) ) {
		cout<<A(i,j)<<" "<<B(i,j)<<endl;
		return false;
	  }
  return true;
}


void solve_random_system(Index n)
{
  Matrix A = random_matrix(n);
  //Vector B = random_vector(n);
  cout << "A = " << A << '\n';
  //cout << "b = " << b << '\n';
  try {
    //Vector x = classical_gaussian_elimination(A, b);
    /*cout << "classical elim solution is x = " << x << '\n';
    Vector v = A*x;
    cout << " A*x = " << v << '\n';*/
	Matrix I = inverse_by_gauss(A);
	//cout<<"A= "<<A;
	cout << "Inverse = "<<I<<endl;
	Matrix C=A*I;
	cout <<"A*I"<<std::fixed<<std::setprecision(3) << C <<endl;
	if ( AllClose(C, identityMatrix(n)) )
	  cout <<"Ok" <<endl;
	else
	  cout <<"Not equal" <<endl;
  }
  catch(const exception& e) {
    cerr << e.what() << '\n';
  }
}



int main (int argc, char **argv) {
  if (argc!=2) {
	cerr<<"Run as: gauss [size]"<<endl;
	exit(EXIT_FAILURE);
  }
  int n = atoi(argv[1]);
  solve_random_system(n);
  exit(EXIT_SUCCESS);
}
