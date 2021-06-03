#include<iostream>
#include<fstream>
#include<conio.h>
#include"help.h"
using namespace std;
class pixel
{
public:
	int r=0;
	int g=0;
	int b=0;
	int classlabel;
};

bool chechloop(pixel*a,pixel*b,int size)
{
	int flag = 1;
	for (int i = 0; i < size; i++)
	{
		if (a[i].r != b[i].r || a[i].g != b[i].g || a[i].b != b[i].b)
		{
			flag = 0;
			break;
		}
	}
	if (flag == 1)
		return true;
	else
		return false;
}

int Euclidean_distance(pixel a,pixel b)
{
	int r = (a.r - b.r)*(a.r - b.r);
	int g = (a.g - b.g)*(a.g - b.g);
	int B = (a.b - b.b)*(a.b - b.b);
	int sum = r + g + B;
	int dist = sqrt(sum);
	return dist;
}
void printimage(pixel*arr)
{
	int x1 = 400, x2 = 402, y1 = 40, y2 = 42;
	int count = 0;
	for (int i = 0; i < 44000; i++)
	{
		myRect(x1, y1, x2, y2, arr[i].r, arr[i].g, arr[i].b, arr[i].r, arr[i].g, arr[i].b);
		x1 = x1 + 2;
		x2 = x2 + 2;
		count++;
		if (count == 200)
		{
			count = 0;
			y1 = y1 + 2;
			y2 = y2 + 2;
			x1 = 400;
			x2 = 402;
		}
	}
}
int main()
{
	pixel*p = new pixel[44000];
	ifstream fin;
	fin.open("pixel.txt");
	for (int i = 0; i < 44000; i++)
	{
		fin >> p[i].r;
		fin >> p[i].g;
		fin >> p[i].b;
		p[i].classlabel = 0;
	}
	printimage(p);
	cout << "Enter the value of K" << endl;
	int K;
	cin >> K;
	pixel*major = new pixel[K];
	for (int i = 0; i < K; i++)
	{
		int r = rand() % 44000;
		major[i] = p[r];
	}
	int i = 0;
	int*arr_k = new int[K];
	pixel*check = new pixel[K];
	while (i < 100)
	{
		for (int i = 0; i < K; i++)     
		{
			check[i].r = major[i].r;
			check[i].g = major[i].g;
			check[i].b = major[i].b;
		}
		for (int j = 0; j < 44000; j++)
		{
			for (int l = 0; l < K; l++)
			{
				arr_k[l] = Euclidean_distance(p[j], major[l]);
			}
			int minimum = 99999;
			int temp;
			int index = 0;
			for (int b = 0; b < K; b++)
			{
				temp = arr_k[b];
				if (temp < minimum)
				{
					minimum = temp;
					index = b + 1;
				}
			}
			p[j].classlabel = index;
		}
		pixel*temp=new pixel[K];
		int count;
		int t_var = 1;
		for (int j = 0; j < K; j++)
		{
			count = 0;
			for (int l = 0; l < 44000; l++)
			{
				if (p[l].classlabel == t_var)
				{
					temp[j].r = temp[j].r + p[l].r;
					temp[j].g = temp[j].g + p[l].g;
					temp[j].b = temp[j].b + p[l].b;
					count++;
				}
			}
			t_var++;
			temp[j].r = temp[j].r / count;
			temp[j].g = temp[j].g / count;
			temp[j].b = temp[j].b / count;

			major[j].r = temp[j].r;
			major[j].g = temp[j].g;
			major[j].b = temp[j].b;
		}
		bool a = chechloop(major, check,K);
		if (a == true)
		{
			break;
		}
		i++;
	}
	cout<<"Iterations : " << i << endl;
	for (int i = 0; i < 44000; i++)
	{
		for (int j = 0; j < K; j++)
		{
			arr_k[j] = Euclidean_distance(p[i], major[j]);
		}
		int minimum = 99999;
		int temp;
		int index = 0;
		for (int b = 0; b < K; b++)
		{
			temp = arr_k[b];
			if (temp < minimum)
			{
				minimum = temp;
				index = b;
			}
		}
		p[i].r = major[index].r;
		p[i].g = major[index].g;
		p[i].b = major[index].b;
	}
	printimage(p);

}