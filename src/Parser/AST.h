// --*- C++ -*-------------------------------------//
// 
//                 The Loli Language
//
//
// filename: AST.h
// descript: Defines the AST Node.
// author  : Kevin Hu <hxy9243@gmail.com>
// note: 
//
//-------------------------------------------------//


#ifndef __AST_H__
#define __AST_H__


namespace lolilang {


// --------------------------- //
// ASTNode class
// --------------------------- //
class ASTNode
{
public:
    ASTNode(int position);
    ~ASTNode();

private:
    
};


// --------------------------- //
// Expresson Node
// --------------------------- //
class Expression : public ASTNode
{
public:
    Expression(int position);
    ~Expression();

private:
    
};


// --------------------------- //
// Identifier Node
// --------------------------- //
class Identifier : public Expression
{
public:
    Identifier(int position);
    ~Identifier();

private:
    
};


// --------------------------- //
// Literal Node
// --------------------------- //
class Literal : public Expression
{
public:
    Literal(int position);
    ~Literal();

private:
    
};


// --------------------------- //
// ProcCall Node
// --------------------------- //
class ProcCall : public Expression
{
public:
    ProcCall(int position);
    ~ProcCall();

private:
    
};


// --------------------------- //
// LambdaExpr Node
// --------------------------- //
class LambdaExpr : public Expression
{
public:
    LambdaExpr(int position);
    ~LambdaExpr();

private:
    
};


// --------------------------- //
// Conditional Node
// --------------------------- //
class Conditional : public Expression
{
public:
    Conditional(int position);
    ~Conditional();

private:
    
};


} // namespace


#endif
