/*
 * =====================================================================================
 *
 *       Filename:  myhome.h
 *
 *    Description:  读取文件，建立邻接表
 *                  增加和删除节点和路线
 *
 *        Version:  1.0
 *        Created:  2014年12月07日 19时05分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (fgm), mehner.fritz@fh-swf.de
 *   Organization:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INFNITY 32768
#define DATAMAX 100
#define NAMEMAX 30
#define NUMMAX 40

typedef struct data{
        char placename[NAMEMAX];
        char placedata[DATAMAX];
}Data;
typedef struct arc{
        int forvex;
        int backves;
        int weight;
}Arc;//文件存储结构体

typedef struct arcnode{
        int adjvex;
        int weight;
        struct arcnode* next;
}ArcNode;

typedef struct vertexnode{
        Data vexdata;
        ArcNode * next;
}VertxNode;

typedef struct {
        VertxNode vertex[NUMMAX];
        int vexnum;
        int arcnum;
}ListMatrix;

/*
 * 利用文件建立地图
 * 输入存放节点的文件 fp1 ，存放弧的文件fp2
 *
*/
int  MakeMap(  ListMatrix *G  );
void  AddPlace( ListMatrix * G );
/*
 * 增加弧
 * 成功返回1
 * 失败返回0
 */
int  AddArc( ListMatrix * G );
int DelePalce( ListMatrix * G );
int DeleArc( ListMatrix * G , int start, int end );
int WriteMaptoFile( ListMatrix * G );
int NametoNum( ListMatrix *G, char * name );
char * NumtoName( ListMatrix *G, int i );
VertxNode * SearchNode( ListMatrix *G ,char * name );



