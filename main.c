//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//
//  2112392 조신영 
//


#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2


// infester 추척하는 함수 정의 
int trackInfester(int patient_no, int *detected_time, int *place)
{
	int i, j;                        //for문을 위한 i, j 선언 
	int infIndex = -1;               //함수의 return 값인 전파자의 번호 선언, index = -1
	int infTime = *detected_time;     //감염 날짜 변수 선언 
	int infPlace = *place;            //감염 장소 변수 선언 
	int trackNum;                    //추적할 환자의 번호 변수 선언 
	int trackTime;                   //추적할 감염 시점 변수 선언 
	int trackPlace1, trackPlace2;    //추적할 감염 장소 변수 선언 (발병일, 발병 하루 전) 
	
	// data의 환자들과 시간, 장소 비교 (입력된 환자 자신 제외) 
	for (i=0; i<ifctdb_len(); i++)
	{
		if (patient_no != i)
		{
			trackNum = i;
			
			trackTime = ifctele_getinfestedTime(ifctdb_getData(i));     // 시점 -> ifctele_getinfestedTime 함수 사용 
			
			// 장소 -> ifctele_getHistPlaceIndex 함수 사용 
			trackPlace1 = ifctele_getHistPlaceIndex(ifctdb_getData(i), N_HISTORY - 1);
			trackPlace2 = ifctele_getHistPlaceIndex(ifctdb_getData(i), N_HISTORY - 2);
			
			// 전염 가능 시기의 시간, 장소 확인 
			for (j=0; j<3; j++)
			{
				if ((place[j] == trackPlace1) && (detected_time - 4 + j == trackTime))     // 발병 당일 
				{
					if (infTime > trackTime)
					{
						infIndex = trackNum;
						infTime = trackTime;
						infPlace = trackPlace1;
					}
				}
				
				if ((place[j] == trackPlace2) && (detected_time - 4 + j == trackTime - 1))      // 발병 하루 전 
				{
					if (infTime > trackTime)
					{
						infIndex = trackNum;
						infTime = trackTime;
						infPlace = trackPlace2;
					}
				}
			}
			
		}
		
	}
	
	return infIndex;     // 전파자의 번호 return 
	
} // trackInfester 함수 



// main 함수- 감염병 관리 프로그램 실행 함수 
   // 1. 특정 환자에 대한 정보 출력
   // 2. 특정 장소에서 감염이 확인된 환자 관련 정보 출력
   // 3. 특정 범위의 나이에 해당하는 환자 관련 정보 출력
   // 4. 감염 경로 및 최초 전파자 추적
   // 0. 프로그램 종료 
