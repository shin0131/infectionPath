//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//
//  2112392 ���ſ� 
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


// infester ��ô�ϴ� �Լ� ���� 
int trackInfester(int patient_no, int *detected_time, int *place)
{
	int i, j;                        //for���� ���� i, j ���� 
	int infIndex = -1;               //�Լ��� return ���� �������� ��ȣ ����, index = -1
	int infTime = *detected_time;     //���� ��¥ ���� ���� 
	int infPlace = *place;            //���� ��� ���� ���� 
	int trackNum;                    //������ ȯ���� ��ȣ ���� ���� 
	int trackTime;                   //������ ���� ���� ���� ���� 
	int trackPlace1, trackPlace2;    //������ ���� ��� ���� ���� (�ߺ���, �ߺ� �Ϸ� ��) 
	
	// data�� ȯ�ڵ�� �ð�, ��� �� (�Էµ� ȯ�� �ڽ� ����) 
	for (i=0; i<ifctdb_len(); i++)
	{
		if (patient_no != i)
		{
			trackNum = i;
			
			trackTime = ifctele_getinfestedTime(ifctdb_getData(i));     // ���� -> ifctele_getinfestedTime �Լ� ��� 
			
			// ��� -> ifctele_getHistPlaceIndex �Լ� ��� 
			trackPlace1 = ifctele_getHistPlaceIndex(ifctdb_getData(i), N_HISTORY - 1);
			trackPlace2 = ifctele_getHistPlaceIndex(ifctdb_getData(i), N_HISTORY - 2);
			
			// ���� ���� �ñ��� �ð�, ��� Ȯ�� 
			for (j=0; j<3; j++)
			{
				if ((place[j] == trackPlace1) && (detected_time - 4 + j == trackTime))     // �ߺ� ���� 
				{
					if (infTime > trackTime)
					{
						infIndex = trackNum;
						infTime = trackTime;
						infPlace = trackPlace1;
					}
				}
				
				if ((place[j] == trackPlace2) && (detected_time - 4 + j == trackTime - 1))      // �ߺ� �Ϸ� �� 
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
	
	return infIndex;     // �������� ��ȣ return 
	
} // trackInfester �Լ� 



// main �Լ�- ������ ���� ���α׷� ���� �Լ� 
   // 1. Ư�� ȯ�ڿ� ���� ���� ���
   // 2. Ư�� ��ҿ��� ������ Ȯ�ε� ȯ�� ���� ���� ���
   // 3. Ư�� ������ ���̿� �ش��ϴ� ȯ�� ���� ���� ���
   // 4. ���� ��� �� ���� ������ ����
   // 0. ���α׷� ���� 
int main(int argc, const char * argv[]) {
    
    int menu_selection;         // menu number ���� ���� ���� 
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
    
    // patientInfo_sample.txt ���� �о���� 
    FILE* file;
    file = fopen("patientInfo_sample.txt", "r");
    
    while ( 3 == fscanf(file, "%i %i %i", &pIndex, &age, &time))     //patient index, age, time �о���� 
    {
    	int i;                                     //for���� ���� i ���� 
		for (i=0; i<5; i++)                        //place 5�� (ȯ���� �̵����) ���� 
    		fscanf(file, "%i", &placeHist[i]);
    		
    	ifct_element = ifctele_genElement(pIndex, age, time, placeHist);
    	
    	// linked list�� ������ ����ü ���� : ifctdb_addTail �Լ� �̿� 
    	ifctdb_addTail(ifct_element);
    	
    	/*
    	printf("%i ��° ȯ�� ���� ��� : ", ȯ�� ��ȣ);
    	for (5�� �ݺ�)
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
        
        
        // MENU_PLACE ���� ���� 
		int i;                         //for���� ���� i
		char place[MAX_PLACENAME];     //char ���� ��� ����
		
		// MENU_AGE ���� ���� 
		int age_min, age_max;         //int ���� minimum, maximum ���� ����
		
		// MENU_TRACK ���� ���� 
		int pat_index;                //patient index �Է� �޴� ����
        int infester = -1;            //infester ����, index -1 
        int firstInf;                 //���� ������ ����
        
        
        switch(menu_selection)
        {
            case MENU_EXIT:          //menu_selection�� 0���� ��� 
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:       //menu_selection�� 1���� ��� 
                printf("\nEnter the Patient Index: ");
                scanf("%i", &pIndex);
                
                ifctele_printElement(ifctdb_getData(pIndex));     //printElement �Լ� ��� 
                
                break;
                
            case MENU_PLACE:         //menu_selection�� 2���� ��� 
                
				printf("\nEnter the Place: ");
                scanf("%s", &place[MAX_PLACENAME]);
                
                for(i=0; i<ifctdb_len(); i++)
                {
                	//���ڿ� �� �Լ� strcmp ��� 
                	if (strcmp(place, ifctele_getPlaceName(ifctele_getHistPlaceIndex(ifctdb_getData(i), N_HISTORY -1))) == 0) 
                		ifctele_printElement(ifctdb_getData(i));
				}
                
                break;
                
            case MENU_AGE:           //menu_selection�� 3���� ��� 
				
				printf("\nEnter the Minimum Age: ");
                scanf("%i", &age_min);
                printf("\nEnter the Maximum Age: ");
                scanf("%i", &age_max);
                
                for (i=0; i<ifctdb_len(); i++)
                {
                	//age_min �̻�, age_max ������ ���� ���� ȯ�� ���� print
                	if (age_min <= ifctele_getAge(ifctdb_getData(i)) && ifctele_getAge(ifctdb_getData(i)) <= age_max)
                		ifctele_printElement(ifctdb_getData(i));
				}
                
                break;
                
            case MENU_TRACK:         //menu_selection�� 4���� ��� 
                
				printf("\nEnter the Patient Index: ");
                scanf("%i", &pat_index);
                
                ifct_element = ifctdb_getData(pat_index);
                
                // ��Ҹ� ���� ������ ����
				int i;                         //for���� ���� i ���� 
				int checkPlace[N_HISTORY];     //��Ҹ� Ȯ���ϴ� �迭 ���� 
				int *ptrplace = &checkPlace[N_HISTORY];
				
				for (i=0; i<N_HISTORY; i++)
				{
					checkPlace[i] = ifctele_getHistPlaceIndex(ifct_element, i);
				} 
				
				// �ð�(��¥)�� ���� ������ ����
				int infectTime;                                         //���� ���� ���� ���� 
				infectTime = ifctele_getinfestedTime(ifct_element);     //���� ���� ���� 
				int *ptrtime = &infectTime;
				
				// trackInfester �Լ��� �̿��Ͽ� infester ã�� 
				infester = trackInfester(pat_index, ptrtime, ptrplace);
				
				// �Էµ� patient�� ���� �������� ��� 
				if (infester = -1) 
				{
					firstInf = pat_index;
					printf("No.%i Patient is the first infector.\n", firstInf);
				}
				
				// �Էµ� patient�� ���� �����ڰ� �ƴ� ��� 
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

