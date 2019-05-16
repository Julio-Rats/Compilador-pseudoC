#ifndef  _LEXICO_
#define   _LEXICO_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define   STR_LEN  256

/*
		Enum que contem todos os tipos de TOKEN da linguagem, serve para a validação
			no processo sintatico (parser), ele é usado na estrutura Token que é usado no
			getToken, retornando a linha e coluna do arquivo fonte, junto com o lexema
			(Token puro, string no arquivo), e o Tipo do Token, expressado por este Enum.

*/

typedef enum{
		ABRIPAR  = 1  , FECHAPAR  , VIRG     , PONTVIRG , FOE        , ERROR      ,
		IDENT    = 7  , STR       , SOMA     , SUB      , DIVI       , ATRIB      ,
		MULT     = 13 , IGUAL     , MOD      , PRINT    , SCAN       , AND	      ,
		ABRICHAV = 19 , FECHACHAV , INT      , FLOAT    , BREAK      , CONTINUE   ,
		FOR      = 25 , NUMINT    , NUMFLOAT , WHILE    , IF         , ELSE       ,
		OR       = 31 , NOT       , MENOR    , MAIOR    , MENORIGUAL , MAIORIGUAL ,
		NIGUAL   = 37 , RETURN    ,
}TToken;

/*
		Enum para controle do estado atual da maquina de estado do analisador lexico,
			serve para indicar e controlar a variavel state_machine.

*/

typedef enum{
		START  = 1 , ID         , NUM   , NUMF , SSTR ,  ESTR       , COMENT     ,
		COMLIN     , ENDLINCOM  , EQUAL , GAND , GOR  ,  IGUALMAIOR , IGUALMENOR ,
		NEG        ,
}MachineState;

typedef struct{
		TToken    ttoken;
		char      lexema[STR_LEN];
		u_int32_t linha;
		u_int32_t coluna;
}Token;

FILE *file_src;

// 		Função que le um tokem valido ou erro, retorna como estrutura Token
//			tendo a string e o tipo (Token) dela.

Token getToken();

#endif // #ifndef LEXICO
