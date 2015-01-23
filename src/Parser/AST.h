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
    
}


// --------------------------- //
// Expresson Node
// --------------------------- //
class Expression : public ASTNode
{
public:
    ExpressionNode(int position);
    ~ExpressionNode();

private:
    
}


} // namespace


#endif
