/*
 * =====================================================================================
 *
 *       Filename:  function.c
 *
 *    Description:  DFS算法
 *                  简单路径
 *                  最短路径
 *
 *        Version:  1.0
 *        Created:  2014年12月09日 08时38分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (fgm), mehner.fritz@fh-swf.de
 *   Organization:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include"myhome.h"
#include"function.h"

void map(void)
{
        printf("\t\t----------------------------------------------------------------------------------------------\n");
        printf("\t\t|        ********| |                                             ********| |                 |\n");
        printf("\t\t|        *海洲湾*| |                                             *舅舅家*| |                 |\n");
        printf("\t\t|        ********| |                                             ********| |                 |\n");
        printf("\t\t|                | |                                                     | |                 |\n");
        printf("\t\t|                | |                                                     | |                 |\n");
        printf("\t\t|                | |                                                     | |-----******      |\n");
        printf("\t\t|                | |    **********                                       |       *海小*      |\n");
        printf("\t\t|                | |    *海头政府*                                       | |-----******      |\n");
        printf("\t\t|                | |    **********                                       | |                 |\n");
        printf("\t\t|----------------- --------  ----------------------------------------------------------------|\n");
        printf("\t\t|----------------------------- -------------------------------------  -----------------------|\n");
        printf("\t\t|                            | |                                  ******                     |\n");
        printf("\t\t|                            | |                                  *超市*                     |\n");
        printf("\t\t|                            | |                                  ******                     |\n");
        printf("\t\t|                            | |                                                             |\n");
        printf("\t\t|                            | |                                                             |\n");
        printf("\t\t|                      ******| |----********                                                 |\n");
        printf("\t\t|                      *海中*       *我的家*                                                 |\n");
        printf("\t\t|                      ******| |----********                                                 |\n");
        printf("\t\t|                            | |    *朋友家*                                                 |\n");
        printf("\t\t|                            | |    ********                                                 |\n");
        printf("\t\t|      ----------------------  |                                                             |\n");
        printf("\t\t|      -------- ---------------|                                                             |\n");
        printf("\t\t|     ********| |     ********                                                               |\n");
        printf("\t\t|     *奶奶家*| |     *大爷家*                                                               |\n");
        printf("\t\t|     ********| |     ********                                                               |\n");
        printf("\t\t|             | |                                                                            |\n");
        printf("\t\t|             | |********                                                                    |\n");
        printf("\t\t|             | |*姑姑家*                                                                    |\n");
        printf("\t\t|             | | *******                                                                    |\n");
        printf("\t\t----------------------------------------------------------------------------------------------\n");

}
void Menu( void )
{

          printf("\t\t\t\t\t----------------------------------------------------\n");

          printf("\t\t\t\t\t *          * **** *    ****  ****    *   *    ****  \n");

          printf("\t\t\t\t\t *    *    *  *    *    *     *  *   **   **   *     \n");

          printf("\t\t\t\t\t  *  * *  *   **** *    *     *  *  *  * *  *  ****  \n");

          printf("\t\t\t\t\t   **   **    *    *    *     *  * *    *    * *     \n");

          printf("\t\t\t\t\t    *   *     **** **** ****  **** *         * ****  \n"); 
 
          printf("\t\t\t\t\t----------------------------------------------------\n");

          printf("\t\t\t\t\t****************************************************\n");

                        printf("\t\t\t\t\t\t\t\t我的家\n");

          printf("\t\t\t\t\t****************************************************\n\n");
                       printf("\t\t\t\t\t\t\t1.地图\n");
                       printf("\t\t\t\t\t\t\t2.所有地点信息\n");
                       printf("\t\t\t\t\t\t\t3.搜索地点\n");
                       printf("\t\t\t\t\t\t\t4.怎么去最快\n");
                       printf("\t\t\t\t\t\t\t5.怎么去最方便\n");
                       printf("\t\t\t\t\t\t\t6.如何布线\n");
                       printf("\t\t\t\t\t\t\t7.添加地点\n");
                       printf("\t\t\t\t\t\t\t8.添加路线\n");
                       printf("\t\t\t\t\t\t\t9.删除路线\n");
                       printf("\t\t\t\t\t\t\t0.退出\n");

}
void _fflush( void )
{
        int  c;
        do{
                c = fgetc(stdin);
        }while( c != '\n' && c != EOF );
}

int visited[NUMMAX];
void  DFTallList( ListMatrix *G )
{
        int i;
        for( i=1; i<=G->vexnum; i++ )
                visited[i] = 0;

        for( i=1; i<=G->vexnum; i++ )
                if(!visited[i])
                {
                        DFTList( G, i );
               }
}
void DFTList( ListMatrix * G,int v0 )//Depth frist traversal of list of map
{       
        ArcNode * p;
#if(1)
        printf("%d\t",NametoNum(G,G->vertex[v0].vexdata.placename));
#endif
        printf("%s\t",G->vertex[v0].vexdata.placename);
        printf("\n");

        visited[v0] = 1;
        p = G->vertex[v0].next;
        while( p != NULL )
        {
                if( !visited[p->adjvex] )
                {
                        DFTList( G , p->adjvex );
                }
                p = p->next;
        }

}

void  AllEasyPath( ListMatrix * G, int star, int end, int  choose )
/*
 * 寻找简单路径
 * choose 为1寻找所有的简单路径
 * choose 为2寻找最短的简单路径
 * */
{
        int i,j;
        int shortest;//用以标记最短的下标
        int path[NUMMAX];
        int  allpath[NUMMAX][NUMMAX];
        int count = 0;
        for( i=1; i<=G->vexnum; i++ )
        {
                visited[i] = 0;
        }
        if( choose == 1 )
        {
                EasyPath( G,star,end,path,0 );
        }else if( choose == 2 )
        {
                ShortestEasyPath(G,star,end,path,0,allpath,&count);
#if(0)
                for( i=1; i<=count; i++)
                {
                        for( j=1; j<=allpath[i][0]; j++ )
                                printf("%d",allpath[i][j]);
                        printf("\n");
                }
#endif
                for( i=1,j=allpath[i][0]; i<=count; i++ )
                {
                        if( j > allpath[i][0] )
                        {      j = allpath[i][0];
                              shortest = i;
                        }
                }//找到最短的那个
#if(1)
                      printf("\t\t\t\t\t\t\t路径为:\n");
                      printf("\t\t\t\t\t\t\t");
                for( j=1; j<=allpath[shortest][0]; j++ )
                {
                        printf("%s->",NumtoName(G,allpath[shortest][j]));
                        if( j%2 == 0 )
                      printf("\n\t\t\t\t\t\t\t");

                }
                printf("\n");
                _fflush();
#endif

#if(0)
                for( j=1; j<=allpath[shortest][0]; j++ )
                        printf("%d",allpath[shortest][j]);//输出
                printf("\n");
#endif
                        
        }
}

