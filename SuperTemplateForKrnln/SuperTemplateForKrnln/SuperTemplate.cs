using QIQI.EplOnCpp.Core;
using QIQI.EplOnCpp.Core.Expressions;
using QIQI.EProjectFile;
using System;
using System.Collections.Generic;

namespace e.lib.krnln
{
    public class SuperTemplate
    {
        public static void ReturnCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            if (expr.ParamList.Count == 1 && expr.ParamList[0] != null)
            {
                writer.Write("return ");
                expr.ParamList[0].WriteTo(writer);
            }
            else
            {
                writer.Write("return");
            }
        }

        public static void BreakCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            writer.Write("break");
        }

        public static void ContinueCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            writer.Write("continue");
        }

        public static void LetCmd(CodeConverter C, CodeWriter writer, EocCallExpression callExpr)
        {
            var target = callExpr.ParamList[0];
            C.WriteLetExpression(writer, target, () => callExpr.ParamList[1].WriteToWithCast(writer, target.GetResultType()));
        }

        public static void LetMutilCmd(CodeConverter C, CodeWriter writer, EocCallExpression callExpr)
        {
            var source = callExpr.ParamList[0];
            for (int i = 1; i < callExpr.ParamList.Count; i++)
            {
                var cur = callExpr.ParamList[i];
                source = new EocCallExpression(C, C.P.GetEocCmdInfo(0, 54), null, new List<EocExpression> { cur, source }, C.P.EocLibs[0].SuperTemplateAssembly);
            }
            source.WriteTo(writer);
        }

        public static void IsNullParameterCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            if (expr.ParamList[0] is EocVariableExpression x
                && x.VariableInfo is MethodParameterInfo paramInfo
                && paramInfo.OptionalParameter)
            {
                var name = C.P.GetUserDefinedName_SimpleCppName(x.VariableInfo.Id);
                writer.Write("eoc_isNull_");
                writer.Write(name);
            }
            else
            {
                throw new Exception("是否为空 只能用于 可空 参数");
            }
        }

        public static void AddCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            OperationCmd(C, writer, expr, "+", "e::lib::krnln::Add");
        }

        public static void SubCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            OperationCmd(C, writer, expr, "-", "e::lib::krnln::Sub");
        }

        public static void MulCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            OperationCmd(C, writer, expr, "*", "e::lib::krnln::Mul");
        }

        public static void EqualCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            OperationCmd(C, writer, expr, "==", "e::lib::krnln::Equal");
        }

        public static void UnequalCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            OperationCmd(C, writer, expr, "!=", "e::lib::krnln::Unequal");
        }

        public static void LessThanCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            OperationCmd(C, writer, expr, "<", "e::lib::krnln::LessThan");
        }

        public static void GreaterThanCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            OperationCmd(C, writer, expr, ">", "e::lib::krnln::GreaterThan");
        }

        public static void LessThanOrEqualCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            OperationCmd(C, writer, expr, "<=", "e::lib::krnln::LessThanOrEqual");
        }

        public static void GreaterThanOrEqualCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            OperationCmd(C, writer, expr, ">=", "e::lib::krnln::GreaterThanOrEqual");
        }

        public static void OperationCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr, string operation, string cmdForAny)
        {
            var resultType = GetOperatingType(C, expr);
            var expectedItemType = resultType;
            var itemSeparator = $" {operation} ";
            if (resultType == ProjectConverter.CppTypeName_Any || resultType == ProjectConverter.CppTypeName_SkipCheck)
            {
                expectedItemType = ProjectConverter.CppTypeName_SkipCheck;
                itemSeparator = ", ";
                writer.Write(cmdForAny);
            }
            writer.Write("(");
            for (int i = 0; i < expr.ParamList.Count; i++)
            {
                var item = expr.ParamList[i];
                if (i != 0)
                    writer.Write(itemSeparator);
                item.WriteToWithCast(writer, expectedItemType);
            }
            writer.Write(")");
        }

        public static CppTypeName GetOperatingTypeForDiv(CodeConverter C, EocCallExpression expr)
        {
            var r = GetOperatingType(C, expr);
            if (C.P.IsIntNumberType(r))
            {
                return ProjectConverter.CppTypeName_Double;
            }
            return r;
        }

        public static CppTypeName GetOperatingType(CodeConverter C, EocCallExpression expr)
        {
            if (expr.ParamList.Count == 0)
            {
                return ProjectConverter.CppTypeName_SkipCheck;
            }
            var P = C.P;
            var resultType = expr.ParamList[0].GetResultType();
            for (int i = 0; i < expr.ParamList.Count; i++)
            {
                var item = expr.ParamList[i];
                var itemType = item.GetResultType();
                if (itemType == ProjectConverter.CppTypeName_String
                    || itemType == ProjectConverter.CppTypeName_DateTime
                    || itemType == ProjectConverter.CppTypeName_Bin
                    || itemType == ProjectConverter.CppTypeName_Double)
                {
                    resultType = itemType;
                    break;
                }
                if (itemType == ProjectConverter.CppTypeName_Any || itemType == ProjectConverter.CppTypeName_SkipCheck)
                {
                    resultType = itemType;
                }
                else if (itemType == ProjectConverter.CppTypeName_IntPtr)
                {
                    resultType = ProjectConverter.CppTypeName_SkipCheck;
                }
                else
                {
                    if (P.IsIntNumberType(itemType))
                    {
                        if (P.IsIntNumberType(resultType))
                        {
                            if (P.GetIntNumberTypeSize(resultType) < P.GetIntNumberTypeSize(itemType))
                            {
                                resultType = itemType;
                            }
                        }
                    }
                    else if (P.IsFloatNumberType(itemType))
                    {
                        if (P.IsIntNumberType(resultType))
                        {
                            resultType = itemType;
                        }
                        else if (P.IsFloatNumberType(resultType))
                        {
                            if (P.GetFloatNumberTypeSize(resultType) < P.GetFloatNumberTypeSize(itemType))
                            {
                                resultType = itemType;
                            }
                        }
                    }
                }
            }
            return resultType;
        }
    }
}