int main(int argc, const char * argv[]) {
    
    int menu_selection;         // menu number 선택 변수 선언 
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
    
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");     //error print
        return -1;
    }
    
    fp = fopen(argv[1],"r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);     //error print
        return -1;
    }
    
    
    
    //1-2. loading each patient informations
    
    // patientInfo_sample.txt 파일 읽어오기 
    FILE* file;
    file = fopen("patientInfo_sample.txt", "r");
    
    while ( 3 == fscanf(file, "%i %i %i", &pIndex, &age, &time))     //patient index, age, time 읽어오기 
    {
    	int i;                                     //for문을 위한 i 선언 
		for (i=0; i<5; i++)                        //place 5개 (환자의 이동경로) 저장 
    		fscanf(file, "%i", &placeHist[i]);
    		
    	ifct_element = ifctele_genElement(pIndex, age, time, placeHist);
    	
    	// linked list에 생성된 구조체 저장 : ifctdb_addTail 함수 이용 
    	ifctdb_addTail(ifct_element);
    	
    	/*
    	printf("%i 번째 환자 감염 경로 : ", 환자 번호);
    	for (5번 반복)
    		printf("%s", ifsele_getPlaceName(placeList[i]));
    	printf("\n");
    	
    	ifct_ele = ifctele_genElement(pIndex, age, time, placeHist);
    	
    	ifctdb_addTail(ifct_ele);
    	*/
	}

	
    
    //1-3. FILE pointer close
    fclose(fp);
    
    {
    	int place1, place2;
    	
    	place1 = 3;
    	place2 = 15;
    	
    	printf("The first place is %s\n\n", ifctele_getPlaceName(place1));
    	printf("The second place is %s\n\n", ifctele_getPlaceName(place2));
	}
    
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");         //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");           //MENU_AGE
        printf("4. Track the root of the infection\n");                     //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu : ");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        
        // MENU_PLACE 변수 선언 
		int i;                         //for문을 위한 i
		char place[MAX_PLACENAME];     //char 형태 장소 변수
		
		// MENU_AGE 변수 선언 
		int age_min, age_max;         //int 형태 minimum, maximum 나이 변수
		
		// MENU_TRACK 변수 선언 
		int pat_index;                //patient index 입력 받는 변수
        int infester = -1;            //infester 변수, index -1 
        int firstInf;                 //최초 전파자 변수
        
        
        switch(menu_selection)
        {
            case MENU_EXIT:          //menu_selection이 0번인 경우 
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:       //menu_selection이 1번인 경우 
                printf("\nEnter the Patient Index: ");
                scanf("%i", &pIndex);
                
                ifctele_printElement(ifctdb_getData(pIndex));     //printElement 함수 사용 
                
                break;
                
            case MENU_PLACE:         //menu_selection이 2번인 경우 
                
				printf("\nEnter the Place: ");
                scanf("%s", &place[MAX_PLACENAME]);
                
                for(i=0; i<ifctdb_len(); i++)
                {
                	//문자열 비교 함수 strcmp 사용 
                	if (strcmp(place, ifctele_getPlaceName(ifctele_getHistPlaceIndex(ifctdb_getData(i), N_HISTORY -1))) == 0) 
                		ifctele_printElement(ifctdb_getData(i));
				}
                
                break;
                
            case MENU_AGE:           //menu_selection이 3번인 경우 
				
				printf("\nEnter the Minimum Age: ");
                scanf("%i", &age_min);
                printf("\nEnter the Maximum Age: ");
                scanf("%i", &age_max);
                
                for (i=0; i<ifctdb_len(); i++)
                {
                	//age_min 이상, age_max 이하인 범위 내의 환자 정보 print
                	if (age_min <= ifctele_getAge(ifctdb_getData(i)) && ifctele_getAge(ifctdb_getData(i)) <= age_max)
                		ifctele_printElement(ifctdb_getData(i));
				}
                
                break;
                
            case MENU_TRACK:         //menu_selection이 4번인 경우 
                
				printf("\nEnter the Patient Index: ");
                scanf("%i", &pat_index);
                
                ifct_element = ifctdb_getData(pat_index);
                
                // 장소를 통한 전파자 추적
				int i;                         //for문을 위한 i 선언 
				int checkPlace[N_HISTORY];     //장소를 확인하는 배열 선언 
				int *ptrplace = &checkPlace[N_HISTORY];
				
				for (i=0; i<N_HISTORY; i++)
				{
					checkPlace[i] = ifctele_getHistPlaceIndex(ifct_element, i);
				} 
				
				// 시간(날짜)을 통한 전파자 추적
				int infectTime;                                         //감염 시점 변수 선언 
				infectTime = ifctele_getinfestedTime(ifct_element);     //감염 시점 저장 
				int *ptrtime = &infectTime;
				
				// trackInfester 함수를 이용하여 infester 찾기 
				infester = trackInfester(pat_index, ptrtime, ptrplace);
				
				// 입력된 patient가 최초 감염자인 경우 
				if (infester = -1) 
				{
					firstInf = pat_index;
					printf("No.%i Patient is the first infector.\n", firstInf);
				}
				
				// 입력된 patient가 최초 감염자가 아닌 경우 
				else
				{
					printf("[No.%i Patient Infection Information]\n - Infester: No.%i Patient\n - Time: %i\n - Place: %s\n\n",
					 pat_index, infester, infectTime, checkPlace[infester]);
					printf("The First Infester is No.%i Patient.\n", firstInf);
				}
				
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}

