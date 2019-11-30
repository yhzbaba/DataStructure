#pragma once
#include "element.h"

using namespace std;

/*��������:
  sourcelist[t],sourcelist[t+1],...,sourcelist[m]
  sourcelist[m+1],soutcelist[m+2],...,sourcelist[n]
  �����ź��򣬰����Ǻϲ���һ������:
  mergedlist[t],mergedlist[t+1],...,mergedlist[n]��,
  ʹ�õ����������ź����.*/
template<class T>
void merge(Element<T>* sourcelist, Element<T>* mergedlist, const int t, const int m, const int n)
{
	int i = t;
	int j = m + 1;
	int k = t;
	while (i <= m && j <= n)
	{
		if (sourcelist[i].GetKey() <= sourcelist[j].GetKey())
		{
			mergedlist[k] = sourcelist[i];
			i++;
		}
		else
		{
			mergedlist[k] = sourcelist[j];
			j++;
		}
		k++;
	}
	//����������¼��
	if (i > m)
		for (int p = k; p <= n; p++)
			mergedlist[p] = sourcelist[j + p - k];
	else
		for (int p = k; p <= n; p++)
			mergedlist[p] = sourcelist[i + p - k];
}
