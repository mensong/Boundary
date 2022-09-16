// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Boundary.h"
#include <string>

int main()
{
	typedef int(*fn_calcConvexHull)(CPoint_2 resuls[], CPoint_2 segs[], int nSegs);
	typedef int(*fn_calcArrangement)(CPoint_2 resuls[], int* faceLen, CPoint_2 segs[], int nSegs);

	fn_calcConvexHull fncalcConvexHull = NULL;
	fn_calcArrangement fncalcArrangement = NULL;

	HMODULE hDll = ::LoadLibraryA("Boundary.dll");
	DWORD err = ::GetLastError();
	if (hDll)
	{
		fncalcConvexHull = (fn_calcConvexHull)GetProcAddress(hDll, "calcConvexHull");
		if (!fncalcConvexHull)
		{
			FreeLibrary(hDll);
			printf(("\n不能加载模块:Boundary.dll"));
			return 0;
		}

		fncalcArrangement = (fn_calcArrangement)GetProcAddress(hDll, "calcArrangement");
		if (!fncalcArrangement)
		{
			FreeLibrary(hDll);
			printf(("\n不能加载模块:Boundary.dll"));
			return 0;
		}
	}
	else
	{
		printf(("\n找不到模块:Boundary.dll"));
		return 0;
	}

	CPoint_2 points[104] = {
		CPoint_2(11193.112195,-1032.184503), CPoint_2(11301.292429,413.092078),
		CPoint_2(11416.553705,-1262.373752), CPoint_2(11522.384515,151.514772),
		CPoint_2(11193.112195,-1032.184503), CPoint_2(11416.553705,-1262.373752),
		CPoint_2(11301.292429,413.092078), CPoint_2(11522.384515,151.514772),
		CPoint_2(9689.004790,-1099.860566), CPoint_2(11193.112195,-1032.184503),
		CPoint_2(9951.257660,-1328.303530), CPoint_2(11416.553705,-1262.373752),
		CPoint_2(9689.004790,-1099.860566), CPoint_2(9951.257660,-1328.303530),
		CPoint_2(11193.112195,-1032.184503), CPoint_2(11416.553705,-1262.373752),
		CPoint_2(9830.887462,-2627.313518), CPoint_2(9689.004790,-1099.860566),
		CPoint_2(10050.137413,-2392.803998), CPoint_2(9951.257660,-1328.303530),
		CPoint_2(9830.887462,-2627.313518), CPoint_2(10050.137413,-2392.803998),
		CPoint_2(9689.004790,-1099.860566), CPoint_2(9951.257660,-1328.303530),
		CPoint_2(11391.159863,-2666.936658), CPoint_2(9830.887462,-2627.313518),
		CPoint_2(11646.528196,-2433.344364), CPoint_2(10050.137413,-2392.803998),
		CPoint_2(11391.159863,-2666.936658), CPoint_2(11646.528196,-2433.344364),
		CPoint_2(9830.887462,-2627.313518), CPoint_2(10050.137413,-2392.803998),
		CPoint_2(11297.533466,-4136.546491), CPoint_2(11391.159863,-2666.936658),
		CPoint_2(11552.894859,-3903.063139), CPoint_2(11646.528196,-2433.344364),
		CPoint_2(11297.533466,-4136.546491), CPoint_2(11552.894859,-3903.063139),
		CPoint_2(11391.159863,-2666.936658), CPoint_2(11646.528196,-2433.344364),
		CPoint_2(13096.794374,-4183.026544), CPoint_2(11297.533466,-4136.546491),
		CPoint_2(12856.794374,-3936.746591), CPoint_2(11552.894859,-3903.063139),
		CPoint_2(13096.794374,-4183.026544), CPoint_2(12856.794374,-3936.746591),
		CPoint_2(11297.533466,-4136.546491), CPoint_2(11552.894859,-3903.063139),
		CPoint_2(13096.794374,-2770.761409), CPoint_2(13096.794374,-4183.026544),
		CPoint_2(12856.794374,-2516.567790), CPoint_2(12856.794374,-3936.746591),
		CPoint_2(13096.794374,-2770.761409), CPoint_2(12856.794374,-2516.567790),
		CPoint_2(13096.794374,-4183.026544), CPoint_2(12856.794374,-3936.746591),
		CPoint_2(14962.962247,-2878.045446), CPoint_2(13096.794374,-2770.761409),
		CPoint_2(14709.068677,-2623.053100), CPoint_2(12856.794374,-2516.567790),
		CPoint_2(14962.962247,-2878.045446), CPoint_2(14709.068677,-2623.053100),
		CPoint_2(13096.794374,-2770.761409), CPoint_2(12856.794374,-2516.567790),
		CPoint_2(14869.796632,-1125.407920), CPoint_2(14962.962247,-2878.045446),
		CPoint_2(14641.726009,-1356.198513), CPoint_2(14709.068677,-2623.053100),
		CPoint_2(14869.796632,-1125.407920), CPoint_2(14641.726009,-1356.198513),
		CPoint_2(14962.962247,-2878.045446), CPoint_2(14709.068677,-2623.053100),
		CPoint_2(13257.302657,-1058.851195), CPoint_2(14869.796632,-1125.407920),
		CPoint_2(13017.302657,-1289.149396), CPoint_2(14641.726009,-1356.198513),
		CPoint_2(13257.302657,-1058.851195), CPoint_2(13017.302657,-1289.149396),
		CPoint_2(14869.796632,-1125.407920), CPoint_2(14641.726009,-1356.198513),
		CPoint_2(13257.302657,231.343134), CPoint_2(13257.302657,-1058.851195),
		CPoint_2(13017.302657,12.609673), CPoint_2(13017.302657,-1289.149396),
		CPoint_2(13257.302657,231.343134), CPoint_2(13017.302657,12.609673),
		CPoint_2(13257.302657,-1058.851195), CPoint_2(13017.302657,-1289.149396),
		CPoint_2(11301.292429,413.092078), CPoint_2(13257.302657,231.343134),
		CPoint_2(11522.384515,151.514772), CPoint_2(13017.302657,12.609673),
		CPoint_2(11301.292429,413.092078), CPoint_2(11522.384515,151.514772),
		CPoint_2(13257.302657,231.343134), CPoint_2(13017.302657,12.609673),
		CPoint_2(9830.887462,-2627.313518), CPoint_2(11297.533466,-4136.546491),
		CPoint_2(13096.794374,-4183.026544), CPoint_2(14962.962247,-2878.045446),
		CPoint_2(14869.796632,-1125.407920), CPoint_2(13257.302657,231.343134),
		CPoint_2(11301.292429,413.092078), CPoint_2(9689.004790,-1099.860566),
	};
	CPoint_2 result[104 * 104];

	int n = fncalcConvexHull(result, points, 104);
	int arrFaceSegsLen[104 * 104];
	int nFace = fncalcArrangement(result, arrFaceSegsLen, points, 52);
	printf("%d\n", nFace);
	int p = 0;
	for (int i = 0; i < nFace; ++i)
	{
		std::string s;
		int faceSegsLen = arrFaceSegsLen[i];
		for (int j = 0; j < faceSegsLen; ++j)
		{
			s += std::to_string(result[p].x) + "," + std::to_string(result[p].y) + " " + std::to_string(result[p + 1].x) + "," + std::to_string(result[p + 1].y) + "\n";
			p += 2;
		}
		s.size();
	}

	FreeLibrary(hDll);

	system("pause");
    return 0;
}

