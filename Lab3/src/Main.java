import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;

import java.io.IOException;
import java.io.PrintWriter;

import gen.*;
import utils.*;

public class Main {
    public static void main(String args[]) throws IOException {
        String fileName = "input3.pas";
        CharStream input = CharStreams.fromFileName(fileName);
        PascalGrammarLexer pascalLexer = new PascalGrammarLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(pascalLexer);
        PascalGrammarParser pascalParser = new PascalGrammarParser(tokens);
        pascalParser.setBuildParseTree(false);
        PrintWriter writer = new PrintWriter("output.c", "UTF-8");
        String s = pascalParser.codeStructure().str;
        writer.print(s);
        Utils.resetVarTypes();
        writer.close();
    }

}
