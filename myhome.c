/*
 * =====================================================================================
 *
 *       Filename:  myhome.c
 *
 *    Description:  读取文件，建立邻接表
 *                  增加和删除节点和路线
 *        Version:  1.0
 *        Created:  2014年12月07日 19时03分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (fgm), mehner.fritz@fh-swf.de
 *   Organization:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include"myhome.h"
int  MakeMap( ListMatrix *G )
/*
 * 利用文件建立地图
 * 输入存放节点的文件 fp1 ，存放弧的文件fp2
 *
*/
{ 
        FILE  * fp1;
        FILE  * fp2;
   int  nodecount = 0;
   int  arccount = 0;
   Data nodedata;
   Arc  arcdata;
   ArcNode * p;
   ArcNode * temp;
        if( (fp1=fopen("vex","ab+")) == NULL )
        {
             printf("vex打开错误");
             return 0;
        }
        if( (fp2=fopen("arc","ab+")) == NULL )
        {
                printf("arc打开错误\n");
                return 0;
        }
   
   while( fread(&nodedata,sizeof(Data),1,fp1) == 1 )
   { 
           nodecount++; 
           strcpy(G->vertex[nodecount].vexdata.placename,nodedata.placename);
           strcpy(G->vertex[nodecount].vexdata.placedata,nodedata.placedata);  
           G->vertex[nodecount].next = NULL;
   }//读取节点

   if( nodecount != 0 )
   {
        while( fread( &arcdata,sizeof(Arc),1,fp2) == 1 )
        {
        
                arccount++;

#if(0)
                printf("%d:",arccount);
                printf("出：%d,入：%d\n",arcdata.forvex,arcdata.backves);
#endif
                temp = ( ArcNode *)malloc(sizeof(ArcNode));
                temp->adjvex = arcdata.backves;
                temp->weight = arcdata.weight;
                temp->next = NULL;
 
                p = G->vertex[arcdata.forvex].next;
                while( p && p->next )  p = p->next;
                if( !p )    G->vertex[arcdata.forvex].next = temp;
                else        p->next =temp;//挂链
        }
   }//读取弧
   G->vexnum = nodecount;
   G->arcnum = arccount;
   fclose(fp1);
   fclose(fp2);
   return 1;
}

int WriteMaptoFile( ListMatrix * G )
{
        FILE *fp1;
        FILE *fp2;
        int i;
        ArcNode * p;
        Arc  arcdata;
        if( (fp1=fopen("vex","wb")) == NULL )
        {
             printf("vex打开错误");
             return 0;
        }
        if( (fp2=fopen("arc","wb")) == NULL )
        {
                printf("arc打开错误\n");
                return 0;
        }

        for( i=1; i<=G->vexnum; i++ )
        {
           if( fwrite( &(G->vertex[i].vexdata), sizeof(Data), 1, fp1) != 1)
           {
                   printf("节点数据写入错误\n");
                   return 0;
           }
            
           p = G->vertex[i].next;
           while( p!=NULL )
           {
                   arcdata.forvex = i;
                   arcdata.backves = p->adjvex;
                   arcdata.weight = p->weight;
                   if(fwrite(&arcdata,sizeof(Arc),1,fp2)!=1)
                   {
                           printf("弧信息写入错误\n");
                           return 0;
                   }

                   p = p->next;
           }

        }//写入弧和节点的信息
   fclose(fp1);
   fclose(fp2);
   return 1;
}
void AddPlace( ListMatrix * G )
{
        int nodenum;
        G->vexnum++;
        nodenum = G->vexnum;
                       printf("\t\t\t\t\t\t\t输入地点名:");
        scanf("%s",G->vertex[nodenum].vexdata.placename);
                       printf("\t\t\t\t\t\t\t输入地点信息:");
        scanf("%s",G->vertex[nodenum].vexdata.placedata);
        G->vertex[nodenum].next = NULL;
        
}
#if(0)
                       printf("\t\t\t\t\t\t\t");
