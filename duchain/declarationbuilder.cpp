/*****************************************************************************
 * Copyright (c) 2007 Piyush verma <piyush.verma@gmail.com>                  *
 * Copyright 2007 Andreas Pakulat <apaku@gmx.de>                             *
 * Copyright 2010 Sven Brauch <svenbrauch@googlemail.com>                    *
 *                                                                           *
 * Permission is hereby granted, free of charge, to any person obtaining     *
 * a copy of this software and associated documentation files (the           *
 * "Software"), to deal in the Software without restriction, including       *
 * without limitation the rights to use, copy, modify, merge, publish,       *
 * distribute, sublicense, and/or sell copies of the Software, and to        *
 * permit persons to whom the Software is furnished to do so, subject to     *
 * the following conditions:                                                 *
 *                                                                           *
 * The above copyright notice and this permission notice shall be            *
 * included in all copies or substantial portions of the Software.           *
 *                                                                           *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,           *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF        *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                     *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE    *
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION    *
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION     *
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.           *
 *****************************************************************************/
#include "declarationbuilder.h"

#include <QByteArray>

#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>

#include <language/duchain/functiondeclaration.h>
#include <language/duchain/classfunctiondeclaration.h>
#include <language/duchain/declaration.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/alltypes.h>
#include <language/duchain/types/abstracttype.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/classdeclaration.h>
#include <language/duchain/classfunctiondeclaration.h>
#include <language/duchain/classmemberdeclaration.h>
#include <language/duchain/classmemberdeclarationdata.h>
#include <language/duchain/types/unsuretype.h>
#include <language/duchain/builders/abstracttypebuilder.h>
#include <language/duchain/aliasdeclaration.h>

#include "contextbuilder.h"

#include "pythoneditorintegrator.h"
#include "QtGlobal"

#include <declarations/importedmoduledeclaration.h>
#include <../kdevplatform/language/duchain/declaration.h>


using namespace KTextEditor;

using namespace KDevelop;

