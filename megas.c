/*=====(O MEGAS ALEXANDROS KAI O KATARAMENOS OFIS)=====|
|)Name: Koytsioras Panagiotis-------------------------=|
|)AM:   2025201100037---------------------------------=|
|)cst11037@uop.gr-------------------------------------=|
|)=====================================================|
|)Name:Gemistos Vasilis-------------------------------=|
|)AM:2025201100010------------------------------------=|
|)cst11010@uop.gr-------------------------------------=|
|)=====================================================|
|)------------------(Date: 23.04.2012)----------------=|
|=====================================================*/
#include <stdio.h>
#include <stdlib.h>

#define SPACE_NUM 0
#define MEGAS_NUM 1
#define SNAKE_NUM 2
#define GOLD_NUM 3
#define WELLS_NUM 4
#define AIRS_NUM 5

int  Difficulty(int height,int width,int **pa);//Difficulty function calculates the number of the wells that are going to be on Game Board.
void Board(int height, int width, int **pa);//Game Board
void ShowAirs(int n, int k, int **pa);//This function prints, on Game Board, airs after "Megas" goes through them
void PutMegas(int height,int width,int **pa);//This function put "M" to one of four cornerns of Game Board
void PutSnake(int height,int width,int **pa);//This function put "S" to Game Board
void PutGold(int height,int width, int **pa);//This function put "G" to Game Board
void PutWells(int height,int width, int wells, int **pa);//This function put "O" to Game Board.Number of wells depends on percent of Difficulty.
void PutAirs(int height, int width, int **pa);//This function put "~" to Game Board, Up,Down,Right and Left of a Well("O")
int  MoveMegasUp(int height, int width, char ch ,int k,int **pa);//This function move "M" Up if Selection="W"
int  MoveMegasDown(int height, int width, char ch ,int k,int **pa);//This function move "M" Down if Selection="S"
int  MoveMegasRight(int height, int width, char ch ,int k,int **pa);//This function move "M" Right if Selection="D"
int  MoveMegasLeft(int height, int width, char ch ,int k,int **pa);//This function move "M" Left if Selection="A"
int  HelpBoard(int height,int width,int **pa);//This function Shows the Gold and one random Well on Help Board!
int  MoveSnake(int height, int width, int **pa);//This function move the snake up,down,right,left.

