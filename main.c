/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  myhome 的主程序
 *
 *        Version:  1.0
 *        Created:  2014年12月08日 16时23分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (fgm), mehner.fritz@fh-swf.de
 *   Organization:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include "myhome.h"
#include "function.h"
extern int visited[NUMMAX];

int main( void )
{ 
        int i;
        int j;
        char choose = 0;
        int count = 0;//时时计数
        int start;
        int end;
        int dist[NUMMAX];
        int path[NUMMAX][NUMMAX]={0};
        char nametemp[NAMEMAX];
        VertxNode * tempNode;
        ArcNode * p;
        ListMatrix G;
        MakeMap(&G);

        Menu();
                       printf("\t\t\t\t\t\t\t输入:");
        choose = getchar();

        while( choose != '0' )
        {
                 switch( choose )
                 {

                         case '1':map();
                                  _fflush();
                                  break;
                         case '2':
                                  for( i=1; i<=G.vexnum; i++ )
                       printf("\t\t\t\t\t\t\t%d:%s\n",i,G.vertex[i].vexdata.placename);
                                  _fflush();
                                  break;
                         case '3':
                                  for( i=0;i<=G.vexnum; i++)
                                          visited[i] = 0;
#if(1)
                       printf("\t\t\t\t\t\t\t输入地名，搜索：");
        scanf("%s",nametemp);
        tempNode  = SearchNode( &G, nametemp );
        if( tempNode != NULL )
        {
                       printf("\t\t\t\t\t\t\t查询到%s\t,其可达：\n",tempNode->vexdata.placename);
                p = tempNode->next;
                while( p!=NULL )
                {
                        
                       printf("\t\t\t\t\t\t\t%s\n",G.vertex[p->adjvex].vexdata.placename);
                        p = p->next;
                }
        }
        else{
                      printf("\t\t\t\t\t\t\t没有找到\"%s\"\n",nametemp);
        }
        _fflush();

#endif//查询 
                                  break;
                         case '4':
                                  for( i=0;i<=G.vexnum; i++)
                                          visited[i] = 0;
                                          
#if(1)
           
                      printf("\t\t\t\t\t\t\t你在那里:");
                                  scanf("%s",nametemp);
                                  if( 0 == (start=NametoNum(&G,nametemp)) )
                                  {
                      printf("\t\t\t\t\t\t\tsorry,没有这个地方\n");
                      _fflush();
                      break;
                                  }
                      printf("\t\t\t\t\t\t\t你要去那里：");
                                  scanf("%s",nametemp);
                                  if( 0 == (end=NametoNum(&G,nametemp)) )
                                  {
                      printf("\t\t\t\t\t\t\tsorry,没有这个地方\n");
                      _fflush();
                      break;
                                  }
                                  AllEasyPath(&G,start,end,2);
#endif
                                  break;
                         case '5':
#if(1)
           
                      printf("\t\t\t\t\t\t\t你在那里:");
                                  scanf("%s",nametemp);
                                  if( 0 == (start=NametoNum(&G,nametemp)) )
                                  {
                      printf("\t\t\t\t\t\t\tsorry,没有这个地方\n");
                      _fflush();
                      break;
                                  }
        ShortestPath(&G,start,dist,path);
                      printf("\t\t\t\t\t\t\t你要去那里：");
                                  scanf("%s",nametemp);
                                  if( 0 == (end=NametoNum(&G,nametemp)) )
                                  {
                      printf("\t\t\t\t\t\t\tsorry,没有这个地方\n");
                      _fflush();
                      break;
                                  }

                      printf("\t\t\t\t\t\t\t路径为:\n");
                      printf("\t\t\t\t\t\t\t");
                for( j=1; j<=NUMMAX; j++ )
                {
                        if(!path[end][j])
                        {
                                printf("%s",NumtoName(&G,end));
                                
                                break;
                        }
                        printf("%s->",NumtoName(&G,path[end][j]));
                        if( j%2 == 0 )
                      printf("\n\t\t\t\t\t\t\t");

                }
                printf("\n");
                _fflush();
#endif
                                  break;
                         case '6':printf("%c",choose);
                                  for( i=0;i<=G.vexnum; i++)
                                          visited[i] = 0;
                      printf("\t\t\t\t\t\t\t输入布线起点：");
                                  scanf("%d",&start);
                                  Prim(&G,start);
                                  _fflush();
                                  break;
                         case '7':
                                  for( i=0;i<=G.vexnum; i++)
                                          visited[i] = 0;
                                  AddPlace( &G );
                                  _fflush();
                                  break;
                         case '8': 
                                  for( i=0;i<=G.vexnum; i++)
                                          visited[i] = 0;
                                  if(!AddArc( &G ))
                      printf("\t\t\t\t\t\t\t添加弧错误\n");
                                  _fflush();
                                  break;
                                  
                         case '9': 
                                  for( i=0;i<=G.vexnum; i++)
                                          visited[i] = 0;
                                  
                      printf("\t\t\t\t\t\t\t输入想删除弧的起点：");
                                  scanf("%s",nametemp);
                                  if( 0 == (start=NametoNum(&G,nametemp)))
                                  {
                      printf("\t\t\t\t\t\t\t地点不存在");
                                      _fflush();
                                      break;
                                  }
                      printf("\t\t\t\t\t\t\t输入想删除弧的终点：");
                                  scanf("%s",nametemp);
                                  if( 0 == (end=NametoNum(&G,nametemp)))
                                  {
                      printf("\t\t\t\t\t\t\t地点不存在");
                                      _fflush();
                                      break;
                                  }
                                  if(!DeleArc(&G , start, end)) 
                                          printf("\t\t\t\t\t\t\t删除失败，不存在该路");
                                          _fflush();
                                  break;
                         case '0':break;
                         default: break;
                 }
                       printf("\t\t\t\t\t\t\t输入:");
                 //_fflush();
                 choose = getchar();

        }

        
#if(0)
        for( i=1; i<=3; i++)
                AddPlace(&G);
#endif//添加节点
#if(0)
        for( i=1; i<=G.vexnum; i++)
                printf("%d:%s\n",i,G.vertex[i].vexdata.placename);
#endif//输出节点
#if(0)
        for( i=1; i<=1; i++)
                if(!AddArc(&G))
                {
                        printf("\n创建失败\n");
                }
#endif//添加弧
#if(0)
        printf("深度优先遍历:");
         DFTallList(&G); 
#endif
        printf("节点数:%d,弧数：%d\n",G.vexnum,G.arcnum);
#if(0)
        printf("所有简单路径:\n");
        AllEasyPath(&G,1,7,1);
        printf("最短简单路径:\n");
        AllEasyPath(&G,1,7,2);
#endif
#if(0)
        
        int dist[NUMMAX];
        int path[NUMMAX][NUMMAX]={0};
        int j;
        ShortestPath(&G,1,dist,path);
        for( i=1; i<=G.vexnum; i++ )
        {
                for( j=1; j<=NUMMAX; j++ )
                {
                        if(!path[i][j])
                        {
                                printf("%d\t",i);
                                break;
                        }
                        printf("%d\t",path[i][j]);
                }
                printf("\n");
        }


#endif//最短路径           
#if(0)
        Prim( &G, 1 );
#endif
        WriteMaptoFile(&G);
}

