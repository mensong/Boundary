// Boundary.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Boundary.h"

#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>

#include "arr_rational_nt.h"
#include <CGAL/Cartesian.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Arr_extended_dcel.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/graph_traits_dual_arrangement_2.h>
#include <CGAL/Arr_face_index_map.h>

#include <climits>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/visitors.hpp>

#include <fstream>

//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef K::Point_2 Point_2;

typedef CGAL::Cartesian<Number_type>                         Kernel;
typedef Kernel::Point_2                                      Point_2;


BOUNDARY_API int calcConvexHull(CPoint_2 resuls[], CPoint_2 points[], int pointsCount)
{
#if 1
	Point_2* _points = new Point_2[pointsCount];
	Point_2* _result = new Point_2[pointsCount];
	for (int i = 0; i < pointsCount; ++i)
	{
		_points[i] = Point_2(points[i].x, points[i].y);
	}
	//Point_2 points[12] = {
	//	Point_2(-171.79633191652559, 233.85308335930412),
	//	Point_2(1210.6164697451459, 451.11741505029863),
	//	Point_2(950.27155588391054, -459.03433107004116),
	//	Point_2(932.16578272320317, 204.90027365297669),
	//	Point_2(392.97641900779024, 120.15958214483196),
	//	Point_2(932.16578272320317, 204.90027365297669),
	//	Point_2(-171.79633191652559, 233.85308335930412),
	//	Point_2(1210.6164697451459, 451.11741505029863),
	//	Point_2(950.27155588391054, -459.03433107004116),
	//	Point_2(932.16578272320317, 204.90027365297669),
	//	Point_2(392.97641900779024, 120.15958214483196),
	//	Point_2(932.16578272320317, 204.90027365297669)
	//};
	//Point_2 result[12];

	Point_2 *ptr = CGAL::convex_hull_2(_points, _points + pointsCount, _result);
	int nPointsOnConvexHull = ptr - _result;
	//std::cout << nPointsOnConvexHull << " points on the convex hull:" << std::endl;
	for (int i = 0; i < nPointsOnConvexHull; ++i)
	{
		resuls[i].x = _result[i].x().to_double();
		resuls[i].y = _result[i].y().to_double();
		//std::cout << result[i].x().to_double() << "," << result[i].y().to_double() << std::endl;
	}

	delete[] _points;
	delete[] _result;

	return nPointsOnConvexHull;
#else
	return convexHull(resuls, points, pointsCount);
#endif
}



// A property map that reads/writes the information to/from the extended 
// face.
template <typename Arrangement, class Type> class Extended_face_property_map {
public:
	typedef typename Arrangement::Face_handle       Face_handle;

	// Boost property type definitions.
	typedef boost::read_write_property_map_tag      category;
	typedef Type                                    value_type;
	typedef value_type&                             reference;
	typedef Face_handle                             key_type;

	// The get function is required by the property map concept.
	friend reference get(const Extended_face_property_map&, key_type key)
	{
		return key->data();
	}

	// The put function is required by the property map concept.
	friend void put(const Extended_face_property_map&,
		key_type key, value_type val)
	{
		key->set_data(val);
	}
};

//typedef CGAL::Cartesian<Number_type>                         Kernel;
typedef CGAL::Arr_segment_traits_2<Kernel>                   Traits_2;
typedef CGAL::Arr_face_extended_dcel<Traits_2, unsigned int> Dcel;
typedef CGAL::Arrangement_2<Traits_2, Dcel>                  Ex_arrangement;
typedef CGAL::Dual<Ex_arrangement>                           Dual_arrangement;
typedef CGAL::Arr_face_index_map<Ex_arrangement>             Face_index_map;
typedef Extended_face_property_map<Ex_arrangement, unsigned int> Face_property_map;
typedef Kernel::Segment_2                                    Segment_2;

