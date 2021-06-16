#include<stdio.h>

int suduco[9][9],prob[9][9][9];

int  arbitrary_assign()
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(suduco[i][j]==0 && prob[i][j][0]!=0){
                suduco[i][j]=prob[i][j][0];
                prob[i][j][0]=0;

                printf("%d %d\n",i,j);
            return 0;
            }
}


int column_check()
{
    for(int i=0;i<9;i++){
            int tmp[10]={0};
        for(int j=0;j<9;j++){
                    int k=-1;
                while(prob[j][i][++k])
                    tmp[prob[j][i][k]]++;
        }
        for(int j=1;j<10;j++)
            if(tmp[j]==1){
                    for(int p=0;p<9;p++){
                        int k=-1;
                        while(prob[p][i][++k])
                            if(prob[p][i][k]==j){
                               suduco[p][i]=j;
                               break;
                            }
                    }
            }
    }
}




int row_check()
{
    for(int i=0;i<9;i++){
            int tmp[10]={0};
        for(int j=0;j<9;j++){
                    int k=-1;
                while(prob[i][j][++k])
                    tmp[prob[i][j][k]]++;
        }
        for(int j=1;j<10;j++)
            if(tmp[j]==1){
                    for(int p=0;p<9;p++){
                        int k=-1;
                        while(prob[i][p][++k])
                            if(prob[i][p][k]==j){
                               suduco[i][p]=j;
                               break;
                            }
                    }
            }
    }
}




int assign_value(int counter[],int r,int c)
{
    int k=0;

    for(int i=1;i<10;i++)
        if(counter[i]==3)
            prob[r][c][k++]=i;          //there are no term to input there

            prob[r][c][k]=0;        //terminated by zero
            if(k==1){                   //only one value are remaining for input in this room
                suduco[r][c]=prob[r][c][--k];
                prob[r][c][k]=0;
            }

            //printf("\tWork\t");
}

int home_search(int counter[],int n,int m)
{
    int tmp[10]={0},keyR=(n/3)*3,keyC=(m/3)*3;
    for(int i=keyR;i<(keyR+3);i++)
        for(int j=keyC;j<(keyC+3);j++)
            if(suduco[i][j]!=0)
                tmp[suduco[i][j]]++;        //the value which are in this home are count

    for(int i=1;i<10;i++)
        if(tmp[i]==0)
            counter[i]++;      //the value which are not in this home are count

}



int col_search(int counter[],int n)
{
    int tmp[10]={0};
    for(int i=0;i<9;i++)
        if(suduco[i][n]!=0)
            tmp[suduco[i][n]]++;        //the value which are in this row and column are count

    for(int i=1;i<10;i++)
        if(tmp[i]==0)
            counter[i]++;      //the value which are not in this row and column are count

}



int row_search(int counter[],int n)
{
    int tmp[10]={0};
    for(int i=0;i<9;i++)
        if(suduco[n][i]!=0)
            tmp[suduco[n][i]]++;        //the value which are in this row and column are count



    for(int i=1;i<10;i++)
        if(tmp[i]==0)
            counter[i]++;      //the value which are not in this row and column are count



}


int search_probablity_value()
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++){
            if(suduco[i][j]==0){
                    int counter[10]={0};
                row_search(counter,i);
                col_search(counter,j);
                home_search(counter,i,j);

                assign_value(counter,i,j);
            }
            else
                prob[i][j][0]=0;
        }
}



int count_number()
{
    int total=0,i,j;

    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            if(suduco[i][j]!=0)
                total++;
    return total;       //return how many number there are in the suduco present
}


int solve_first_step()
{
    int first,second=count_number();

    for( ; ; ){
        search_probablity_value();      //solve where only one value are pointed
        first=count_number();

        if(first==second)
            break;
        else
            second=first;
    }
return first;
}


int final_solver()
{int b=0,k=0;
    while(count_number()!=81 && k<150){
        solve_first_step();

        row_check();

        solve_first_step();

        column_check();

        int a=solve_first_step();
        if(a==b)
            arbitrary_assign();
        else
            b=a;
        k++;
    }


}


int input_suduco()
{
    char d;

    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            scanf("%d%c",&suduco[i][j],&d);

}


int main()
{
    int a,b;
    printf("Input suduco :\n");
    printf("Note : Input number separated by a space and Input zero where there are no value\n");

        input_suduco();
        final_solver();
        //final_solver();

        printf("Probablity value is\n");
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){int k=-1;
                while(prob[i][j][++k])
                    printf("%d",prob[i][j][k]);
                printf("\t");}
                 printf("\n");}

printf("\n\nYour solution is :\n\n");
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++)
            printf("%d ",suduco[i][j]);
            printf("\n");
    }

    return 0;
}




/*
0 0 0 0 0 0 5 0 0
3 0 2 0 7 0 9 1 0
6 0 0 9 0 0 0 0 0
0 0 0 0 0 0 0 2 6
0 2 0 3 0 0 1 5 9
7 9 0 6 0 5 0 8 0
1 0 9 7 0 0 0 0 0
4 5 0 0 0 0 2 3 0
0 3 8 4 5 0 6 0 0


0 8 0 0 2 0 0 0 6
0 9 2 0 5 0 7 0 0
0 0 0 6 0 1 0 0 3
0 7 0 0 0 0 0 0 0
5 0 3 0 0 0 9 0 4
0 0 0 0 0 0 0 8 0
4 0 0 7 0 3 0 0 0
0 0 7 0 4 0 8 3 0
1 0 0 0 9 0 0 5 0


9 0 0 0 0 0 0 0 7
0 2 0 8 0 3 0 4 0
1 7 0 0 4 0 0 2 8
0 0 5 0 0 0 8 0 0
0 4 0 2 5 6 0 1 0
0 3 1 0 0 0 4 6 0
0 1 9 0 6 0 7 8 0
0 5 0 0 0 0 0 9 0
7 0 0 4 1 9 0 0 3

0 0 0 0 0 0 7 0 8
0 9 5 0 0 3 0 2 0
6 0 0 2 0 0 0 9 0
0 0 9 0 8 0 0 0 0
2 1 0 0 9 0 0 6 3
0 0 0 0 0 0 0 0 5
0 6 0 0 0 5 0 0 1
0 7 0 3 0 0 6 4 0
1 0 8 0 0 0 0 0 0


0 0 0 0 0 0 7 0 0
0 0 5 0 0 0 0 0 0
6 0 0 0 0 0 0 0 0
0 0 0 0 8 0 0 0 0
0 0 0 0 9 0 0 0 3
0 0 0 0 0 0 0 0 5
0 0 0 0 0 5 0 0 1
0 0 0 0 0 0 0 4 0
1 0 0 0 0 0 0 0 0


*/