void EasyPath( ListMatrix * G, int star, int end, int path[],int d )
{//d初始化为0，标记路的长度
        int m,i;
        ArcNode *p;

        visited[star] = 1; // 标记已访问
        d++;//长度加一
        path[d] = star;//路径符号进入
        if( star == end )
        {
                for( i=1; i<=d; i++ )
                        printf("%d",path[i]);
                printf("\n");
        }//开始等与结束时，输出路径
        p =G->vertex[star].next;

        while( p!=NULL )        
        {
                m = p->adjvex;
                if(!visited[m])
                        EasyPath(G,m,end,path,d);
                p = p->next;
        }
        visited[star]=0;//访问回溯遍历
}

void ShortestEasyPath( ListMatrix * G, int star, int end, int path[],int d,int  allpath[][NUMMAX],int* count )
{//d初始化为0，标记路的长度
        int m,i;
        ArcNode *p;

        visited[star] = 1; // 标记已访问
        d++;//长度加一
        path[d] = star;//路径符号进入
        if( star == end )
        {
                (*count)++;
                allpath[*count][0] = d;
                for( i=1; i<=d; i++ )
                       allpath[*count][i] = path[i];
        }//开始等与结束时，输出路径
        p =G->vertex[star].next;

        while( p!=NULL )
        {
                m = p->adjvex;
                if(!visited[m])
                    ShortestEasyPath(G,m,end,path,d,allpath,count);
                p = p->next;
        }
        visited[star]=0;//访问回溯遍历
}
void ShortestPath( ListMatrix *G,int start, int dist[], int path[][NUMMAX])
{
        int mindist;
        int i,j,k;
        int t = 1;
        ArcNode * p;


        for( i=1; i<=G->vexnum; i++ )
        {
                dist[i] = INFNITY; 
        }
        p = G->vertex[start].next;
        while( p!=NULL )
        {
                dist[p->adjvex] = p->weight;
                path[p->adjvex][1] = start;//任一个和start相连的点，第一个必为 start
                p = p->next;
        }

        path[start][0] = 1;//进入v集

        for( i=2; i<=G->vexnum; i++ )
        {
                mindist = INFNITY;


                for( j=1; j<=G->vexnum; j++ )
                {
                        if(!path[j][0]&&dist[j]<mindist)
                        {
                                k = j;
                                mindist = dist[j];
                        }
                }
                
                if( mindist == INFNITY ) return;
                 
                path[k][0] = 1;//入V集

                p = G->vertex[k].next;//查看他连通几个点
                while( p!=NULL )
                {
                        if( mindist+p->weight < dist[p->adjvex] )//是否满足变短
                        {
                                dist[p->adjvex] = mindist+p->weight;//改变dist的值

                                t = 1;
                                while( path[k][t] != 0 )
                                {
                                        path[p->adjvex][t] = path[k][t];
                                        t++;
                                }

                                path[p->adjvex][t] = k;
                                path[p->adjvex][t+1] = 0;//将到从start点到p->adjvex 点的路径放入 对应的path[p->adjvex][]
                        }

                        p = p->next;
                }//while 判断与k 相连的节点，是否可以通过k，缩短路径长度

        }//for 循环 n-1 次找到n-1的最短路径
}
void Prim( ListMatrix *G, int start )
/*
 * 寻找一某一点为核心的最佳布线
 * 即使用prime最小生成树
 */
 {
         struct{
                 int adjvex;
                 int lowcost;
         }closedge[NUMMAX];

         int i,j,k,m,min;
         ArcNode * p;

         closedge[start].lowcost = 0;

         for( i=1; i<=G->vexnum; i++ )
         {
                 if( i != start )
                 {
                         closedge[i].adjvex = start;
                         closedge[i].lowcost = INFNITY;
                 }
         }//初始化，无穷大
         
         p = G->vertex[start].next;
         while( p != NULL )
         {
                 closedge[p->adjvex].lowcost = p->weight;
                 p = p->next;
         }//复制

         for( j=1; j<=G->vexnum; j++ )
         {
                 min = INFNITY;
                 for( k=1; k<=G->vexnum; k++ )
                 {
                          if( closedge[k].lowcost!=0 && closedge[k].lowcost < min )
                         {
                              m = k;
                              min = closedge[k].lowcost;
                         }
                 }//挑选最小的

                 closedge[m].lowcost = 0;

                 p = G->vertex[m].next;

                 while( p != NULL )
                 {
                         if( p->weight < closedge[p->adjvex].lowcost )
                         {
                                 closedge[p->adjvex].lowcost = p->weight;
                                 closedge[p->adjvex].adjvex = m;
                         }
                         p = p->next;
                 }//while 找到变短的
         }
                       printf("\t\t\t\t\t\t\t布线方式:\n");
         for( i=1; i<=G->vexnum; i++ )
         {
                 if( i!= start)
                 {
                       printf("\t\t\t\t\t\t\t%d 从%d:%s 到 %d:%s\n ",i,closedge[i].adjvex,
                                 NumtoName(G,closedge[i].adjvex),i,NumtoName(G,i));
                        
                 }
         }

 }

        

 




 
