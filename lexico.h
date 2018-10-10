#ifndef LEXICO
#define  LEXICO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum{
		ABRIPAR  = 1  , FECHAPAR  , VIRG    , PONTVIRG , FOE        , ERROR      ,
		IDENT    = 7  , STR       , SOMA    , SUB      , DIVI       , ATRIB      ,
		MULT     = 13 , IGUAL     , MOD     , PRINT    , SCAN       , AND	       ,
		ABRICHAV = 19 , FECHACHAV , INT     , FLOAT    , BREAK      , CONTINUE   ,
		FOR      = 25 , NUMint    , NUMfloat , WHILE    , IF         , ELSE       ,
		OR       = 31 , NOT       , MENOR   , MAIOR    , MENORIGUAL , MAIORIGUAL ,
		NIGUAL        ,
}TToken;

typedef enum{
		START  = 1 , ID         , NUM   , NUMF , SSTR ,  ESTR       , COMENT     ,
		COMLIN     , ENDLINCOM  , EQUAL , GAND , GOR  ,  IGUALMAIOR , IGUALMENOR ,
		NEG        ,
}MachineState;



typedef struct{
		unsigned short int linha;
		unsigned short int coluna;
		char lexema[60];
		TToken ttoken;
}Token;

FILE *arq;
Token getToken();

#endif // #ifndef LEXICO
