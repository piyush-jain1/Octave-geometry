#include <iostream>
#include <octave/oct.h>
#include <octave/parse.h>
#include <octave/Cell.h>
#include "clipper.hpp"


DEFUN_DLD(polyUnion, args, , "polyUnion help")
{	

	int nargin = args.length();
	if(nargin != 2)		print_usage();
	else
	{	
		Cell x=args(0).cell_value();
      		Cell y=args(1).cell_value();
		ClipperLib::Paths subj1,subj2;
		for(int i = 0; i < x.numel(); ++i)
		{
			if (x(i).numel()==y(i).numel())
			{
				//Elements of the cell array can only be vector columns or rows
				Array<int> xcor=x(i).vector_value();
				Array<int> ycor=y(i).vector_value();

				ClipperLib::Path p;

				for(int j = 0 ; j < x(i).numel(); ++j)
				{
					ClipperLib::IntPoint ip;
					ip.X = xcor(j);
					ip.Y = ycor(j);
					p.push_back(ip);
				}

				if(i == 0)		
				{
					subj1.push_back(p);
				}
				else if(i == 1)	
				{
					subj2.push_back(p);
				}
			}
		}

		ClipperLib::Clipper c;

		c.AddPaths(subj1, ClipperLib::ptSubject, true);
	  	c.AddPaths(subj2, ClipperLib::ptSubject,    true);

		ClipperLib::Paths solution;
		c.Execute(ClipperLib::ctUnion, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

		std::cout<<"Union conatins "<<solution.size()<<" disjoint polygon(s)"<<std::endl<<std::endl;
		
		for(int i = 0; i < solution.size(); ++i)
		{
			ClipperLib::Path p3 = solution.at(i);
			//Vertex i.j represents jth vertex of ith disjoint polygon of the union
			for(int j = 0; j < p3.size(); ++j)
			{
			    ClipperLib::IntPoint ip = p3.at(j);
			    std::cout<<"Vertex "<<i+1<<"."<<j+1<<" : "<<ip.X<<" "<<ip.Y<<std::endl;
			}
	        
		}
	}
	return 	octave_value_list();
}

/*

%!test
%!x={[0 100 100 0],[50 150 150 50]}
%!y={[0 0 100 100],[0 0 100 100]}

*/