int  main(void){//Function main begins here!
//Variable Declarations
  char sign;
  /*k: Keep Megas position at variable "k",and set at it values from (1) to (4) [1-4]-(Corners)
   *h: This variable is responsible of showing Game/Help Board
   *g: When g=1 Game ends(Snake kills Megas)
   *q: When q=1 Game ends(Megas fall into a Well)
   *Snakeswitch: This Variable allows Snake to make one move after two moves of Megas 
   */
  int height,width,i,j,wells,h,k,g=0,SnakeSwitch=0,q=0;
  int **pa=NULL;
//Read from user dimensions of dynamic array
	printf("/============================\\\n");
	printf("|Give Dimensions Of 2D Table:|\n");
	printf("\\============================/\n");
	printf("   |~[ From (2) to (30) ]~|\n");
	printf("   \\======================/\n");
	printf("        /============\\\n");
	printf("        |Height = ");
	scanf("%d",&height);//Read Height from user
	while(height<2 || height>30){//Check if height is out of limits
		printf("        |Out Of Limits.\n        |Height = ");
		scanf("%d",&height);
	}
	printf("        \\============/\n");
	printf("        /============\\\n");
	printf("        |Width  = ");
	//Read width from user
	scanf("%d",&width);
	while(width<2 || width>30){//Check if width is out of limits
		printf("        |Out Of Limits.\n        |Width = ");
		scanf("%d",&width);
	}
	printf("        \\============/\n");

  wells=Difficulty(height,width,pa);//Call Difficulty Function(5%,10%,15%)
  
  pa=calloc(height,sizeof(int*)); //Memory allocation for the 2d Game Board	
  //Check availability of memory
		if(pa==NULL){
			printf("No Memory Available!");
			return 0;
		}   
  for(i=0;i<height;i++){
    pa[i]=calloc(width,sizeof(int));
    if(pa[i]==NULL){
				printf("No Memory Available!");
				return 0;
			}
  }
  
  srand(time(NULL));//srand declaration
	//Put symbols on Game Board
  PutMegas(height,width,pa);
  PutWells(height,width,wells,pa);
  PutAirs(height,width,pa);
  PutGold(height,width,pa);
  PutSnake(height,width,pa);
  
  //Keep Megas position at variable "k",and set at it values from (1) to (4) [1-4]-(Corners)
  if(pa[0][0]==MEGAS_NUM){
    k=1;
  }
  if(pa[0][width-1]==MEGAS_NUM){
    k=2;
  }
  if(pa[height-1][0]==MEGAS_NUM){
    k=3;
  }
  if(pa[height-1][width-1]==MEGAS_NUM){
    k=4;
  }
	

  do{
    ShowAirs(height,width,pa); //Show Air when Megas goes through a cell
    if(h!=1){	
	  printf("GAME BOARD:\n");
      Board(height,width,pa);//Print in screen board
    }	
    h=0;  
    for(i=0; i<height; i++){
      for(j=0; j<width; j++){
	if(pa[i][j]==11){
	  printf("\n");
	  return;
	}
      }
    }	
    //Game Menu 
    printf("\n/================\\");
    printf("\n|.  [h]~[HELP]  .|");
    printf("\n\\================/");
    printf("\n |. [w]~[UP]   .|");
    printf("\n |. [s]~[DOWN] .|");
    printf("\n |. [d]~[RIGHT].|");
    printf("\n |. [a]~[LEFT] .|\n");
    printf("/================\\");
    printf("\n|.  [e]~[EXIT]  .|");
    printf("\n\\================/\n");
    printf(">Make a choice:");
    scanf("%s",&sign);//Read choice from user
    
    SnakeSwitch++;
    
    switch(sign){
    case 'w':
		q=MoveMegasUp(height,width,sign,k,pa);
		if(SnakeSwitch==2){
			g=MoveSnake(height,width,pa);
			SnakeSwitch=0;	
		}		
    break;
    case 's':
		q=MoveMegasDown(height,width,sign,k,pa);
		if(SnakeSwitch==2){
			g=MoveSnake(height,width,pa);	
			SnakeSwitch=0;	
		}	

    break;	
    case 'd':
		q=MoveMegasRight(height,width,sign,k,pa);
		if(SnakeSwitch==2){
			g=MoveSnake(height,width,pa);		
			SnakeSwitch=0;	
		}
    break;
    case 'a':
		q=MoveMegasLeft(height,width,sign,k,pa);	
		if(SnakeSwitch==2){
			g=MoveSnake(height,width,pa);		
			SnakeSwitch=0;	
		}
    break;	
    case 'h':
      printf("HELP BOARD:\n");
      HelpBoard(height,width,pa);
      h=1;
      break;	
    case 'e':	
      printf("Bye Bye!\n");
      break;
    default:
      printf(">Error.\n>Make a Choice:");//Error Option
      scanf("%s",&sign);//Read choice from user			
      break;	
    }	
    if(q==1){
	sign='e';
    }
    if(g==1){
	sign='e';
	printf("The snake kills you! You lose! \n");
    }
  }while(sign != 'e');//if choice is "e" the program ends
	
  //free memory
  for(i=0;i<height;i++){
    free(pa[i]);
  }
  free(pa);
  //end of free
  
}//Function main ends here!

