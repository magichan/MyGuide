/*
 * =====================================================================================
 *
 *       Filename:  function.h
 *
 *    Description:  用于实现利用图的性质的各种功能
 *            
 *
 *        Version:  1.0
 *        Created:  2014年12月09日 08时19分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (fgm), mehner.fritz@fh-swf.de
 *   Organization:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
void DFTallList(ListMatrix *G );
void DFTList( ListMatrix*G ,int v0);

void AllEasyPath( ListMatrix * G, int star, int end, int  choose );
void EasyPath( ListMatrix * G, int star, int end, int path[],int d );
void ShortestEasyPath( ListMatrix * G, int star, int end, int path[],int d,int  allpath[][NUMMAX],int* count );
void ShortestPath( ListMatrix *G,int start, int dist[], int path[][NUMMAX]);
void Prim( ListMatrix *G, int start );
void Menu( void );        
void map( void );
void _fflush( void );



