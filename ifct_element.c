//
//  ifs_element.c
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "C:\Users\USER\Desktop\Univ\2022_2-2\전자공학프로그래밍\기말 프로젝트\basecode\ifct_element.h"

typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
} place_t;

char countryName[N_PLACE+1][MAX_PLACENAME] =
{   "Seoul",
    "Jeju",
    "Tokyo",
    "LosAngeles",
    "NewYork",
    "Texas",
    "Toronto",
    "Paris",
    "Nice",
    "Rome",
    "Milan",
    "London",
    "Manchester",
    "Basel",
    "Luzern",
    "Munich",
    "Frankfurt",
    "Berlin",
    "Barcelona",
    "Madrid",
    "Amsterdam",
    "Stockholm",
    "Oslo",
    "Hanoi",
    "Bangkok",
    "KualaLumpur",
    "Singapore",
    "Sydney",
    "SaoPaulo",
    "Cairo",
    "Beijing",
    "Nairobi",
    "Cancun",
    "BuenosAires",
    "Reykjavik",
    "Glasgow",
    "Warsow",
    "Istanbul",
    "Dubai",
    "CapeTown",
    "Unrecognized"
};

char* ifctele_getPlace 

typedef struct ifs_ele {
	int index;
	int age;
	int time;
	place_t place[N_HISTORY];
	//number -> int
	//age -> int
	//infection timing -> int
	//path before infection -> place_t (enum arrangement (N_HISTORY))
	
} ifs_ele_t;




void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY]);
{
	ifs_ele_t* ptr;
	
	ptr = malloc();
	ptr->index = index;         // 구조체를 만들어서 환자 정보를 저장 
	
	//free는 하면 안됨
	
	return ptr;
}



int ifctele_getAge(void* obj)
{
	ifs_ele_t* Ptr = (ifs_ele_t*)obj;
	
	return ptr->age;
}                                            // 나머지 함수들도 이와 유사하게 코딩하면 됨 


char* ifctele_getPlaceName(int placeIndex);
int ifctele_getHistPlaceIndex(void* obj, int index);
unsigned int ifctele_getinfestedTime(void* obj);



void ifcele_printElement(void* obj)
{
	ifs_ele_t* Ptr = (ifs_ele_t*)obj;
	
	printf("Age : %i\n", ptr-<age);   //print elements
}




