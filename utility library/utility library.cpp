#include <iostream>
#include "clsUtil.h"
using namespace std;



int main()
{
	clsUtil::sRand();

	//string arr1[100];
	int arr1[100] = {10,20,30,40,50,60,70,80,90, 100};
	string arr2[100] = {"Ali", "Mohammad", "Kasem", "Hamas", "Kassam", "AlQouds"};
	int arr3[100];
	int length=0, length2=0;

	//clsUtil::shufflefArray(arr2);
	//clsUtil::fillArrayWithRandomWords(arr2, 10, clsUtil::MixChar, 4);
	//clsUtil::printArrayElements(arr2, 10);

	//cout << "test" << clsUtil::tap(5)<<"test";
	string name = "Gomaa El Sherbini";

	name= clsUtil::EncryptText(name);
	name = clsUtil::DecryptText(name);
	cout << name << endl;


	cout << endl;
	system("pause>0");
}