//=====[Board FUNCTION]=====//
void Board(int height, int width, int **pa){
  int i,j;

if(width<10){
		printf("   ");
		for(j=0; j<width; j++){
			printf("%s%d", " ", j+1);
		}
		printf("\n");
		printf("-");
		for(j=0; j<width+1; j++){
			printf("--");
		}
		printf("\n");
	}
	else{
		printf("   ");
		for(j=0;j<9;j++){
			printf("%s%d", "  ", j+1);
		}
		for(j=0;j<width-9;j++){
			printf("%s%d", " ", j+10);
		}
		printf("\n");
		printf("---");
		for(j=0;j<width;j++){
			printf("---");
		}
		printf("\n");
	}

  for(i=0;i<height;i++){
		if(i<9){
			printf("%s%d%s", " ", i+1, "|"); 
		}
		else{
			printf("%d%s", i+1, "|");
		}
      for(j=0; j<width; j++) {
          //Case 0-Space(#) 
          if(pa[i][j]==SPACE_NUM){
              if(width<10){
                  printf(" #");
              }
              else{
                  printf("  #");
              }
          }
          if(pa[i][j]==10){
              if(width<10){
                  printf(" .");
              }
              else{
                  printf("  .");
              }
          }
          if(pa[i][j]==11){
              if(width<10){
                  printf(" M");
              }
              else{
                  printf("  M");
              }
          }
          //Case 1-Megas(M)           
          if(pa[i][j]==MEGAS_NUM){
              if(width<10){
                  printf(" M");
              }
              else{
                  printf("  M");
              }
          }
          //Case 2-Snake(S)       
          if(pa[i][j]==SNAKE_NUM){
              if(width<10){
                  printf(" S");
              }
              else{
                  printf("  S");
              }
          }
          //Case 3-Gold(G)        
          if(pa[i][j]==GOLD_NUM){
              if(width<10){
                  printf(" #");
              }
              else{
                  printf("  #");
              }
          }
          //Case 4-Well(O)        
          if(pa[i][j]==WELLS_NUM){
              if(width<10){
                  printf(" #");
              }
              else{
                  printf("  #");
              }
          }
          //Case 5-7 Air(~)   
          if(pa[i][j]==AIRS_NUM){
              if(pa[i][j]!=1){
                  if(width<10){
                      printf(" #");
                  }
                  else{
                      printf("  #");
                  }	
              }
          }
          if(pa[i][j]==7){
              if(pa[i][j]!=MEGAS_NUM){
                  if(width<10){
                      printf(" ~");
                  }
                  else{
                      printf("  ~");
                  }
              }
          }
          //Case 6-Dot(.)           
          if(pa[i][j]==6){
              if(width<10){
                  printf(" .");
              }
              else{
                  printf("  .");
              }
          }
      }	
      printf("\n");
  }
}

//=====[MoveSnake Function]=====//
int MoveSnake(int height, int width, int **pa){
	int i, j, m1, m2, s1, s2,g;
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			if(pa[i][j]==MEGAS_NUM){
				m1=i;
				m2=j;
			}
			if(pa[i][j]==SNAKE_NUM){
				s1=i;
				s2=j;
			}
		}
	}
	if (m1 > s1){
		if ( (s1+1)<height && (pa[s1+1][s2]!=4 && pa[s1+1][s2]!=3 && pa[s1+1][s2]!=5)){
			if(pa[s1+1][s2]==MEGAS_NUM){
				g=1;
				pa[s1][s2]=0;
				pa[s1+1][s2]= SNAKE_NUM;
				return g;
			}
			pa[s1][s2]= 0;
			pa[s1+1][s2]= SNAKE_NUM;
		}
	}
	else if ( m1 < s1){
		if ( (s1-1)>=0 && (pa[s1-1][s2]!=4 && pa[s1-1][s2]!=3 && pa[s1-1][s2]!=5)){
			if(pa[s1-1][s2]==MEGAS_NUM){
				g=1;
				pa[s1][s2]= 0;
				pa[s1-1][s2]=SNAKE_NUM;
				return g;
			}
			pa[s1][s2]= 0;
			pa[s1-1][s2]=SNAKE_NUM;
		}
	}
	else if (m2 > s2){
		if ( (s2+1)<width && (pa[s1][s2+1]!=4 && pa[s1][s2+1]!=3 && pa[s1][s2+1]!=5)){
			if(pa[s1][s2+1]==MEGAS_NUM){
				g=1;
				pa[s1][s2]= 0;
				pa[s1][s2+1]=SNAKE_NUM;
				return g;
			}
			pa[s1][s2]= 0;
			pa[s1][s2+1]=SNAKE_NUM;
		}
	}
	else if (m2 < s2){
		if( (s2-1)>=0 && (pa[s1][s2-1]!=4 & pa[s1][s2-1]!=3 && pa[s1][s2-1]!=5)){
			if(pa[s1][s2-1]==MEGAS_NUM){
				g=1;
				pa[s1][s2]= 0;
				pa[s1][s2-1]=SNAKE_NUM;
				return g;
			}
			pa[s1][s2]= 0;
			pa[s1][s2-1]=SNAKE_NUM;
		}
	}
}
	
