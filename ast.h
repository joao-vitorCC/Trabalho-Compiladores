#ifndef AST
# define AST
#endif
enum tiposNo{
	programa,
	declFuncV,
	declP,
	declV,
	declF,
	listaPar,
	bloco,
	listaDeclV,
	tipoInt,
	tipoCar,
	listaCom,
	comanRet,
	comanLeia,
	comanEscrevaExp,
	comanEscrevaCadeia,
	comanLinha,
	comanSe,
	comanSeSenao,
	comanEnquanto,
	exprAtrib,
	exprOr,
	exprAnd,
	exprEq,
	exprDif,
	exprMenor,
	exprMaior,
	exprMaiorEq,
	exprMenorEq,
	exprAdicao,
	exprSubtracao,
	exprMult,
	exprDiv,
	exprInv,
	exprNeg,
	exprChamaFuncParam,
	exprChamaFuncSParam,
	exprVar,
	exprCadeiaConst,
	exprIntConst,
	exprParen
};
struct no{
	enum tiposNo t;
	char nome[10000]; 
	char valor[10000]; 
	struct no *f1;
	struct no* f2;
	struct no *f3;
	struct no * proximo;
	
};
struct no * criaNo(enum tiposNo t, char nome[],char valor[]);
