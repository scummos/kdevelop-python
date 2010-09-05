// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "pythonvisitor.h"

namespace PythonParser
{

void Visitor::visitNode(AstNode *node)
{
    if (node)
    {
        switch (node->kind)
        {
        case AstNode::AndExprKind:
            visitAndExpr(reinterpret_cast<AndExprAst*>(node));
            break;
        case AstNode::AndTestKind:
            visitAndTest(reinterpret_cast<AndTestAst*>(node));
            break;
        case AstNode::ArglistKind:
            visitArglist(reinterpret_cast<ArglistAst*>(node));
            break;
        case AstNode::ArgumentKind:
            visitArgument(reinterpret_cast<ArgumentAst*>(node));
            break;
        case AstNode::ArithExprKind:
            visitArithExpr(reinterpret_cast<ArithExprAst*>(node));
            break;
        case AstNode::ArithOpKind:
            visitArithOp(reinterpret_cast<ArithOpAst*>(node));
            break;
        case AstNode::AssertStmtKind:
            visitAssertStmt(reinterpret_cast<AssertStmtAst*>(node));
            break;
        case AstNode::AtomKind:
            visitAtom(reinterpret_cast<AtomAst*>(node));
            break;
        case AstNode::AugassignKind:
            visitAugassign(reinterpret_cast<AugassignAst*>(node));
            break;
        case AstNode::BreakStmtKind:
            visitBreakStmt(reinterpret_cast<BreakStmtAst*>(node));
            break;
        case AstNode::ClassdefKind:
            visitClassdef(reinterpret_cast<ClassdefAst*>(node));
            break;
        case AstNode::CodeexprKind:
            visitCodeexpr(reinterpret_cast<CodeexprAst*>(node));
            break;
        case AstNode::CompOpKind:
            visitCompOp(reinterpret_cast<CompOpAst*>(node));
            break;
        case AstNode::ComparisonKind:
            visitComparison(reinterpret_cast<ComparisonAst*>(node));
            break;
        case AstNode::CompoundStmtKind:
            visitCompoundStmt(reinterpret_cast<CompoundStmtAst*>(node));
            break;
        case AstNode::ContinueStmtKind:
            visitContinueStmt(reinterpret_cast<ContinueStmtAst*>(node));
            break;
        case AstNode::DecoratorKind:
            visitDecorator(reinterpret_cast<DecoratorAst*>(node));
            break;
        case AstNode::DecoratorsKind:
            visitDecorators(reinterpret_cast<DecoratorsAst*>(node));
            break;
        case AstNode::DefparamKind:
            visitDefparam(reinterpret_cast<DefparamAst*>(node));
            break;
        case AstNode::DelStmtKind:
            visitDelStmt(reinterpret_cast<DelStmtAst*>(node));
            break;
        case AstNode::DictParamKind:
            visitDictParam(reinterpret_cast<DictParamAst*>(node));
            break;
        case AstNode::DictmakerKind:
            visitDictmaker(reinterpret_cast<DictmakerAst*>(node));
            break;
        case AstNode::DottedAsNameKind:
            visitDottedAsName(reinterpret_cast<DottedAsNameAst*>(node));
            break;
        case AstNode::DottedAsNamesKind:
            visitDottedAsNames(reinterpret_cast<DottedAsNamesAst*>(node));
            break;
        case AstNode::DottedNameKind:
            visitDottedName(reinterpret_cast<DottedNameAst*>(node));
            break;
        case AstNode::ExceptClauseKind:
            visitExceptClause(reinterpret_cast<ExceptClauseAst*>(node));
            break;
        case AstNode::ExecStmtKind:
            visitExecStmt(reinterpret_cast<ExecStmtAst*>(node));
            break;
        case AstNode::ExprKind:
            visitExpr(reinterpret_cast<ExprAst*>(node));
            break;
        case AstNode::ExprStmtKind:
            visitExprStmt(reinterpret_cast<ExprStmtAst*>(node));
            break;
        case AstNode::ExprlistKind:
            visitExprlist(reinterpret_cast<ExprlistAst*>(node));
            break;
        case AstNode::FactOpKind:
            visitFactOp(reinterpret_cast<FactOpAst*>(node));
            break;
        case AstNode::FactorKind:
            visitFactor(reinterpret_cast<FactorAst*>(node));
            break;
        case AstNode::FlowStmtKind:
            visitFlowStmt(reinterpret_cast<FlowStmtAst*>(node));
            break;
        case AstNode::ForStmtKind:
            visitForStmt(reinterpret_cast<ForStmtAst*>(node));
            break;
        case AstNode::FpDefKind:
            visitFpDef(reinterpret_cast<FpDefAst*>(node));
            break;
        case AstNode::FplistKind:
            visitFplist(reinterpret_cast<FplistAst*>(node));
            break;
        case AstNode::FunPosParamKind:
            visitFunPosParam(reinterpret_cast<FunPosParamAst*>(node));
            break;
        case AstNode::FuncDefKind:
            visitFuncDef(reinterpret_cast<FuncDefAst*>(node));
            break;
        case AstNode::FuncdeclKind:
            visitFuncdecl(reinterpret_cast<FuncdeclAst*>(node));
            break;
        case AstNode::GenForKind:
            visitGenFor(reinterpret_cast<GenForAst*>(node));
            break;
        case AstNode::GenIfKind:
            visitGenIf(reinterpret_cast<GenIfAst*>(node));
            break;
        case AstNode::GenIterKind:
            visitGenIter(reinterpret_cast<GenIterAst*>(node));
            break;
        case AstNode::GlobalStmtKind:
            visitGlobalStmt(reinterpret_cast<GlobalStmtAst*>(node));
            break;
        case AstNode::IfStmtKind:
            visitIfStmt(reinterpret_cast<IfStmtAst*>(node));
            break;
        case AstNode::ImportAsNameKind:
            visitImportAsName(reinterpret_cast<ImportAsNameAst*>(node));
            break;
        case AstNode::ImportAsNamesKind:
            visitImportAsNames(reinterpret_cast<ImportAsNamesAst*>(node));
            break;
        case AstNode::ImportFromKind:
            visitImportFrom(reinterpret_cast<ImportFromAst*>(node));
            break;
        case AstNode::ImportNameKind:
            visitImportName(reinterpret_cast<ImportNameAst*>(node));
            break;
        case AstNode::ImportStmtKind:
            visitImportStmt(reinterpret_cast<ImportStmtAst*>(node));
            break;
        case AstNode::LambdaDefKind:
            visitLambdaDef(reinterpret_cast<LambdaDefAst*>(node));
            break;
        case AstNode::ListForKind:
            visitListFor(reinterpret_cast<ListForAst*>(node));
            break;
        case AstNode::ListIfKind:
            visitListIf(reinterpret_cast<ListIfAst*>(node));
            break;
        case AstNode::ListIterKind:
            visitListIter(reinterpret_cast<ListIterAst*>(node));
            break;
        case AstNode::ListMakerTestKind:
            visitListMakerTest(reinterpret_cast<ListMakerTestAst*>(node));
            break;
        case AstNode::ListParamKind:
            visitListParam(reinterpret_cast<ListParamAst*>(node));
            break;
        case AstNode::ListmakerKind:
            visitListmaker(reinterpret_cast<ListmakerAst*>(node));
            break;
        case AstNode::NotTestKind:
            visitNotTest(reinterpret_cast<NotTestAst*>(node));
            break;
        case AstNode::NumberKind:
            visitNumber(reinterpret_cast<NumberAst*>(node));
            break;
        case AstNode::PassStmtKind:
            visitPassStmt(reinterpret_cast<PassStmtAst*>(node));
            break;
        case AstNode::PlainArgumentsListKind:
            visitPlainArgumentsList(reinterpret_cast<PlainArgumentsListAst*>(node));
            break;
        case AstNode::PowerKind:
            visitPower(reinterpret_cast<PowerAst*>(node));
            break;
        case AstNode::PrintStmtKind:
            visitPrintStmt(reinterpret_cast<PrintStmtAst*>(node));
            break;
        case AstNode::ProjectKind:
            visitProject(reinterpret_cast<ProjectAst*>(node));
            break;
        case AstNode::RaiseStmtKind:
            visitRaiseStmt(reinterpret_cast<RaiseStmtAst*>(node));
            break;
        case AstNode::ReturnStmtKind:
            visitReturnStmt(reinterpret_cast<ReturnStmtAst*>(node));
            break;
        case AstNode::ShiftExprKind:
            visitShiftExpr(reinterpret_cast<ShiftExprAst*>(node));
            break;
        case AstNode::ShiftOpKind:
            visitShiftOp(reinterpret_cast<ShiftOpAst*>(node));
            break;
        case AstNode::SimpleStmtKind:
            visitSimpleStmt(reinterpret_cast<SimpleStmtAst*>(node));
            break;
        case AstNode::SmallStmtKind:
            visitSmallStmt(reinterpret_cast<SmallStmtAst*>(node));
            break;
        case AstNode::StmtKind:
            visitStmt(reinterpret_cast<StmtAst*>(node));
            break;
        case AstNode::SubscriptKind:
            visitSubscript(reinterpret_cast<SubscriptAst*>(node));
            break;
        case AstNode::SubscriptlistKind:
            visitSubscriptlist(reinterpret_cast<SubscriptlistAst*>(node));
            break;
        case AstNode::SuiteKind:
            visitSuite(reinterpret_cast<SuiteAst*>(node));
            break;
        case AstNode::TermKind:
            visitTerm(reinterpret_cast<TermAst*>(node));
            break;
        case AstNode::TermOpKind:
            visitTermOp(reinterpret_cast<TermOpAst*>(node));
            break;
        case AstNode::TestKind:
            visitTest(reinterpret_cast<TestAst*>(node));
            break;
        case AstNode::TestlistKind:
            visitTestlist(reinterpret_cast<TestlistAst*>(node));
            break;
        case AstNode::TestlistSafeKind:
            visitTestlistSafe(reinterpret_cast<TestlistSafeAst*>(node));
            break;
        case AstNode::TrailerKind:
            visitTrailer(reinterpret_cast<TrailerAst*>(node));
            break;
        case AstNode::TryStmtKind:
            visitTryStmt(reinterpret_cast<TryStmtAst*>(node));
            break;
        case AstNode::VarargslistKind:
            visitVarargslist(reinterpret_cast<VarargslistAst*>(node));
            break;
        case AstNode::WhileStmtKind:
            visitWhileStmt(reinterpret_cast<WhileStmtAst*>(node));
            break;
        case AstNode::XorExprKind:
            visitXorExpr(reinterpret_cast<XorExprAst*>(node));
            break;
        case AstNode::YieldExprKind:
            visitYieldExpr(reinterpret_cast<YieldExprAst*>(node));
            break;
        case AstNode::YieldStmtKind:
            visitYieldStmt(reinterpret_cast<YieldStmtAst*>(node));
            break;
        default:
            Q_ASSERT(false);
        }
    }
}

} // end of namespace PythonParser