#endif
int  AddArc( ListMatrix * G  )
/*
 * 增加弧
 * 成功返回1
 * 失败返回0
 */
{
     char forvextemp[NAMEMAX]; 
     char backvextemp[NAMEMAX];
     int forvex;
     int backvex;
     ArcNode * temp;
     ArcNode * temp2;
     ArcNode * p;
     printf(":");
                       printf("\t\t\t\t\t\t\t输入起点：");
#if(1)
     scanf("%s",forvextemp);
    if( (forvex = NametoNum( G, forvextemp )) == 0  )
    {
            return 0;
    }
                       printf("\t\t\t\t\t\t\t输入终点:");
    scanf("%s",backvextemp);
    if( (backvex = NametoNum( G,backvextemp)) == 0 )
    {
            return 0;
    }//读取起点和终点
#endif//用字符标记

#if(0)
     scanf("%d",&forvex);
    if( forvex > G->vexnum  )
    {
            return 0;
    }
    printf("输入终点:");
    scanf("%d",&backvex);
    if( backvex > G->vexnum )
    {
            return 0;
    }
#endif//用数字标记

    G->arcnum++;//弧数加一

    temp = (ArcNode*)malloc(sizeof(ArcNode));
                       printf("\t\t\t\t\t\t\t输入路径长度");
    scanf("%d",&temp->weight);
    temp->adjvex = backvex;
    temp->next = NULL;//赋值

    p = G->vertex[forvex].next;
    while( p&&p->next )  p = p->next;
    if( !p )  G->vertex[forvex].next = temp;
    else      p->next = temp; //挂链
#if(1)
    G->arcnum++;//弧数加一

    temp2 = (ArcNode*)malloc(sizeof(ArcNode));
    temp2->weight = temp->weight;
    temp2->adjvex = forvex;
    temp2->next = NULL;//赋值

    p = G->vertex[backvex].next;
    while( p&&p->next )  p = p->next;
    if( !p )  G->vertex[backvex].next = temp2;
    else      p->next = temp2; //挂链
#endif
    return 1;

    
}
int DeleArc( ListMatrix * G , int start, int end )
/* 删除节点
 * 成功返回以
 * 失败返回0
 * */
{
        ArcNode * temp;
        ArcNode * p;

        p = G->vertex[start].next;
        temp = G->vertex[start].next;

        while( p != NULL )
        {
                if( p->adjvex == end && p == G->vertex[start].next)
                {
                        G->vertex[start].next = p->next;
                        free( p );
                        break;
                }else if( p->adjvex == end && p != G->vertex[start].next )
                {
                        temp->next = p->next;
                        free( p );
                        break;

                }
                 if( temp == G->vertex[start].next )
                 {
                         ;
                 }
                 else{
                         temp = temp->next;
                 }
                p = p->next;
        }

        p = G->vertex[end].next;
        temp = G->vertex[end].next;

        while( p != NULL )
        {
                if( p->adjvex == start && p == G->vertex[end].next)
                {
                        G->vertex[end].next = p->next;
                        free( p );
                        return 1;
                }else if( p->adjvex == start && p != G->vertex[end].next )
                {
                        temp->next = p->next;
                        free( p );
                        return 1;

                }
                 if( temp == G->vertex[end].next )
                 {
                         ;
                 }
                 else{
                         temp = temp->next;
                 }
                p = p->next;
        }
#if(0)
        p = G->vertex[end].next;

        while( p != NULL )
        {
                if( p->adjvex == start )
                {
                        temp = p;
                        p = p->next;
                        free( temp );
                        return 1;
                }
                
                p = p->next;
        }
#endif//错误代码

        return 0;
}

int NametoNum( ListMatrix *G, char * name )
{
        int i;
        for( i=1; i<=G->vexnum; i++ )
        {
                if( strcmp( name, G->vertex[i].vexdata.placename) == 0  )
                        return i;
        }
        return 0;
}


VertxNode * SearchNode( ListMatrix *G ,char * name )
{
        int i;
        for( i=0; i<=G->vexnum; i++ )
        {
                if( strcmp( name, G->vertex[i].vexdata.placename ) == 0 )
                        return &(G->vertex[i]);
        }
        return NULL;
}
char * NumtoName( ListMatrix *G, int i )
{
        if( i > G->vexnum ) return NULL;
        return G->vertex[i].vexdata.placename;
        
}

int DeletNode( ListMatrix *G  , char * name )
{
        ArcNode * p;
        int num;
        int count=0;
        int data[NAMEMAX] ={0};
        int i;
        ArcNode temp;
        if( (num = NametoNum(G,name)) == 0 )
                {
                        return 0;
                }
        p = G->vertex[num].next;

        while( p!=NULL )
        {
                count++;
                data[count] = p->adjvex;
                 p = p->next;
        }
        for( i=1; data[i]!=0 ; i++ )
        {
                DeleArc( G,num,data[i]);
        }
        for( i =num; i<G->vexnum; i++ )
        {
                G->vertex[i] = G->vertex[i+1];
        }
        for( i=1; i<G->vexnum; i++ )
        {
                p = G->vertex[i].next;
                while( p!= NULL )
                {
                        if( p->adjvex > num )
                                p->adjvex--;
                        p = p->next;
                }
        }
        return 0;


}