//=====[ShowAirs FUNCTION]=====//
void ShowAirs(int height, int width, int **pa){ 
  int i,j;
  for (i=0; i<height; i++){
    for (j=0; j<width; j++){
      if (pa[i][j]==4){
	if((i+1)<height){
	  if(pa[i+1][j]==6){
	    pa[i+1][j]=7;
	  }
	}
	if((i-1)>=0){
	  if(pa[i-1][j]==6){
	    pa[i-1][j]=7;
	  }
	}
	if((j+1)<width){
	  if(pa[i][j+1]==6){
	    pa[i][j+1]=7;
	  }
	}
	if((j-1)>=0){
	  if(pa[i][j-1]==6){
	    pa[i][j-1]=7;
	  }
	}							
      }	
    }	
	
  }
}

//=====[Difficulty FUNCTION]=====//
int  Difficulty(int height,int width,int **pa){
  int Selection,Wells;
  printf("/===========================\\\n");
	printf("| Choose Percent of Wells : |\n");
	printf("\\===========================/\n");
	printf(" |[1]-[A Few]-------->[5%%] |\n");
	printf(" |[2]-[Quite A Few]-->[10%%]|\n");
	printf(" |[3]-[A Lot]-------->[15%%]|\n");
	printf(" \\=========================/\n");
	printf(">");
  scanf("%d",&Selection);
  if(Selection==1)
    Wells=(height*width*5)/(100);
    
  if(Selection==2)
    Wells=(height*width*10)/(100);
  
  if(Selection==3)
    Wells=(height*width*15)/(100);
    
  return Wells;
}


//=====[PutMegas FUNCTION]=====//
void PutMegas(int height,int width,int **pa){
  int matrix1[2],matrix2[2];
  int r1,r2;
  matrix1[0]=0;
  matrix1[1]=height-1;
  matrix2[0]=0;
  matrix2[1]=width-1;
  r1=rand() % 2;
  r2=rand() % 2;	
  pa[matrix1[r1]][matrix2[r2]]=1;	
}


//=====[PutSnake FUNCTION]=====//
void PutSnake(int height,int width,int **pa){
  int r1,r2;
  r1 = rand()%(height);//pick a number between 0 and height
  r2 = rand()%(width);//pick a number between 0 and width
  while(pa[r1][r2]==MEGAS_NUM || pa[r1][r2]==3 || pa[r1][r2]==4 || pa[r1][r2]==5){
    r1 = rand()%(height);
    r2 = rand()%(width);
  }
  pa[r1][r2]=2;
}


//=====[PutGold FUNCTION]=====//
void PutGold(int height,int width, int **pa){
  int r1,r2;
  r1 = rand()%(height);//pick a number between 0 and height
  r2 = rand()%(width);//pick a number between 0 and width
  while(pa[r1][r2]==MEGAS_NUM || pa[r1][r2]==2 || pa[r1][r2]==4 || pa[r1][r2]==5){
    r1 = rand()%(height);
    r2 = rand()%(width);
  }
  pa[r1][r2]=3;
}


//=====[PutWells FUNCTION]=====//
void PutWells(int height,int width,int wells, int **pa){
  int i,r1,r2;
  for(i=0; i<wells; i++){
    r1 = rand()%(height);//pick a number between 0 and height
    r2 = rand()%(width);//pick a number between 0 and width
    while(pa[r1][r2]==MEGAS_NUM || pa[r1][r2]==3 || pa[r1][r2]==4){
      r1 = rand()%(height);
      r2 = rand()%(width);
    }
    pa[r1][r2]=4;
  }
}

