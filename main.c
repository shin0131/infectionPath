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
#include "C:\Users\USER\Desktop\Univ\2022_2-2\전자공학프로그래밍\기말 프로젝트\basecode\ifct_element.h"
#include "C:\Users\USER\Desktop\Univ\2022_2-2\전자공학프로그래밍\기말 프로젝트\basecode\ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2


int trackInfester(int patient_no, int *detected_time, int *place);

int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1],"r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    
    #if
    //1-2. loading each patient informations
    
    // patientInfo_sample.txt 파일 읽어오기 
    FILE* file;
    file = fopen("C:\Users\USER\Desktop\Univ\2022_2-2\전자공학프로그래밍\기말 프로젝트\patientInfo_sample.txt", "r");
    
    while ( 3 == fscanf(file, "%i %i %i", &pIndex, &age, &time))
    {
    	int i;                                    //
		for (i=0; i<5; i++)                       //
    		fscanf(file, "%i", &placeHist[i]); 
			//
    		
    	ifct_element = ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY]);
    	
    	// linked list에 생성된 구조체 저장 : ifctdb_addTail 함수 이용 
    	ifctdb_addTail(ifct_element);
    	
    	printf("%i 번째 환자 감염 경로 : ", 환자 번호);
    	for (5번 반복)
    		printf("%s", ifsele_getPlaceName(placeList[i]));
    	printf("\n");
    	
    	ifct_ele = ifctele_genElement(pIndex, age, time, placeHist);
    	
    	ifctdb_addTail(ifct_ele);
    	
	}
	#endif

	
    
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
        
        switch(menu_selection)
        {
            case MENU_EXIT:          //menu_selection이 0번인 경우 
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:       //menu_selection이 1번인 경우 
                printf("Enter the Patient Index: \n");
                scanf("%i", &pIndex);
                
                ifctele_printElement(ifctdb_getData(pIndex));     //printElement 함수 사용 
                
                break;
                
            case MENU_PLACE:         //menu_selection이 2번인 경우 
                int i;                         //for문을 위한 i 선언 
				char place[MAX_PLACENAME];     //char 형태 장소 변수 선언 
                
				printf("Enter the Place: \n");
                scanf("%s", &place);
                
                for(i=0; i<ifctdb_len(); i++)
                {
                	
				}
                
                break;
                
            case MENU_AGE:           //menu_selection이 3번인 경우 
                int age_min, age_max;     //int 형태 minimum, maximum 나이 변수 선언 
				
				printf("Enter the Minimum Age: \n");
                scanf("%i", &);
                printf("Enter the Maximum Age: \n");
                scanf("%i", &);
                
                break;
                
            case MENU_TRACK:         //menu_selection이 4번인 경우 
                printf("")
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
