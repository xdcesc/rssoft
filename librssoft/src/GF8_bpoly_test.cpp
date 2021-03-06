/*
     Copyright 2013 Edouard Griffiths <f4exb at free dot fr>

     This file is part of RSSoft. A Reed-Solomon Soft Decoding library

     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 51 Franklin Street, Boston, MA  02110-1301  USA

	 Original from Arash Partow (see original copytight notice).
	 Modified and included in RSSoft in gf sub-namespace.

	 Tests of Galois Field sub-library on GF(8)[X,Y]

*/

#include <iostream>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "GFq.h"
#include "GFq_Element.h"
#include "GFq_Polynomial.h"
#include "GF2_Element.h"
#include "GF2_Polynomial.h"
#include "GFq_BivariateMonomial.h"
#include "GFq_BivariatePolynomial.h"

/*
   P(X) = X^3+X+1
   p(x) = 1x^3+0x^2+1x^1+1x^0
             1    0    1    1 <-MSB
*/
rssoft::gf::GF2_Element ppe[4] = {1,1,0,1};
rssoft::gf::GF2_Polynomial ppoly(4,ppe);
/*
  A Galois Field of type GF(2^3)
*/
rssoft::gf::GFq gf8(3,ppoly);


// ================================================================================================
int main(int argc, char *argv[])
{
	unsigned int k = 3;

	rssoft::gf::GFq_BivariateMonomial m_XY(rssoft::gf::GFq_Element(gf8,1),1,1); // X*Y
	rssoft::gf::GFq_BivariateMonomial m_aXY(rssoft::gf::GFq_Element(gf8,2),1,1); // a*X*Y
	rssoft::gf::GFq_BivariateMonomial m_X2(rssoft::gf::GFq_Element(gf8,1),2,0);  // X^2
	rssoft::gf::GFq_BivariateMonomial m_1(rssoft::gf::GFq_Element(gf8,1),0,0);   // 1
	rssoft::gf::GFq_BivariateMonomial m_a(rssoft::gf::GFq_Element(gf8,2),0,0);   // a
	rssoft::gf::GFq_BivariateMonomial m_aX3(rssoft::gf::GFq_Element(gf8,2),3,0); // a*X^3
	rssoft::gf::GFq_BivariateMonomial m_Y2(rssoft::gf::GFq_Element(gf8,1),0,2);  // Y^2
	rssoft::gf::GFq_BivariateMonomial m_X(rssoft::gf::GFq_Element(gf8,1),1,0);   // X
	rssoft::gf::GFq_BivariateMonomial m_Y(rssoft::gf::GFq_Element(gf8,1),0,1);   // Y

	rssoft::gf::GFq_Element a(gf8,2);
	rssoft::gf::GFq_Element one(gf8,1);

	std::cout << "m_XY  = " << m_XY << " wdeg = " << m_XY.first.wdeg(1,k-1) << std::endl;
	std::cout << "m_aXY = " << m_aXY << " wdeg = " << m_aXY.first.wdeg(1,k-1) << std::endl;
	std::cout << "m_X2  = " << m_X2 << " wdeg = " << m_X2.first.wdeg(1,k-1) << std::endl;
	std::cout << "m_1   = " << m_1 << " wdeg = " << m_1.first.wdeg(1,k-1) << std::endl;
	std::cout << "m_aX3 = " << m_aX3 << " wdeg = " << m_aX3.first.wdeg(1,k-1) << std::endl;
	std::cout << "m_Y2  = " << m_Y2 << " wdeg = " << m_Y2.first.wdeg(1,k-1) << std::endl;
	std::cout << "m_X  = " << m_X << " wdeg = " << m_X.first.wdeg(1,k-1) << std::endl;
	std::cout << "m_Y  = " << m_Y << " wdeg = " << m_Y.first.wdeg(1,k-1) << std::endl;

	std::vector<rssoft::gf::GFq_BivariateMonomial> monos_P;
	monos_P.push_back(m_XY); // X*Y
	monos_P.push_back(m_X2); // X^2
	monos_P.push_back(m_1); // 1
	monos_P.push_back(m_aX3); // a*X^3

	rssoft::gf::GFq_BivariatePolynomial P(1,k-1);
	P.init(monos_P);

	std::cout << std::endl;
	std::cout << "P(X,Y) = " << P << std::endl;

	std::vector<rssoft::gf::GFq_BivariateMonomial> monos_Q;
	monos_Q.push_back(m_aXY); // a*X*Y
	monos_Q.push_back(m_Y2); // Y^2

	rssoft::gf::GFq_BivariatePolynomial Q(1,k-1);
	Q.init(monos_Q);

	std::cout << "Q(X,Y) = " << Q << std::endl;
	
	std::cout << "P+Q = " << P+Q << std::endl;
	std::cout << "P+a = " << P + a << std::endl;
	std::cout << "Q+a = " << Q + a << std::endl;

	std::vector<rssoft::gf::GFq_BivariateMonomial> monos_U;
	monos_U.push_back(m_1);
	monos_U.push_back(m_X);

	rssoft::gf::GFq_BivariatePolynomial U(1,k-1);
	U.init(monos_U);

	std::cout << std::endl;
	std::cout << "U(X,Y) = " << U << std::endl;
	std::cout << "U^2(X,Y) = " << U*U << std::endl;
	std::cout << "P*U = " << P*U << std::endl;
	std::cout << "Q/m_Y = " << Q/m_Y << std::endl;
	std::cout << "Q/a = " << Q/a << std::endl;

	std::vector<rssoft::gf::GFq_BivariateMonomial> monos_U1;
	monos_U1.push_back(m_a);
	monos_U1.push_back(m_XY);

	rssoft::gf::GFq_BivariatePolynomial U1(1,k-1);
	U1.init(monos_U1);

	std::cout << std::endl;
	std::cout << "U1(X,Y) = " << U1 << std::endl;
	std::cout << "U1^4(X,Y) = " << (U1^4) << std::endl;

	std::cout << std::endl;
	std::cout << "P(a,a^2) = " << P(a,a^2) << std::endl;
	std::cout << "P(a,1) = " << P(a,one) << std::endl;
	std::cout << "P(1,a^2) = " << P(one,a^2) << std::endl;

	std::cout << std::endl;
	std::cout << "P(X,0) = " << P.get_X_0() << std::endl;
	std::cout << "P(0,Y) = " << P.get_0_Y() << std::endl;
	std::cout << "Q(X,0) = " << Q.get_X_0() << std::endl;
	std::cout << "Q(0,Y) = " << Q.get_0_Y() << std::endl;
	
	rssoft::gf::GFq_BivariatePolynomial P1 = P*m_X2;

	std::cout << std::endl;
	std::cout << "P1(X,Y) = " << P1 << std::endl;
	std::cout << "P1*(X,Y) = " << star(P1) << std::endl;
	std::cout << "P*(X,Y)  = " << star(P) << std::endl;
	
	std::cout << std::endl;
	std::cout << "P(X,Y)^[0,0] = " << dHasse(0,0,P) << std::endl;
	std::cout << "P(X,Y)^[1,0] = " << dHasse(1,0,P) << std::endl;
	std::cout << "P(X,Y)^[0,1] = " << dHasse(0,1,P) << std::endl;
	std::cout << "P(X,Y)^[1,1] = " << dHasse(1,1,P) << std::endl;
	std::cout << "P(X,Y)^[2,0] = " << dHasse(2,0,P) << std::endl;
	std::cout << "P(X,Y)^[0,2] = " << dHasse(0,2,P) << std::endl;


	rssoft::gf::GFq_BivariatePolynomial Y0(1,k-1);
	rssoft::gf::GFq_BivariatePolynomial Y2(1,k-1);
	rssoft::gf::GFq_BivariatePolynomial X5(1,k-1);
	Y0.init_y_pow(gf8, 0);
	Y2.init_y_pow(gf8, 2);
	X5.init_x_pow(gf8, 5);

	std::cout << std::endl;
	std::cout << "Y0(X,Y) = " << Y0 << std::endl;
	std::cout << "Y2(X,Y) = " << Y2 << std::endl;
	std::cout << "X5(X,Y) = " << X5 << std::endl;

	std::cout << std::endl;
	std::cout << "lm(P) = " << P.get_leading_monomial() << std::endl;
	std::cout << "lm(P1) = " << P1.get_leading_monomial() << std::endl;
	std::cout << "lm(Q) = " << Q.get_leading_monomial() << std::endl;
	std::cout << "lm(U) = " << U.get_leading_monomial() << std::endl;

	rssoft::gf::GFq_BivariateMonomial m_a3X(rssoft::gf::GFq_Element(gf8,gf8.alpha(3)),1,0);  // a^3*X
	rssoft::gf::GFq_BivariateMonomial m_a2X2(rssoft::gf::GFq_Element(gf8,gf8.alpha(2)),2,0); // a^2*X^2
	rssoft::gf::GFq_BivariateMonomial m_a4X5(rssoft::gf::GFq_Element(gf8,gf8.alpha(4)),5,0); // a^4*X^5
	rssoft::gf::GFq_BivariateMonomial m_aX6(rssoft::gf::GFq_Element(gf8,2),6,0);             // a^1*X^6
	rssoft::gf::GFq_BivariateMonomial m_a5X7(rssoft::gf::GFq_Element(gf8,gf8.alpha(5)),7,0); // a^5*X^7
	rssoft::gf::GFq_BivariateMonomial m_a5X8(rssoft::gf::GFq_Element(gf8,gf8.alpha(5)),8,0); // a^5*X^8

	std::vector<rssoft::gf::GFq_BivariateMonomial> monos_V;
	monos_V.push_back(m_1);
	monos_V.push_back(m_a3X);
	monos_V.push_back(m_a2X2);
	monos_V.push_back(m_aX3);
	monos_V.push_back(m_a4X5);
	monos_V.push_back(m_aX6);
	monos_V.push_back(m_a5X7);
	monos_V.push_back(m_a5X8);

	rssoft::gf::GFq_BivariatePolynomial V(1,k-1);
	V.init(monos_V);

	rssoft::gf::GFq_Element a5(gf8,gf8.alpha(5));

	std::cout << std::endl;
	std::cout << "V(X,Y) = " << V << std::endl;
	std::cout << "V(a^5,0) = " << V(a5, rssoft::gf::GFq_Element(gf8,0)) << std::endl;

	rssoft::gf::GFq_BivariatePolynomial X1(1,k-1);
	X1.init_x_pow(gf8, 1);

	std::cout << std::endl;
	std::cout << "X1(X,Y) = " << X1 << std::endl;
	std::cout << "P(X,Q(X,Y))  = " << P(X1,Q) << std::endl;
	std::cout << "Q(X,U1(X,Y)) = " << Q(X1,U1) << std::endl;
}