//=====[PutAirs FUNCTION]=====//
void PutAirs(int height, int width, int **pa){
  int i,j,k=0;
  for (i=0; i<height; i++){
    for (j=0; j<width; j++){
      if (pa[i][j]==4){
	if((i+1)<height){
	  if(pa[i+1][j]!=MEGAS_NUM){
	    pa[i+1][j]=5;
	  }
	}
	if((i-1)>=0){
	  if(pa[i-1][j]!=MEGAS_NUM){
	    pa[i-1][j]=5;
	  }
	}
	if((j+1)<width){
	  if(pa[i][j+1]!=MEGAS_NUM){
	    pa[i][j+1]=5;
	  }
	}
	if((j-1)>=0){
	  if(pa[i][j-1]!=MEGAS_NUM){
	    pa[i][j-1]=5;
	  }
	}								
      }	
    }	
	
  }
}

//=====[MoveMegasUp FUNCTION]=====//
int MoveMegasUp(int height, int width, char move,int k,int **pa){
  int i,j,g;
  for(i=0; i<height; i++){
    for (j=0; j<width; j++){
      if(move=='w'){ //move up
	if(pa[i][j]==MEGAS_NUM){
	  if((i-1)>=0){
	    if(pa[i-1][j]==0 || pa[i-1][j]==6){
	      pa[i-1][j]=MEGAS_NUM;
	      pa[i][j]=6;
	    }
	    if(pa[i-1][j]==10){
	      
	      pa[i-1][j]=11;
	      pa[i][j]=6;
	      printf("/========\\\n");
	      printf("|YOU WON!|\n");
		  printf("\\========/\n");
	      return g;
	    }
						
				
	  }
	  else{
	    printf("You are out of borders! You can't go up! \n");
	    return g;
	  }
	  if (pa[i-1][j]==3){
	    if(k==1){
	      pa[0][0]=10;
	    }
	    if(k==2){
	      pa[0][width-1]=10;
	    }
	    if(k==3){
	      pa[height-1][0]=10;
	    }
	    if(k==4){
	      pa[height-1][width-1]=10;
	    }
	    printf("You found Gold!\nGo Back To Your Beggining position!\n");
						
	    return g;
	  }
	  if (pa[i-1][j]==4){
	    g=1;
	    printf("You Fell into a well\nYou Lose\n");
	    return g;
	  }
	  if (pa[i-1][j]==5){
							
	    pa[i-1][j]=MEGAS_NUM;
	    pa[i][j]=6;
	    printf("You feel the air from the well into the (%d,%d)!\n",i,j+1);
	  }	
	  if (pa[i-1][j]==7){
	    pa[i-1][j]=MEGAS_NUM;
	    pa[i][j]=6;
	    printf("You feel the air from the well into the (%d,%d)!\n",i,j+1);
	    ShowAirs(height,width,pa);	
	  }
	  ShowAirs(height,width,pa);
	  return g;
	}
      }
    }
  }
}