BOUNDARY_API int calcArrangement(CPoint_2 resuls[], int* arrFaceSegsLen, CPoint_2 segs[], int nSegs)
{
	// Construct an arrangement of seven intersecting line segments.	
	Ex_arrangement  arr;

	//Point_2 p1(1, 1), p2(1, 4), p3(2, 2), p4(3, 7), p5(4, 4), p6(7, 1), p7(9, 3);
	//insert(arr, Segment_2(p1, p6));
	//insert(arr, Segment_2(p1, p4));  insert(arr, Segment_2(p2, p6));
	//insert(arr, Segment_2(p3, p7));  insert(arr, Segment_2(p3, p5));
	//insert(arr, Segment_2(p6, p7));  insert(arr, Segment_2(p4, p7));

	//insert(arr, Segment_2(Point_2(100.0, 100.0), Point_2(0.5, 100.0)));
	//insert(arr, Segment_2(Point_2(0.5, 100.0), Point_2(0.5, 0.5)));
	//insert(arr, Segment_2(Point_2(100.0, 0.5), Point_2(0.5, 0.5)));
	//insert(arr, Segment_2(Point_2(100.0, 0.5), Point_2(100.0, 100.0)));

	//insert(arr, Segment_2(Point_2(200.0, 100.0), Point_2(100.0, 100.0)));
	
	//std::ofstream ofile;
	//ofile.open("points.txt");

	for (int i = 0; i < nSegs * 2; i+=2)
	{
		insert(arr, Segment_2(
			Point_2(segs[i].x, segs[i].y), 
			Point_2(segs[i+1].x, segs[i+1].y)
		));
		//ofile <<  std::to_string(segs[i].x) << "," << std::to_string(segs[i].y) << " " << std::to_string(segs[i + 1].x) << "," << std::to_string(segs[i + 1].y) << std::endl;
	}

	//ofile.close();

	// Create a mapping of the arrangement faces to indices.
	Face_index_map  index_map(arr);

	// Perform breadth-first search from the unbounded face, using the event
	// visitor to associate each arrangement face with its discover time.
	unsigned int    time = 0;
	boost::breadth_first_search(Dual_arrangement(arr), arr.unbounded_face(),
		boost::vertex_index_map(index_map).visitor
		(boost::make_bfs_visitor
		(stamp_times(Face_property_map(), time,
		boost::on_discover_vertex()))));

	// Print the discover time of each arrangement face.
	int r = 0;
	int p = 0;
	Ex_arrangement::Face_iterator  fit;
	for (fit = arr.faces_begin(); fit != arr.faces_end(); ++fit)
	{		
		//std::cout << "Discover time " << fit->data() << " for ";
		//if (fit != arr.unbounded_face()) {
		//	std::cout << "face ";
		//	print_ccb<Ex_arrangement>(fit->outer_ccb());
		//}
		//else
		//	std::cout << "the unbounded face." << std::endl;
		
		if (fit != arr.unbounded_face()) 
		{
			typename Ex_arrangement::Ccb_halfedge_const_circulator  circ = fit->outer_ccb();
			typename Ex_arrangement::Ccb_halfedge_const_circulator  curr = circ;
			typename Ex_arrangement::Halfedge_const_handle          he;

			int segCount = 0;
			do
			{
				he = curr;

				resuls[p].x = he->curve().source().x().to_double();
				resuls[p].y = he->curve().source().y().to_double();
				resuls[p + 1].x = he->curve().target().x().to_double();
				resuls[p + 1].y = he->curve().target().y().to_double();

				p += 2;
				++segCount;

				//std::cout <<
				//	"[" << he->curve().source().x().to_double() << "," << he->curve().source().y().to_double() << " -- " <<
				//	he->curve().target().x().to_double() << "," << he->curve().target().y().to_double() << "]   " << std::endl;

				++curr;
			} while (curr != circ);
						
			arrFaceSegsLen[r] = segCount;
			++r;
		}
	}

	return r;
}

