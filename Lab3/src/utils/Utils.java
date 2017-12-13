package utils;

import java.util.HashMap;
import java.util.Map;

public class Utils {
    private static Map<String, String> varTypes = new HashMap<>();

    public static void addVars(String type, String ... args) {
        for (String arg : args) {
            if (varTypes.containsKey(arg)) {
                throw new IllegalArgumentException("Variable " + arg + " has more than one declaration.");
            }
            varTypes.put(arg, type);
        }
    }

    public static String getVarType(String var) {
        if (!varTypes.containsKey(var)) {
            throw new IllegalArgumentException("Variable " + var + " wasn't declared.");
        }
        return varTypes.get(var);
    }

    public static Map<String, String> getVarTypes() {
        return varTypes;
    }

    public static void resetVarTypes() {
        varTypes = new HashMap<>();
    }

    public static String genScanf(boolean ln, String ... varNames) {
        if (varNames.length == 0) {
            return "getchar();";
        }
        StringBuilder sb = new StringBuilder("scanf(");
        sb.append("\"");
        sb.append(betweenQuotes(varNames));
        if (ln) {
            sb.append("\\n");
        }
        sb.append("\"");
        for (String v : varNames) {
            sb.append(", &");
            sb.append(v);
        }
        sb.append(");");
        return sb.toString();
    }

    private static StringBuilder betweenQuotes(String ... varNames) {
        StringBuilder sb = new StringBuilder("");
        for (String v : varNames) {
            String vType = getVarType(v);
            if (vType.equals("int")) {
                sb.append("%d");
            } else if (vType.equals("double")) {
                sb.append("%f");
            } else if (vType.equals("char")) {
                sb.append("%c");
            } else if (vType.equals("bool")) {
                sb.append("%d");
            }
        }
        return sb;
    }

    public static String genPrintf(boolean ln, String ... varNames) {
        if (varNames.length == 0) {
            return "printf(\"\n\");";
        }
        StringBuilder sb = new StringBuilder("printf(");
        sb.append("\"");
        sb.append(betweenQuotes(varNames));
        if (ln) {
            sb.append("\\n");
        }
        sb.append("\"");
        for (String v : varNames) {
            sb.append(", ");
            sb.append(v);
        }
        sb.append(");");
        return sb.toString();
    }

}