//=====[MoveMegasDown FUNCTION]=====//
int MoveMegasDown(int height, int width, char move,int k,int **pa){
  int i,j,g;
  for(i=0; i<height; i++){
    for (j=0; j<width; j++){
      if(move=='s'){ //move down
	if(pa[i][j]==1){
	  if((i+1)<height){
	    if(pa[i+1][j]==0 || pa[i+1][j]==6){
	      pa[i+1][j]=MEGAS_NUM;
	      pa[i][j]=6;
	    }
	    if(pa[i+1][j]==10){
	      
	      pa[i+1][j]=11;
	      pa[i][j]=6;
	      printf("/========\\\n");
	      printf("|YOU WON!|\n");
		  printf("\\========/\n");
	      return g;
							
	    }
						
	  }
	  else{
	    printf("You are out of borders! You can't go down! \n");
	    return g;
	  }
	  if (pa[i+1][j]==3){
	    if(k==1){
	      pa[0][0]=10;
	    }
	    if(k==2){
	      pa[0][width-1]=10;
	    }
	    if(k==3){
	      pa[height-1][0]=10;
	    }
	    if(k==4){
	      pa[height-1][width-1]=10;
	    }
	    printf("You found Gold!\nGo Back To Your Beggining position!\n");
	    return g;
	  }
	  if (pa[i+1][j]==4){
	    g=1;
	    printf("You Fell into a well\nYou Lose\n");
	    return g;
	  }
	  if (pa[i+1][j]==5){
	    pa[i+1][j]=MEGAS_NUM;
	    pa[i][j]=6;
	    printf("You feel the air from the well into the (%d,%d)!\n",i+2,j+1);
	  }
	  if (pa[i+1][j]==7){
	    pa[i+1][j]=MEGAS_NUM;
	    pa[i][j]=6;
	    printf("You feel the air from the well into the (%d,%d)!\n",i,j+1);
	    ShowAirs(height,width,pa);
	  }
	  ShowAirs(height,width,pa);
	  return g;
	}
      }
    }
  }
}

//=====[MoveMegasRight FUNCTION]=====//
int MoveMegasRight(int height, int width, char move,int k,int **pa){
  int i,j,g;
  for(i=0; i<height; i++){
    for (j=0; j<width; j++){
      if(move=='d'){ //move right
	if(pa[i][j]==1){
	  if((j+1)<width){
	    if(pa[i][j+1]==0 || pa[i][j+1]==6){
						
	      pa[i][j+1]=MEGAS_NUM;
	      pa[i][j]=6;
	    }
	    if(pa[i][j+1]==10){
	      pa[i][j+1]=11;
	      pa[i][j]=6;
	      printf("/========\\\n");
	      printf("|YOU WON!|\n");
		  printf("\\========/\n");
	      return g;
	    }
						
						
	  }
	  else{
	    printf("You are out of borders! You can't go right! \n");
	    return g;
	  }
	  if (pa[i][j+1]==3){
	    if(k==1){
	      pa[0][0]=10;
	    }
	    if(k==2){
	      pa[0][width-1]=10;
	    }
	    if(k==3){
	      pa[height-1][0]=10;
	    }
	    if(k==4){
	      pa[height-1][width-1]=10;
	    }
	    printf("You found Gold!\nGo Back To Your Beggining position!\n");
	    return g;
						
	  }
	  if (pa[i][j+1]==4){
            g=1;
	    printf("You Fell into a well\nYou Lose\n");
	    return g;
	  }
	  if (pa[i][j+1]==5){
						
	    pa[i][j+1]=MEGAS_NUM;
	    pa[i][j]=6;
	    printf("You feel the air from the well into the (%d,%d)!\n",i+1,j+2);
							
	  }
	  if (pa[i][j+1]==7){
						
	    pa[i][j+1]=MEGAS_NUM;
	    pa[i][j]=6;
	    printf("You feel the air from the well into the (%d,%d)!\n",i,j+1);
	    ShowAirs(height,width,pa);
							
	  }					
	  ShowAirs(height,width,pa);
						
	  return g;
	}
      }
    }
  }
}	