namespace Python
{

DeclarationBuilder::DeclarationBuilder()
        : DeclarationBuilderBase()
{
    kDebug() << "Building Declarations";
}

DeclarationBuilder::DeclarationBuilder( PythonEditorIntegrator* editor )
        : DeclarationBuilderBase( )
{
    setEditor(editor);
    kDebug() << "Building Declarations";
}

DeclarationBuilder:: ~DeclarationBuilder()
{
}

void DeclarationBuilder::closeDeclaration()
{
    if ( lastContext() )
    {
        DUChainReadLocker lock( DUChain::lock() );
        currentDeclaration()->setKind( Declaration::Type );
    }

    eventuallyAssignInternalContext();

    DeclarationBuilderBase::closeDeclaration();
}

template<typename T> T* DeclarationBuilder::visitVariableDeclaration(Ast* node)
{
    NameAst* currentVariableDefinition = dynamic_cast<NameAst*>(node);
    Q_ASSERT(currentVariableDefinition);
    if ( currentVariableDefinition->context != ExpressionAst::Store
      && currentVariableDefinition->context != ExpressionAst::Parameter
      && currentVariableDefinition->context != ExpressionAst::AugStore
    ) {
            return 0;
    }
    Identifier* id = currentVariableDefinition->identifier;
    return visitVariableDeclaration<T>(id, currentVariableDefinition);
}

/*
 * WARNING: This will return a nullpointer if another than the expected type of variable was found!
 * */
template<typename T> T* DeclarationBuilder::visitVariableDeclaration(Identifier* node, Ast* originalAst)
{
    DUChainWriteLocker lock(DUChain::lock());
    Q_ASSERT(node);
    AssignmentAst* parent = dynamic_cast<AssignmentAst*>(node->parent->parent);
    
    QList<Declaration*> existingDeclarations;
    CursorInRevision until = editorFindRange(node, node).end;
    
    existingDeclarations = currentContext()->findDeclarations(identifierForNode(node), until);
    
    Declaration* dec = 0;
    
    kDebug() << "VARIABLE CONTEXT: " << currentContext()->scopeIdentifier() << currentContext()->range().castToSimpleRange() << currentContext()->type();
    
    if ( currentContext() && currentContext()->type() == DUContext::Class && ! existingDeclarations.length() ) {
        kDebug() << "Creating class member declaration for " << node->value << node->startLine << ":" << node->startCol;
        kDebug() << "Context type: " << currentContext()->scopeIdentifier() << currentContext()->range().castToSimpleRange();
        dec = openDeclaration<ClassMemberDeclaration>(node, originalAst ? originalAst : node, DeclarationIsDefinition);
        closeDeclaration();
    }
    else if ( ! existingDeclarations.length() ) {
        kDebug() << "Creating variable declaration for " << node->value << node->startLine << ":" << node->startCol;
        dec = openDeclaration<T>(node, originalAst ? originalAst : node, DeclarationIsDefinition);
        closeDeclaration();
//         dec->setType(IntegralType::Ptr(new IntegralType(IntegralType::TypeMixed)));
        dec->setKind(KDevelop::Declaration::Instance); // everything is an object in python
        if ( parent ) {
            NameAst* singleValue = dynamic_cast<NameAst*>(parent->value);
            if ( singleValue ) {
                kDebug() << "Found a single target value for variable declaration";
                QList<Declaration*> newValueDecs = currentContext()->findDeclarations(identifierForNode(singleValue->identifier), until);
                if ( newValueDecs.length() > 0 ) {
                    Declaration* newValueDec = newValueDecs.last();
                    kDebug() << newValueDec << newValueDec->type<AbstractType>();
                    dec->setType(newValueDec->type<AbstractType>());
                }
            }
        }
    }
    else {
        kDebug() << "Not updating existing declaration for " << node->value;
        dec = existingDeclarations.last();
        setEncountered(dec);
    }
    AssignmentAst* assignment = node->parent && node->parent->parent ? dynamic_cast<AssignmentAst*>(node->parent->parent) : 0;
    if ( dec->abstractType().isNull() && assignment && assignment->value ) {
        switch ( assignment->value->astType ) {
            case Python::Ast::StringAstType:
                kDebug() << "Found a string variable declaration";
                dec->setType(IntegralType::Ptr(new IntegralType(IntegralType::TypeString)));
                break;
            case Python::Ast::NumberAstType:
                kDebug() << "Found a number variable";
                dec->setType(IntegralType::Ptr(new IntegralType(IntegralType::TypeFloat)));
                break;
            default:
                kDebug() << "Could not determine type for variable " << node->value;
                break;
        }
    }
    else {
        kDebug() << "Could not convert variable declaration to assignment!";
    }
//     dec->setType<>();
    T* result = dynamic_cast<T*>(dec);
    if ( ! result ) kError() << "variable declaration does not have the expected type";
    return result;
}

void DeclarationBuilder::visitExceptionHandler(ExceptionHandlerAst* node)
{
    if ( node->name ) visitVariableDeclaration<Declaration>(node->name); // except Error as <vardecl>
    DeclarationBuilderBase::visitExceptionHandler(node);
}

void DeclarationBuilder::visitFor(ForAst* node)
{
    if ( node->target->astType == Ast::NameAstType ) visitVariableDeclaration<Declaration>(node->target);
    else if ( node->target->astType == Ast::TupleAstType ) {
        foreach ( ExpressionAst* tupleMember, dynamic_cast<TupleAst*>(node->target)->elements ) {
            if ( tupleMember->astType == Ast::NameAstType ) visitVariableDeclaration<Declaration>(tupleMember);
        }
    }
    Python::ContextBuilder::visitFor(node);
}

void DeclarationBuilder::visitImport(ImportAst* node)
{
    Python::ContextBuilder::visitImport(node);
    foreach ( AliasAst* name, node->names ) {
        TopDUContextPointer contextptr = contextsForModules.value(name->asName ? name->asName->identifier->value : name->name->value);
        kDebug() << "Chain for document: " << contextptr;
        m_importContextsForImportStatement.push(contextptr);
        importedModuleDeclaration* dec;
        if ( name->asName ) dec = visitVariableDeclaration<importedModuleDeclaration>(name->asName);
        else dec = visitVariableDeclaration<importedModuleDeclaration>(name->name);
        QString moduleName = name->name->value;
        if ( name->asName && name->asName->identifier ) 
            moduleName += "." + name->asName->identifier->value;
        kDebug() << "Module name: " << moduleName;
        if ( dec ) {
            DUChainWriteLocker lock(DUChain::lock());
            dec->m_moduleIdentifier = moduleName;
            dec->setType(IntegralType::Ptr(new IntegralType(IntegralType::TypeMixed)));
        }
        m_importContextsForImportStatement.clear();
    }
}

void DeclarationBuilder::visitImportFrom(ImportFromAst* node)
{
    Python::AstDefaultVisitor::visitImportFrom(node);
    foreach ( AliasAst* name, node->names ) {
        importedModuleDeclaration* dec = 0;
        if ( name->asName ) dec = visitVariableDeclaration<importedModuleDeclaration>(name->asName);
        else dec = visitVariableDeclaration<importedModuleDeclaration>(name->name);
        if ( dec && name->name && node->module ) {
            dec->m_moduleIdentifier = node->module->value + "." + name->name->value;
            kDebug() << "FromImport module name: " << name->name->value;
        }
        if ( dec ) {
            dec->setType(IntegralType::Ptr(new IntegralType(IntegralType::TypeMixed)));
        }
    }
}

void DeclarationBuilder::visitAssignment(AssignmentAst* node)
{
    foreach ( ExpressionAst* target, node->targets ) {
        if ( target->astType == Ast::NameAstType ) {
            visitVariableDeclaration<Declaration>(target);
        }
    }
    visitNode(node->value);
}

void DeclarationBuilder::visitClassDefinition( ClassDefinitionAst* node )
{
    kDebug() << "opening class definition";
//     ClassDeclaration* classDec = new ClassDeclaration(editorFindRange(node->body.first(), node->body.last()), currentContext());
    
    openDeclaration<ClassDeclaration>( node->name, node );
    eventuallyAssignInternalContext();
    closeDeclaration();
    
    DeclarationBuilderBase::visitClassDefinition( node );
}

void DeclarationBuilder::visitFunctionDefinition( FunctionDefinitionAst* node )
{
    kDebug() << "opening function definition";
    int decoratorOffset = node->decorators.length(); // adjust the actual range of the functions' name
    node->name->startLine += decoratorOffset; node->name->endLine += decoratorOffset;
    kDebug() << "Function definition RANGE:" << node->name->startLine << node->name->startCol << node->name->endLine << node->name->endCol;
    
    // adjust range of arguments, too
    if ( node->arguments ) {
        node->arguments->startLine += decoratorOffset;
        node->arguments->endLine += decoratorOffset;
    }
    
    FunctionDeclaration* dec = openDeclaration<FunctionDeclaration>( node->name, node );

    FunctionType::Ptr type(new FunctionType);

    openType(type);
    ContextBuilder::visitFunctionDefinition( node );
    closeType();

    {
        DUChainWriteLocker lock;
        dec->setType(type);
    }
    closeDeclaration();
}

void DeclarationBuilder::visitLambda( LambdaAst* node )
{
    kDebug() << "opening lambda def";
//     openDeclaration<FunctionDeclaration>( QualifiedIdentifier( "lambda" ), node ) );
    ContextBuilder::visitLambda( node );
//     closeDeclaration();
}

void DeclarationBuilder::visitCall(CallAst* node)
{
    foreach ( ExpressionAst* currentArgument, node->arguments ) {
        NameAst* realArgument = dynamic_cast<NameAst*>(currentArgument);
        if ( realArgument ) {
            visitVariableDeclaration<Declaration>(realArgument); // some_func(<arg1>, <arg2>)
        }
    }
    Python::AstDefaultVisitor::visitCall(node);
}

void DeclarationBuilder::visitArguments( ArgumentsAst* node )
{
    AbstractFunctionDeclaration* function = dynamic_cast<AbstractFunctionDeclaration*>(currentDeclaration());
    kDebug() << "Current context for parameters: " << currentContext();
    if ( function ) {
        NameAst* realParam;
        foreach (ExpressionAst* expression, node->arguments) {
            realParam = dynamic_cast<NameAst*>(expression);
            if ( realParam && realParam->context == ExpressionAst::Parameter ) {
                Declaration* paramDeclaration = visitVariableDeclaration<Declaration>(realParam);
                function->addDefaultParameter(IndexedString(realParam->identifier->value));
                FunctionType::Ptr type = currentType<FunctionType>();
                if ( type && paramDeclaration ) type->addArgument(paramDeclaration->abstractType());
            }
            else {
                DeclarationBuilderBase::visitArguments(node);
            }
        }
    }
}

}

