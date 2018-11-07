#ifndef  _SEMANTICO_
#define  _SEMANTICO_

typedef enum{
    OPR = 1, IF, JUMP, LABEL, CALL,
}TInstruction;

typedef struct{
    TInstruction INSTRUCTION;
    char         OPR[2];
    char         REGISTER[3][16];
}t_bitcode;

extern t_bitcode  *listBitcode;

#endif
