using QIQI.EplOnCpp.Core;
using QIQI.EplOnCpp.Core.Expressions;
using System;
using System.IO;
using System.Linq;
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
                expr.ParamList[0].WriteToWithCast(writer, C.Info.ReturnDataType);
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

        public static void ShellCodeCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            if (expr.ParamList.Count != 1)
            {
                throw new Exception("置入代码 必须提供 字节集/文本型常量");
            }
            byte[] shellCode;
            object value;
            if (expr.ParamList[0].TryGetConstValueWithCast(EocDataTypes.Bin, out value))
            {
                shellCode = ((object[])value).Cast<byte>().ToArray();
            }
            else if (expr.ParamList[0].TryGetConstValueWithCast(EocDataTypes.String, out value))
            {
                shellCode = File.ReadAllBytes((string)value);
            }
            else
            {
                throw new Exception("置入代码 必须提供 字节集/文本型常量");
            }
            writer.Write("__asm");
            using (writer.NewBlock())
            {
                foreach (var codeByte in shellCode)
                {
                    writer.NewLine();
                    writer.Write($"_emit {codeByte}");
                }
            }
        }

        public static void IsNullParameterCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            if (expr.ParamList[0] is EocVariableExpression x
                && x.VariableInfo is EocParameterInfo paramInfo
                && paramInfo.Optional)
            {
                writer.Write("eoc_isNull_");
                writer.Write(paramInfo.CppName);
            }
            else
            {
                throw new Exception("是否为空 只能用于 可空 参数");
            }
        }

        public static void AddCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, "+");
        public static void SubCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, "-");
        public static void MulCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, "*");
        public static void EqualCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, "==", GetOperatingType(C, expr));
        public static void UnequalCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, "!=", GetOperatingType(C, expr));
        public static void LessThanCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, "<", GetOperatingType(C, expr));
        public static void GreaterThanCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, ">", GetOperatingType(C, expr));
        public static void LessThanOrEqualCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, "<=", GetOperatingType(C, expr));
        public static void GreaterThanOrEqualCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, ">=", GetOperatingType(C, expr));
        public static void AndAlsoCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, "&&");
        public static void OrElseCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, "||");
        public static void NotCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => UnaryOperationCmd(C, writer, expr, "!");
        public static void BitAndCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, "&");
        public static void BitOrCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, "|");
        public static void BitXorCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => OperationCmd(C, writer, expr, "^");
        public static void BitNotCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => UnaryOperationCmd(C, writer, expr, "~");
        public static void NegCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr) => UnaryOperationCmd(C, writer, expr, "-");

        public static void BitShiftLeftCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            if (expr.ParamList.Count != 2)
                throw new ArgumentException();
            writer.Write("(");
            expr.ParamList[0].WriteTo(writer);
            writer.Write(" << ");
            expr.ParamList[1].WriteToWithCast(writer, EocDataTypes.Int);
            writer.Write(")");
        }

        public static void BitShiftRightCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr)
        {
            if (expr.ParamList.Count != 2)
                throw new ArgumentException();
            writer.Write("(");
            expr.ParamList[0].WriteTo(writer);
            writer.Write(" >> ");
            expr.ParamList[1].WriteToWithCast(writer, EocDataTypes.Int);
            writer.Write(")");
        }

        public static void UnaryOperationCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr, string operation, CppTypeName expectedItemType = null)
        {
            if (expr.ParamList.Count != 1)
                throw new ArgumentException();
            var resultType = expr.GetResultType();
            if (expectedItemType == null)
                expectedItemType = resultType;
            writer.Write("(");
            writer.Write(operation);
            expr.ParamList[0].WriteToWithCast(writer, expectedItemType);
            writer.Write(")");
        }

        public static void OperationCmd(CodeConverter C, CodeWriter writer, EocCallExpression expr, string operation, CppTypeName expectedItemType = null)
        {
            var resultType = expr.GetResultType();
            if (expectedItemType == null)
                expectedItemType = resultType;
            var itemSeparator = $" {operation} ";
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
            if (EocDataTypes.IsIntNumberType(r))
            {
                return EocDataTypes.Double;
            }
            return r;
        }

        public static CppTypeName GetOperatingTypeForBitShift(CodeConverter C, EocCallExpression expr)
        {
            return expr.ParamList[0].GetResultType();
        }

        public static CppTypeName DetectCompatibleType(CodeConverter C, IEnumerable<EocExpression> expr)
        {
            //假定IntPtr仅可等价于Int32或Int64
            var P = C.P;
            CppTypeName resultType = null;
            foreach (var item in expr)
            {
                var itemType = item.GetResultType();
                if (resultType == null)
                    resultType = itemType;
                if (itemType == EocDataTypes.String
                    || itemType == EocDataTypes.DateTime
                    || itemType == EocDataTypes.Bin
                    || itemType == EocDataTypes.Double)
                {
                    resultType = itemType;
                    break;
                }
                if (itemType == EocDataTypes.Any || itemType == EocDataTypes.Auto)
                {
                    if (resultType != EocDataTypes.Any)
                        resultType = itemType;
                }
                else if (itemType == EocDataTypes.IntPtr)
                {
                    if (EocDataTypes.IsIntNumberType(resultType))
                    {
                        if (EocDataTypes.GetIntNumberTypeSize(resultType) <= EocDataTypes.GetIntNumberTypeSize(EocDataTypes.Int))
                            resultType = EocDataTypes.IntPtr;
                        else
                            resultType = EocDataTypes.Long;
                    }
                }
                else if (EocDataTypes.IsIntNumberType(itemType))
                {
                    if (resultType == EocDataTypes.IntPtr)
                    {
                        if (EocDataTypes.GetIntNumberTypeSize(itemType) > EocDataTypes.GetIntNumberTypeSize(EocDataTypes.Int))
                            resultType = EocDataTypes.Long;
                    }
                    else if (EocDataTypes.IsIntNumberType(resultType))
                    {
                        if (EocDataTypes.GetIntNumberTypeSize(resultType) < EocDataTypes.GetIntNumberTypeSize(itemType))
                            resultType = itemType;
                    }
                }
                else if (EocDataTypes.IsFloatNumberType(itemType))
                {
                    if (EocDataTypes.IsIntNumberType(resultType) || resultType == EocDataTypes.IntPtr)
                        resultType = itemType;
                    else if (EocDataTypes.IsFloatNumberType(resultType))
                    {
                        if (EocDataTypes.GetFloatNumberTypeSize(resultType) < EocDataTypes.GetFloatNumberTypeSize(itemType))
                            resultType = itemType;
                    }
                }
            }
            return resultType;
        }

        public static CppTypeName GetOperatingType(CodeConverter C, EocCallExpression expr) => DetectCompatibleType(C, expr.ParamList);
    }
}