//=====[moveMegasLeft FUNCTION]=====//
int MoveMegasLeft(int height, int width, char move,int k,int **pa){
  int i,j,g;
  for(i=0; i<height; i++){
    for (j=0; j<width; j++){
      if(move=='a'){ //move left
	if(pa[i][j]==1){
	  if((j-1)>=0){
	    if(pa[i][j-1]==0 || pa[i][j-1]==6){
							
	      pa[i][j-1]=MEGAS_NUM;
	      pa[i][j]=6;
							
	    }
	    if(pa[i][j-1]==10){
	      pa[i][j-1]=11;
	      pa[i][j]=6;
	      printf("/========\\\n");
	      printf("|YOU WON!|\n");
		  printf("\\========/\n");
	      return g;
	    }
						
	  }
	  else{
	    printf("You are out of borders! You can't go left! \n");
	    return g;
	  }
	  if (pa[i][j-1]==3){
	    if(k==1){
	      pa[0][0]=10;
	    }
	    if(k==2){
	      pa[0][width-1]=10;
	    }
	    if(k==3){
	      pa[height-1][0]=10;
	    }
	    if(k==4){
	      pa[height-1][width-1]=10;
	    }
	    printf("You found Gold!\nGo Back To Your Beggining position!\n");
	    return g;
	  }
	  if (pa[i][j-1]==4){
            g=1;
	    printf("You Fell into a well\nYou Lose\n");
	    return g;
	  }
	  if (pa[i][j-1]==5){
							
	    pa[i][j-1]=MEGAS_NUM;
	    pa[i][j]=6;
	    printf("You feel the air from the well into the (%d,%d)!\n",i+1,j);
						
	  }
	  if (pa[i][j-1]==7){
							
	    pa[i][j-1]=MEGAS_NUM;
	    pa[i][j]=6;
	    printf("You feel the air from the well into the (%d,%d)!\n",i,j+1);
	    ShowAirs(height,width,pa);
							
	  }
	

	  ShowAirs(height,width,pa);
		
	  return g;
					
	}
      }
    }
  }
}	

//=====[HelpBoard FUNCTION]=====//
int HelpBoard(int height,int width,int **pa){
  int i,j,r1,r2,v;
  r1 = rand()%(height);
  r2 = rand()%(width);
  while(pa[r1][r2]!=4){
    r1 = rand()%(height);
    r2 = rand()%(width);
  }
  pa[r1][r2]=8;

if(width<10){
		printf("   ");
		for(j=0; j<width; j++){
			printf("%s%d", " ", j+1);
		}
		printf("\n");
		printf("-");
		for(j=0; j<width+1; j++){
			printf("--");
		}
		printf("\n");
	}
	else{
		printf("   ");
		for(j=0;j<9;j++){
			printf("%s%d", "  ", j+1);
		}
		for(j=0;j<width-9;j++){
			printf("%s%d", " ", j+10);
		}
		printf("\n");
		printf("---");
		for(j=0;j<width;j++){
			printf("---");
		}
		printf("\n");
	} 
  for(i=0;i<height;i++){
if(i<9){
			printf("%s%d%s", " ", i+1, "|"); 
		}
		else{
			printf("%d%s", i+1, "|");
		}
    for(j=0;j<width;j++) {
      //Case 0-Space(#) 
      if(pa[i][j]==0){
	if(width<10){
	  printf(" #");
	}
	else{
	  printf("  #");
	}
      }
      //Case 1-Megas(M)           
      if(pa[i][j]==MEGAS_NUM){
	if(width<10){
	  printf(" M");
	}
	else{
	  printf("  M");
	}
      }
      //Case 2-Snake(S)       
      if(pa[i][j]==2){
	if(width<10){
	  printf(" S");
	}
	else{
	  printf("  S");
	}
      }
      //Case 3-Gold(G)        
      if(pa[i][j]==3){
	if(width<10){
	  printf(" G");
	}
	else{
	  printf("  G");
	}
      }
      //Case 4-Well(O)        
      if(pa[i][j]==8){
	if(width<10){
	  printf(" O");
	}
	else{
	  printf("  O");
	}
	pa[i][j]=4;
      }
      else if(pa[i][j]==4){
	if(width<10){
	  printf(" #");
	}
	else{
	  printf("  #");
	}
      }
      //Case 5-Air(~)           

      if(pa[i][j]==5){
	if(pa[i][j]!=MEGAS_NUM){
	  if(width<10){
	    printf(" #");
	  }
	  else{
	    printf("  #");
	  }	
	}
      }
      if(pa[i][j]==7){
	if(pa[i][j]!=MEGAS_NUM){
	  if(width<10){
	    printf(" ~");
	  }
	  else{
	    printf("  ~");
	  }
	}
      }
		

      //Case 6-Dot(.)           
      if(pa[i][j]==6){
	if(width<10){
	  printf(" .");
	}
	else{
	  printf("  .");
	}
      }
     
    }	
    printf("\n");
  }
}
