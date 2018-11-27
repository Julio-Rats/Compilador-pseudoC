#include "lexico.h"

/*------------------------------------------------------------------------------

							Analisador Léxico

	Faz a leitura do arquivo fonte, caracter por caracter,
			pegando os tokens conforme estabelecido pela gramatica

------------------------------------------------------------------------------*/

Token getToken(){

	Token		STC_Token;	           	// ED de retorno do analisador léxico.
	char		char_atual;	           	// Caracter lido armazenado aq.
	char		str_atual[32]  = "";  	// String de retorno como lexema (VAR,NUM,STR).
	MachineState    			 state_machine    = 1;  // Estado de Maquina da autômato.
	short          int     flag_coment			 = 0;  // Verifica fim de comentario.
	unsigned short int	   str_length  			= 0;  // Comprimento atual da str_atual.
	static unsigned short int  coluna  			= 1;  // Coluna do arquivo TXT.
	static unsigned short int  linha 	 			= 1;  // Linha do aquivo TXT.

	while (1){   // WHILE TRUE machine state
		char_atual = fgetc(file_src);
		if (feof(file_src)){
				STC_Token.ttoken = FOE;
				strcpy(str_atual, "EOF");
				str_length = 3;
				coluna    += 4;
				break;
		} // if (feof(file_src))
		if (flag_coment){
				if (char_atual == '\n'){
						ungetc(char_atual,file_src);
						state_machine = START;
						flag_coment = 0;
				}
				continue;
		}
		if (((char_atual == '\n')||(char_atual == '\r'))&&
													((state_machine == COMLIN)||(state_machine == START))) {
				linha++;
				coluna  = 1;
				continue;
		}else{
				coluna++;
		}// if (char_atual == '\n')

		if (state_machine == START){
				if ((char_atual == ' ') || (char_atual == '\t')){
							continue;
				} // if ((char_atual == ' ') || (char_atual == '\t'))

				if (char_atual == '/'){
						state_machine = COMENT;
						continue;
				} // if (char_atual == '/')

				if (char_atual == '('){
						STC_Token.ttoken = ABRIPAR;
						str_length = 1;
						coluna++;
						strcpy(str_atual, "(");
						break;
				}// if (char_atual == '(')
				if (char_atual == ')'){
						STC_Token.ttoken = FECHAPAR;
						str_length = 1;
						coluna++;
						strcpy(str_atual, ")");
						break;
				}// if (char_atual == '(')
				if (char_atual == '{'){
						STC_Token.ttoken = ABRICHAV;
						str_length = 1;
						coluna++;
						strcpy(str_atual, "{");
						break;
				}// if (char_atual == '{')
				if (char_atual == '}'){
						STC_Token.ttoken = FECHACHAV;
						str_length = 1;
						coluna++;
						strcpy(str_atual, "}");
						break;
				}// if (char_atual == '}')
				if (char_atual == '='){
						state_machine = EQUAL;
						continue;
				}// if (char_atual == '=')
				if (char_atual == ','){
						STC_Token.ttoken = VIRG;
						str_length = 1;
						coluna++;
						strcpy(str_atual, ",");
						break;
				}// if (char_atual == ',')
				if (char_atual == '+'){
						STC_Token.ttoken = SOMA;
						str_length = 1;
						coluna++;
						strcpy(str_atual, "+");
						break;
				}// if (char_atual == '+')
				if (char_atual == '-'){
						STC_Token.ttoken = SUB;
						str_length = 1;
						coluna++;
						strcpy(str_atual, "-");
						break;
				}// if (char_atual == '-')
				if (char_atual == '/'){
						go_divi:
						STC_Token.ttoken = DIVI;
						str_length = 1;
						coluna++;
						strcpy(str_atual, "/");
						break;
				}// if (char_atual == '/')
				if (char_atual == '*') {
						STC_Token.ttoken = MULT;
						str_length       = 1;
						coluna++;
						strcpy(str_atual, "*");
						break;
				}// if (char_atual == '*')
				if (char_atual == '%'){
						STC_Token.ttoken = MOD;
						strcpy(str_atual, "%");
						coluna++;
						str_length = 1;
						break;
				}// if (char_atual == '%')
				if (char_atual == ';'){
						STC_Token.ttoken = PONTVIRG;
						strcpy(str_atual, ";");
						coluna++;
						str_length = 1;
						break;
				}// if (char_atual == ';')
				if (char_atual == '&'){
						state_machine = GAND;
						continue;
				}// if (char_atual == '&')
				if (char_atual == '|'){
						state_machine = GOR;
						continue;
				}// if (char_atual == '&')
				if (char_atual == '>'){
						state_machine = IGUALMAIOR;
						continue;
				}// if (char_atual == '>')
				if (char_atual == '<'){
					state_machine = IGUALMENOR;
					continue;
				}// if (char_atual == '>')
				if (char_atual == '!'){
					state_machine = NEG;
					continue;
				}//if (char_atual == '>')

				if ( ((char_atual >= 'a')&&(char_atual <= 'z')) || ((char_atual >= 'A')&&(char_atual <= 'Z')) ) {
						state_machine = ID;   // ----- VAR -----
						str_atual[str_length++] = char_atual;
						continue;
				}else if ((char_atual >= '0')&&(char_atual <= '9') ){
						state_machine = NUM;   // ----- NUM -----
						str_atual[str_length++] = char_atual;
						continue;
				}else if (char_atual == '"'){
						state_machine = SSTR;   // ----- STR -----
						str_atual[str_length++] = char_atual;
						continue;
				}
go_error:
				STC_Token.ttoken = ERROR;		// ----- ERROR -----
				str_atual[str_length++] = char_atual;
				coluna++;
				break;
		}// if (state_machine == START)



		if (state_machine == ID){ // VAR
				if ( ((char_atual >= 'a')&&(char_atual <= 'z')) || ((char_atual >= 'A')&&(char_atual <= 'Z')) ){
						str_atual[str_length++] = char_atual;
						continue;
				}
				if ((char_atual >= '0')&&(char_atual <= '9') ){
 						str_atual[str_length++] = char_atual;
						continue;
				}
				ungetc(char_atual, file_src);
				STC_Token.ttoken = IDENT;
				if (strcmp(str_atual,"print")==0) {
							STC_Token.ttoken = PRINT;
				}else if (strcmp(str_atual,"scan")==0){
							STC_Token.ttoken = SCAN;
				}else if (strcmp(str_atual,"break")==0){
							STC_Token.ttoken = BREAK;
				}else if (strcmp(str_atual,"continue")==0){
							STC_Token.ttoken = CONTINUE;
				}else if (strcmp(str_atual,"for")==0){
							STC_Token.ttoken = FOR;
				}else if (strcmp(str_atual,"else")==0){
							STC_Token.ttoken = ELSE;
				}else if (strcmp(str_atual,"while")==0){
							STC_Token.ttoken = WHILE;
				}else if (strcmp(str_atual,"if")==0){
							STC_Token.ttoken = IF;
				}else if (strcmp(str_atual,"int")==0){
							STC_Token.ttoken = INT;
				}else if (strcmp(str_atual,"float")==0){
							STC_Token.ttoken = FLOAT;
				}else if (strcmp(str_atual,"return")==0){
							STC_Token.ttoken = RETURN;
				}
				break;
		} //	if (state_machine == ID)



		if (state_machine == NUM){ // NUM
				if (char_atual == '.'){
						state_machine = NUMF;
						str_atual[str_length++] = char_atual;
						continue;
				}
				if ( (char_atual >= '0')&&(char_atual <= '9') ){
						str_atual[str_length++] = char_atual;
						continue;
				}
				ungetc(char_atual, file_src);
				STC_Token.ttoken = NUMint;
				break;
		}//	if (state_machine == NUM)

		if (state_machine == NUMF){ // NUMF
				if ( (char_atual >= '0')&&(char_atual <= '9') ) {
						str_atual[str_length++] = char_atual;
						continue;
				}
				ungetc(char_atual, file_src);
				STC_Token.ttoken = NUMfloat;
				break;
		}//	if (state_machine == NUMF)



		if (state_machine == SSTR){ // SSTR
				str_atual[str_length++] = char_atual;
				if (char_atual == '\\'){
						state_machine = ESTR;
						continue;
				}
				if (char_atual == '"'){
						STC_Token.ttoken = STR;
						coluna++;
						break;
				}
				continue;
		} // if (state_machine == SSTR)

		if (state_machine == ESTR){ // STR capture "\"
				str_atual[str_length++] = char_atual;
				state_machine = SSTR;
				continue;
		}// if (state_machine == ESTR)



		if (state_machine == EQUAL){
				if (char_atual == '='){
						STC_Token.ttoken = IGUAL;
						str_length = 2;
						coluna++;
						strcpy(str_atual, "==");
						break;
				}
				ungetc(char_atual,file_src);
				STC_Token.ttoken = ATRIB;
				str_length = 1;
				// coluna--;
				strcpy(str_atual, "=");
				break;
		} // if (state_machine == EQUAL)


		if (state_machine == GAND){
				if (char_atual != '&')
						goto go_error;

				STC_Token.ttoken = AND;
				str_length = 2;
				coluna++;
				strcpy(str_atual, "&&");
				break;

		}//if (state_machine == GAND)

		if (state_machine == GOR){
			if (char_atual != '|')
						goto go_error;

				STC_Token.ttoken = OR;
				str_length = 2;
				coluna++;
				strcpy(str_atual, "||");
				break;

		}//if (state_machine == GOR

		if (state_machine == IGUALMAIOR){
				if (char_atual == '='){
					STC_Token.ttoken = MAIORIGUAL;
					str_length = 2;
					coluna++;
					strcpy(str_atual, ">=");
					break;
				}
				ungetc(char_atual, file_src);
				STC_Token.ttoken = MAIOR;
				str_length = 1;
				// coluna++;
				strcpy(str_atual, ">");
				break;
		}//if (state_machine == IGUALMAIOR)

		if (state_machine == IGUALMENOR){
				if (char_atual == '='){
					STC_Token.ttoken = MENORIGUAL;
					str_length = 2;
					coluna++;
					strcpy(str_atual, "<=");
					break;
				}
				ungetc(char_atual, file_src);
				STC_Token.ttoken = MENOR;
				str_length = 1;
				// coluna++;
				strcpy(str_atual, "<");
				break;
		}//if (state_machine == IGUALMENOR)

		if (state_machine == NEG){
				if (char_atual == '='){
					STC_Token.ttoken = NIGUAL;
					str_length = 2;
					coluna++;
					strcpy(str_atual, "!=");
					break;
				}
				ungetc(char_atual, file_src);
				STC_Token.ttoken = NOT;
				str_length = 1;
				// coluna++;
				strcpy(str_atual, "!");
				break;
		}//if (state_machine == NEG)



		if (state_machine == COMENT){  // comentario
				if (char_atual == '/'){
						flag_coment = 1;
						continue;
				}
				if (char_atual == '*'){
						state_machine = COMLIN;
						continue;
				}
				ungetc(char_atual, file_src);
				coluna -= 1;
				goto go_divi;
		} // if (state_machine == COMENT)

		if (state_machine == COMLIN){
				if (char_atual == '*'){
						state_machine = ENDLINCOM;
				}
				continue;
		} // if (state_machine == COMLIN)

		if (state_machine == ENDLINCOM){
				if (char_atual == '/'){
						state_machine = START;
				}else{
						state_machine = COMLIN;
				}
				continue;
		} // if (state_machine == ENDLINCOM)

	} // while(1)

	str_atual[str_length] = '\0';
	STC_Token.linha       = linha;
	STC_Token.coluna      = (--coluna)-(str_length);
	strcpy(STC_Token.lexema,str_atual);
	return STC_Token;
} // getToken ()
